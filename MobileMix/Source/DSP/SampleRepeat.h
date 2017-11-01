/*
  ==============================================================================

    SampleRepeat.h
    Created: 31 Oct 2017 1:22:37am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SampleRepeat :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        size_t samplesToRepeat = 0;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    SampleRepeat() = default;
    ~SampleRepeat() = default;

    void prepare(const dsp::ProcessSpec& spec) override
    {
        channelStates.clear();
        channelStates.resize(spec.numChannels);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        for (size_t channel = 0; channel < context.getInputBlock().getNumChannels(); ++channel)
        {
            float* samples = context.getOutputBlock().getChannelPointer(channel);
            ChannelState* channelState = &channelStates[channel];

            for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
            {
                if (channelState->samplesReplaced == 0)
                    channelState->repeatSampleValue = samples[i];
                else
                    samples[i] = channelState->repeatSampleValue;

                channelState->samplesReplaced++;
                if (channelState->samplesReplaced == params->samplesToRepeat)
                    channelState->samplesReplaced = 0;
            }
        }
    }

    void reset() override
    {
        channelStates.clear();
    }

    Parameters::Ptr params = new Parameters;

private:
    struct ChannelState
    {
        size_t samplesReplaced = 0;
        float repeatSampleValue = 0.0f;
    };

    std::vector<ChannelState> channelStates;
};
