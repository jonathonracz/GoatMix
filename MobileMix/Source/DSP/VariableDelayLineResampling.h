/*
  ==============================================================================

    VariableDelayLineResampling.h
    Created: 2 Nov 2017 4:09:55pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "RingBuffer.h"

class VariableDelayLineResampling :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
    dsp::ProcessorState
    {
        size_t maxDelay = 0;
        size_t samplesToDelay = 0;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    VariableDelayLineResampling() = default;
    ~VariableDelayLineResampling() = default;

    void prepare(const dsp::ProcessSpec& spec) override
    {
        channelStates.clear();
        channelStates.resize(spec.numChannels, ChannelState
                             {
                                 RingBuffer<float>(static_cast<int>(params->maxDelay))
                             });

        for (auto& channelState : channelStates)
            channelState.line.fill(0);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        if (context.isBypassed)
            return;

        for (size_t channel = 0; channel < context.getInputBlock().getNumChannels(); ++channel)
        {
            float* samples = context.getOutputBlock().getChannelPointer(channel);
            ChannelState* channelState = &channelStates[channel];
            if (params->samplesToDelay == 0 && channelState->line.getLogicalCapacity() == 0)
                continue;

            int newDelay = static_cast<int>(params->samplesToDelay);
            jassert(newDelay <= params->maxDelay); // This would require allocation on the audio thread!

            // Resize our ringbuffer if we have a new delay length.
            if (newDelay != channelState->line.getLogicalCapacity())
            {
                interp.reset();
                channelState->line.linearize();
                float* lineSamples = channelState->line.getPointerToFirstHalf();
                int numLineSamples = channelState->line.getNumElements();
                interp.process(numLineSamples / static_cast<double>(newDelay), lineSamples, lineSamples, newDelay);

                // Resize the RingBuffer and copy in the new data.
                channelState->line.setLogicalCapacity(newDelay, true);
            }

            // Actually push to the ringbuffer.
            for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
            {
                if (params->samplesToDelay > 0)
                {
                    float delayedSample = channelState->line.pop();
                    channelState->line.push(samples[i]);
                    samples[i] = delayedSample;
                }
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
        RingBuffer<float> line;
    };

    std::vector<ChannelState> channelStates;
    LagrangeInterpolator interp;
};
