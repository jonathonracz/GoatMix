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

    float getPeak(int channel) const
    {
        return channelStates[channel].peakSum / channelStates[channel].buffer.getLogicalCapacity();
    }

    float getRMS(int channel) const
    {
        return std::sqrt(channelStates[channel].rmsSum / channelStates[channel].buffer.getLogicalCapacity());
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
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
            }
        }
    }

    void pushSample(float newSample, int channel)
    {
        if (channelStates[channel].buffer.isFull())
            popSample(channel);

        channelStates[channel].buffer.push(newSample);
        channelStates[channel].peakSum += newSample;
        channelStates[channel].rmsSum += (newSample * newSample);
    }

    void popSample(int channel)
    {
        float poppedSample = channelStates[channel].buffer.pop();
        channelStates[channel].peakSum -= poppedSample;
        channelStates[channel].rmsSum -= (poppedSample * poppedSample);
    }

    struct ChannelState
    {
        RingBuffer<float> buffer;
        float peakSum = 0.0f;
        float rmsSum = 0.0f;
    };

    std::vector<ChannelState> channelStates;
};
