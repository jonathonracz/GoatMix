/*
  ==============================================================================

    DelayLine.h
    Created: 31 Oct 2017 2:57:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "RingBuffer.h"

class DelayLine :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        size_t maxDelay;
        size_t samplesToDelay;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    DelayLine() = default;
    ~DelayLine() = default;

    void prepare(const dsp::ProcessSpec& spec) override
    {
        channelStates.clear();
        channelStates.resize(spec.numChannels, ChannelState
        {
            RingBuffer<float>(static_cast<int>(params->maxDelay))
        });

        for (auto& channelState : channelStates)
            channelState.line.fill(0);

        resizeScratchSpaceFadeOut.resize(params->maxDelay);
        resizeScratchSpaceFadeIn.resize(params->maxDelay);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        if (context.isBypassed)
            return;

        for (size_t channel = 0; channel < context.getInputBlock().getNumChannels(); ++channel)
        {
            float* samples = context.getOutputBlock().getChannelPointer(channel);
            ChannelState* channelState = &channelStates[channel];
            if (params->samplesToDelay == 0 && channelState->line.logicalCapacity() == 0)
                continue;

            int newDelay = static_cast<int>(params->samplesToDelay);
            jassert(newDelay <= params->maxDelay); // This would require allocation on the audio thread!

            // Resize our ringbuffer if we have a new delay length.
            if (newDelay != channelState->line.logicalCapacity())
            {
                DBG("New delay detected! " << newDelay << " samples");
                int totalNumElements = 0;
                {
                    int firstHalfSize = channelState->line.getSizeOfFirstHalf();
                    int secondHalfSize = channelState->line.getSizeOfSecondHalf();
                    memcpy(&resizeScratchSpaceFadeOut[0], channelState->line.getPointerToFirstHalf(), firstHalfSize * sizeof(float));
                    memcpy(&resizeScratchSpaceFadeOut[firstHalfSize], channelState->line.getPointerToSecondHalf(), secondHalfSize * sizeof(float));
                    memcpy(&resizeScratchSpaceFadeIn[0], &resizeScratchSpaceFadeOut[0], channelState->line.numElements() * sizeof(float));
                    totalNumElements = firstHalfSize + secondHalfSize;
                }

                // Crossfade to avoid popping using a simple PSOLA-type method with
                // a linear fade.
                LinearSmoothedValue<float> fadeOut(1.0f);
                fadeOut.setValue(0.0f);
                LinearSmoothedValue<float> fadeIn(0.0f);
                fadeIn.setValue(1.0f);
                if (newDelay > channelState->line.numElements()) // Stretching
                {
                    int fadeSpace = newDelay - (2 * channelState->line.numElements());
                    if (fadeSpace < 0) // Has overlap
                    {
                        fadeSpace *= -1;
                        fadeOut.applyGain(&resizeScratchSpaceFadeOut[totalNumElements - fadeSpace], fadeSpace);
                        fadeIn.applyGain(&resizeScratchSpaceFadeIn[0], fadeSpace);
                        FloatVectorOperations::add(&resizeScratchSpaceFadeOut[totalNumElements - fadeSpace], &resizeScratchSpaceFadeIn[0], fadeSpace);
                        memcpy(&resizeScratchSpaceFadeOut[totalNumElements], &resizeScratchSpaceFadeIn[fadeSpace], (totalNumElements - fadeSpace) * sizeof(float));
                    }
                    else // Has no overlap
                    {
                        fadeOut.applyGain(&resizeScratchSpaceFadeOut[0], totalNumElements);
                        fadeIn.applyGain(&resizeScratchSpaceFadeIn[0], totalNumElements);
                        memset(&resizeScratchSpaceFadeOut[totalNumElements], 0, fadeSpace * sizeof(float));
                        memcpy(&resizeScratchSpaceFadeOut[totalNumElements + fadeSpace], &resizeScratchSpaceFadeIn[0], totalNumElements);
                    }
                }
                else if (newDelay < channelState->line.numElements()) // Shrinking
                {
                    fadeOut.applyGain(&resizeScratchSpaceFadeOut[0], newDelay);
                    fadeIn.applyGain(&resizeScratchSpaceFadeIn[totalNumElements - newDelay], newDelay);
                    FloatVectorOperations::add(&resizeScratchSpaceFadeOut[0], &resizeScratchSpaceFadeIn[totalNumElements - newDelay], newDelay);
                }

                // Resize the RingBuffer and copy in the new data.
                channelState->line.setLogicalCapacity(newDelay);
                channelState->line.setData(resizeScratchSpaceFadeOut.data(), newDelay);
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

    // This could be done with one scratch buffer, but it gets way harder
    // because I'd have to mix the std::vector and AudioBlock APIs for accessing
    // and manipulating data. Maybe someday.
    std::vector<float> resizeScratchSpaceFadeOut;
    std::vector<float> resizeScratchSpaceFadeIn;
};
