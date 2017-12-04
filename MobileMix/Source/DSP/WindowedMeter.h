/*
  ==============================================================================

    WindowedMeter.h
    Created: 4 Nov 2017 1:48:58am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "RingBuffer.h"
#include "DecibelDecay.h"
#include <atomic>

class WindowedMeter :
    public dsp::ProcessorBase,
    public AsyncUpdater,
    public Timer
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        float msIntegrationTime = 25.0f;
        float msPeakHoldTime = 1000.0f;
        float dBPerSecondDecay = DecibelDecay::DecaydBFactors::ppmType1;
        float msMeterResetTimeout = 3000.0f;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    WindowedMeter() { reset(); }
    WindowedMeter(Parameters::Ptr parameters) : params(parameters) { reset(); }
    ~WindowedMeter() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        activeSampleRate = spec.sampleRate;
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();
        activeBlockSize = context.getInputBlock().getNumSamples();
        const float* sampleRead = context.getInputBlock().getChannelPointer(0);
        for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
            pushSample(sampleRead[i]);

        calculateValues();
    }

    void reset() noexcept override
    {
        std::atomic_thread_fence(std::memory_order_release);
        peakInstant.store(0.0f, std::memory_order_relaxed);
        peakWindowed.store(0.0f, std::memory_order_relaxed);
        rms.store(0.0f, std::memory_order_relaxed);
        peakOverall.store(0.0f, std::memory_order_relaxed);
        peakHold.store(0.0f, std::memory_order_relaxed);
    }

    float getPeakInstant() const noexcept
    {
        return peakInstant.load(std::memory_order_acquire);
    }

    float getPeakWindowed() const noexcept
    {
        return peakWindowed.load(std::memory_order_acquire);
    }

    float getRMS() const noexcept
    {
        return rms.load(std::memory_order_acquire);
    }

    float getPeakHold() const noexcept
    {
        return peakHold.load(std::memory_order_acquire);
    }

    float getPeakOverall() const noexcept
    {
        return peakOverall.load(std::memory_order_acquire);
    }

    void resetPeakOverall() noexcept
    {
        peakOverall.store(0.0f, std::memory_order_release);
    }

    bool getClippingStatus() const noexcept
    {
        return getPeakOverall() > 1.0f;
    }

    void resetClippingStatus() noexcept
    {
        resetPeakOverall();
    }

    Parameters::Ptr params = new Parameters;

private:
    friend class MultiWindowedMeter;

    void updateParameters() noexcept
    {
        int newWindowSize = (params->msIntegrationTime / 1000.0f) * activeSampleRate;
        if (newWindowSize != buffer.getLogicalCapacity())
        {
            if (newWindowSize > buffer.getLogicalCapacity())
                while (buffer.getNumElements() > newWindowSize)
                    popSample();

            buffer.setLogicalCapacity(newWindowSize);
        }

        decay.setdBPerSecondDecay(params->dBPerSecondDecay);
        activeSamplesToHold = (params->msPeakHoldTime / 1000.0f) * activeSampleRate;
        msMeterResetTimeout.store(params->msMeterResetTimeout, std::memory_order_release);
    }

    void pushSample(float newSample) noexcept
    {
        newSample = std::fabs(newSample);
        if (buffer.isFull())
            popSample();

        buffer.push(newSample);

        peakSum += newSample;
        rmsSum += square(newSample);
    }

    void popSample() noexcept
    {
        float poppedSample = buffer.pop();
        peakSum -= poppedSample;
        rmsSum -= square(poppedSample);
    }

    void calculateValues() noexcept
    {
        float deltaTime = activeBlockSize / static_cast<float>(activeSampleRate);
        float bufferMax = std::max(FloatVectorOperations::findMaximum(buffer.getPointerToFirstHalf(), buffer.getSizeOfFirstHalf()),
                                   FloatVectorOperations::findMaximum(buffer.getPointerToSecondHalf(), buffer.getSizeOfSecondHalf()));
        float newPeakWindowed = std::max(peakSum / buffer.getLogicalCapacity(), decay.decayLinear(peakWindowed.load(std::memory_order_relaxed), deltaTime));
        float newRMS = std::max(std::sqrt(rmsSum / buffer.getLogicalCapacity()), decay.decayLinear(rms.load(std::memory_order_relaxed), deltaTime));

        std::atomic_thread_fence(std::memory_order_release);
        peakInstant.store(bufferMax, std::memory_order_relaxed);
        peakWindowed.store(newPeakWindowed, std::memory_order_relaxed);
        rms.store(newRMS, std::memory_order_relaxed);

        if (bufferMax > peakOverall.load(std::memory_order_relaxed))
            peakOverall.store(bufferMax, std::memory_order_relaxed);

        bool shouldSetPeakHold = false;
        if (bufferMax > peakHold.load(std::memory_order_relaxed))
        {
            shouldSetPeakHold = true;
            samplesHeld = 0;
        }

        if (samplesHeld > activeSamplesToHold)
        {
            shouldSetPeakHold = true;
            samplesHeld %= activeSamplesToHold;
        }

        if (shouldSetPeakHold)
            peakHold.store(bufferMax, std::memory_order_relaxed);
    }

    void handleAsyncUpdate() noexcept override
    {
        startTimer(static_cast<int>(msMeterResetTimeout.load(std::memory_order_acquire)));
    }

    void timerCallback() noexcept override
    {
        reset();
    }

    std::atomic<float> peakInstant;
    std::atomic<float> peakWindowed;
    std::atomic<float> peakOverall;
    std::atomic<float> peakHold;
    std::atomic<float> rms;

    std::atomic<float> msMeterResetTimeout;

    RingBuffer<float> buffer;
    float peakSum;
    float rmsSum;
    DecibelDecay decay;
    size_t samplesHeld;

    double activeSampleRate;
    size_t activeBlockSize;
    size_t activeSamplesToHold;

    JUCE_DECLARE_WEAK_REFERENCEABLE(WindowedMeter)
};
