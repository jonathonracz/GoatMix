/*
  ==============================================================================

    AmplitudeQuantize.h
    Created: 31 Oct 2017 1:21:53am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

struct AmplitudeQuantize :
    dsp::ProcessorBase
{
    struct Parameters :
        dsp::ProcessorState
    {
        size_t bitDepth = 16;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    AmplitudeQuantize() = default;
    ~AmplitudeQuantize() = default;

    void prepare(const dsp::ProcessSpec& spec) override {}
    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        if (params->bitDepth >= 16)
            return;

        // Convert from floating point scale to bit depth scale.
        context.getOutputBlock().multiply(static_cast<float>(params->bitDepth));

        // Quantize all samples to the bit depth via rounding.
        for (size_t channel = 0; channel < context.getInputBlock().getNumChannels(); ++channel)
        {
            float* samples = context.getOutputBlock().getChannelPointer(channel);
            for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
                samples[i] = std::round(samples[i]);
        }

        // Convert back to floating point.
        context.getOutputBlock().multiply(1.0f / static_cast<float>(params->bitDepth));
    }
    
    void reset() override {}

    Parameters::Ptr params = new Parameters;
};
