/*
  ==============================================================================

    SignalSnapshotter.h
    Created: 21 Nov 2017 2:02:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "RingBuffer.h"
#include "../External/readerwriterqueue/readerwriterqueue.h"
#include "RefCountedAudioBuffer.h"
#include <vector>

class SignalSnapshotter :
    public dsp::ProcessorBase
{
public:
    class Snapshot :
        public ReferenceCountedObject
    {
    public:
        Snapshot() {} // Creates a null snapshot.
        ~Snapshot()
        {
            // Return the referenced buffer to the pool if applicable.
            if (owner && signal && getReferenceCount() == 0)
                owner->returnReadBuffer(signal);
        }

        bool isValid() const noexcept { return signal != nullptr; }

        // Returns the underlying buffer.
        const RefCountedAudioBuffer<float>::Ptr getSignal() const noexcept { return signal; }

        using Ptr = ReferenceCountedObjectPtr<Snapshot>;
    private:
        friend SignalSnapshotter;
        explicit Snapshot(SignalSnapshotter* _owner, RefCountedAudioBuffer<float>::Ptr _signal) :
            signal(_signal), owner(_owner) {}
        RefCountedAudioBuffer<float>::Ptr signal = nullptr;
        WeakReference<SignalSnapshotter> owner = nullptr;
    };

    struct Parameters :
        dsp::ProcessorState
    {
        float snapshotTimeDeltaSeconds = 1.0f / 30.0f; // Time delta
        int snapshotSampleSize = 512; // Samples to snapshot
        int numSnapshotBuffers = 8;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    SignalSnapshotter() = default;
    ~SignalSnapshotter() = default;

    double getActiveSampleRate() const noexcept { return activeSampleRate; }
    float getActiveSnapshotTimeDeltaSeconds() const noexcept { return activeSnapshotTimeDeltaSeconds; }
    int getActiveSnapshotSampleSize() const noexcept { return activeSnapshotSampleSize; }
    int getActiveNumSnapshotBuffers() const noexcept { return activeNumSnapshotBuffers; }

    // For use by reading classes.
    Snapshot::Ptr getNextSnapshot() noexcept
    {
        RefCountedAudioBuffer<float>::Ptr nextBuffer = nullptr;
        readBuffers.try_dequeue(nextBuffer);
        return new Snapshot(this, nextBuffer);
    }

    Snapshot::Ptr getLatestSnapshot() noexcept
    {
        RefCountedAudioBuffer<float>::Ptr latestBuffer = nullptr;
        if (!readBuffers.try_dequeue(latestBuffer))
            return new Snapshot(this, latestBuffer);

        for (size_t i = 0; i < snapshots.size() - 1; ++i)
        {
            RefCountedAudioBuffer<float>::Ptr newBuffer = nullptr;
            if (!readBuffers.try_dequeue(newBuffer))
                break;

            bool result = writeBuffers.try_enqueue(latestBuffer);
            jassert(result);
            latestBuffer = newBuffer;
        }

        // Explicity prevent copying (so we don't call the destructor more than
        // once, returning the snapshot buffer to the pool more than once).
        return new Snapshot(this, latestBuffer);
    }

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        masterReference.clear(); // Prevent any snapshots from getting re-queued.
        activeSampleRate = spec.sampleRate;
        activeSnapshotTimeDeltaSeconds = params->snapshotTimeDeltaSeconds;
        activeSnapshotSampleSize = params->snapshotSampleSize;
        activeNumSnapshotBuffers = params->numSnapshotBuffers;

        samplesBetweenSnapshots = static_cast<int>(activeSampleRate * activeSnapshotTimeDeltaSeconds);
        snapshotBuffers.resize(spec.numChannels);
        for (RingBuffer<float>& snapshotBuffer : snapshotBuffers)
        {
            snapshotBuffer.setLogicalCapacity(params->snapshotSampleSize);
        }

        readBuffers = moodycamel::ReaderWriterQueue<RefCountedAudioBuffer<float>::Ptr>(activeNumSnapshotBuffers);
        writeBuffers = moodycamel::ReaderWriterQueue<RefCountedAudioBuffer<float>::Ptr>(activeNumSnapshotBuffers);

        snapshots.clear();
        while (activeNumSnapshotBuffers > snapshots.size())
            snapshots.add(new RefCountedAudioBuffer<float>);

        for (RefCountedAudioBuffer<float>::Ptr snapshot : snapshots)
        {
            snapshot->setSize(static_cast<int>(spec.numChannels), static_cast<int>(activeSnapshotSampleSize));
            bool enqueueResult = false;
            enqueueResult = writeBuffers.try_enqueue(snapshot);
            jassert(enqueueResult);
        }

        reset();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        int samplesToProcess = static_cast<int>(context.getInputBlock().getNumSamples());
        while (samplesToProcess > 0)
        {
            int currentSample = static_cast<int>(context.getInputBlock().getNumSamples()) - samplesToProcess;
            int samplesToProcessForThisLoop = std::min(samplesToProcess, samplesUntilSnapshot);

            copyBlockToSnapshotBuffer(context.getInputBlock().getSubBlock(currentSample, samplesToProcessForThisLoop));

            samplesToProcess -= samplesToProcessForThisLoop;
            samplesUntilSnapshot -= samplesToProcessForThisLoop;

            if (samplesUntilSnapshot <= 0)
            {
                copySnapshotBufferToQueue();
                samplesUntilSnapshot = samplesBetweenSnapshots;
            }
        }
    }

    void reset() noexcept override
    {
        for (RingBuffer<float>& ringBuffer : snapshotBuffers)
        {
            ringBuffer.clear();
            ringBuffer.fill();
        }

        samplesUntilSnapshot = samplesBetweenSnapshots;
    }

    Parameters::Ptr params = new Parameters;

private:
    void returnReadBuffer(RefCountedAudioBuffer<float>::Ptr buffer) noexcept
    {
        jassert(buffer);
        bool result = writeBuffers.try_enqueue(buffer);
        jassert(result);
    }

    void copyBlockToSnapshotBuffer(const dsp::AudioBlock<float>& block) noexcept
    {
        jassert(block.getNumChannels() <= snapshotBuffers.size());
        for (size_t channel = 0; channel < block.getNumChannels(); ++channel)
            snapshotBuffers[channel].push(block.getChannelPointer(channel), static_cast<int>(block.getNumSamples()));
    }

    void copySnapshotBufferToQueue() noexcept
    {
        RefCountedAudioBuffer<float>::Ptr buffer = nullptr;
        writeBuffers.try_dequeue(buffer);
        if (buffer)
        {
            jcf::BufferDebugger::capture("Snapshotter (copied buffer)", buffer->getReadPointer(0), buffer->getNumSamples(), -1.0f, 1.0f);
            jassert(buffer->getNumChannels() == static_cast<int>(snapshotBuffers.size()));
            for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
            {
                const RingBuffer<float>& snapshot = snapshotBuffers[static_cast<size_t>(channel)];
                jassert(snapshot.getNumElements() == buffer->getNumSamples());
                FloatVectorOperations::copy(buffer->getWritePointer(channel), snapshot.getPointerToFirstHalf(), snapshot.getSizeOfFirstHalf());
                if (snapshot.getSizeOfSecondHalf() > 0)
                    FloatVectorOperations::copy(buffer->getWritePointer(channel, snapshot.getSizeOfFirstHalf()), snapshot.getPointerToSecondHalf(), snapshot.getSizeOfSecondHalf());
            }

            bool result = readBuffers.try_enqueue(buffer);
            jassert(result);
        }
    }

    friend Snapshot;

    // The queue of fresh snapshots produced by this class which are ready to
    // be read/used by clients. After the clients are finished, deletion of the
    // containing Snapshot objects will place the referenced AudioBuffer
    // pointers into the writeBuffers queue to be recycled.
    moodycamel::ReaderWriterQueue<RefCountedAudioBuffer<float>::Ptr> readBuffers;

    // The queue of old snapshots available to have new data written to and
    // placed in back in readBuffer for use by clients of this class.
    moodycamel::ReaderWriterQueue<RefCountedAudioBuffer<float>::Ptr> writeBuffers;

    // RingBuffer objects containing the rolling data which can be snapshotted
    // when the delta time of samples between snapshots is met.
    std::vector<RingBuffer<float>> snapshotBuffers;

    ReferenceCountedArray<RefCountedAudioBuffer<float>> snapshots;

    int samplesBetweenSnapshots = 0;
    int samplesUntilSnapshot = 0;

    double activeSampleRate = 0.0;
    float activeSnapshotTimeDeltaSeconds = params->snapshotTimeDeltaSeconds;
    int activeSnapshotSampleSize = params->snapshotSampleSize;
    int activeNumSnapshotBuffers = params->numSnapshotBuffers;

    JUCE_DECLARE_WEAK_REFERENCEABLE(SignalSnapshotter)
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SignalSnapshotter)
};
