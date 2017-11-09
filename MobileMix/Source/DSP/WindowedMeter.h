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
#include <atomic>

class WindowedMeter :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        size_t windowSamples = 8;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    WindowedMeter() = default;
    ~WindowedMeter() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        channelStates.resize(spec.numChannels);
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();
        for (size_t channel = 0; channel < context.getInputBlock().getNumChannels(); ++channel)
        {
            const float* sampleRead = context.getInputBlock().getChannelPointer(channel);
            for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
                pushSample(sampleRead[i], static_cast<int>(channel));
        }
    }

    void reset() noexcept override
    {
    }

    float getPeak(int channel) const noexcept
    {
        return channelStates[channel].peakSum.load(std::memory_order_relaxed) / channelStates[channel].bufferSize.load(std::memory_order_relaxed);
    }

    float getRMS(int channel) const noexcept
    {
        return std::sqrt(channelStates[channel].rmsSum.load(std::memory_order_relaxed) / channelStates[channel].bufferSize.load(std::memory_order_relaxed));
    }

    float getOverallPeak(int channel) const noexcept
    {
        return channelStates[channel].overallPeak.load(std::memory_order_relaxed);
    }

    void resetOverallPeak(int channel) noexcept
    {
        channelStates[channel].overallPeak.store(0.0f, std::memory_order_relaxed);
    }

    void resetOverallPeak() noexcept
    {
        for (int i = 0; i < static_cast<int>(channelStates.size()); ++i)
            resetOverallPeak(i);
    }

    bool getClippingStatus(int channel) const noexcept
    {
        return getOverallPeak(channel) > 1.0f;
    }

    void resetClippingStatus(int channel) noexcept
    {
        resetOverallPeak(channel);
    }

    void resetClippingStatus() noexcept
    {
        resetOverallPeak();
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters() noexcept
    {
        for (int channel = 0; channel < static_cast<int>(channelStates.size()); ++channel)
        {
            size_t currWindowSize = params->windowSamples;
            if (currWindowSize != channelStates[channel].buffer.getLogicalCapacity())
            {
                if (currWindowSize > channelStates[channel].buffer.getLogicalCapacity())
                    while (channelStates[channel].buffer.getNumElements() != currWindowSize)
                        popSample(channel);

                channelStates[channel].buffer.setLogicalCapacity(static_cast<int>(currWindowSize));
                channelStates[channel].bufferSize.store(static_cast<int>(currWindowSize), std::memory_order_relaxed);
            }
        }
    }

    void pushSample(float newSample, int channel) noexcept
    {
        ChannelState* ch = &channelStates[channel];
        if (ch->buffer.isFull())
            popSample(channel);

        ch->buffer.push(newSample);

        float newPeakSum = ch->peakSum.load(std::memory_order_relaxed) + newSample;
        float newRMSSum = ch->rmsSum.load(std::memory_order_relaxed) + (newSample * newSample);
        ch->peakSum.store(newPeakSum, std::memory_order_relaxed);
        ch->rmsSum.store(newRMSSum, std::memory_order_relaxed);

        if (newSample > ch->overallPeak.load(std::memory_order_relaxed))
            ch->overallPeak.store(newSample, std::memory_order_relaxed);
    }

    void popSample(int channel) noexcept
    {
        ChannelState* ch = &channelStates[channel];
        float poppedSample = ch->buffer.pop();

        float newPeakSum = ch->peakSum.load(std::memory_order_relaxed) - poppedSample;
        float newRMSSum = ch->rmsSum.load(std::memory_order_relaxed) - (poppedSample * poppedSample);
        ch->peakSum.store(newPeakSum, std::memory_order_relaxed);
        ch->rmsSum.store(newRMSSum, std::memory_order_relaxed);
    }

    struct ChannelState
    {
        ChannelState() {}
        explicit ChannelState(const ChannelState& other) :
            buffer(other.buffer),
            bufferSize(other.bufferSize.load()),
            peakSum(other.peakSum.load()),
            rmsSum(other.rmsSum.load()),
            overallPeak(other.overallPeak.load())
        {
        }

        ~ChannelState() {}

        RingBuffer<float> buffer;
        std::atomic<int> bufferSize = 0;
        std::atomic<float> peakSum = 0.0f;
        std::atomic<float> rmsSum = 0.0f;
        std::atomic<float> overallPeak = 0.0f;
    };

    std::vector<ChannelState> channelStates;
};
