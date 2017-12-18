/*
  ==============================================================================

    Compressor.h
    Created: 2 Nov 2017 1:47:19pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../External/SimpleComp/SimpleComp.h"
#include <vector>

class Compressor :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        size_t attack = 100; // Milliseconds
        size_t release = 100; // Milliseconds
        float threshold = 0.5f; // Linear dB
        size_t ratio = 1; // As 1:ratio
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    Compressor() = default;
    ~Compressor() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        jassert(spec.numChannels == 2); // TODO: Test chunkware compressor on mono...
        compressor.setSampleRate(spec.sampleRate);
        compressor.initRuntime();
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();
        float* left = context.getOutputBlock().getChannelPointer(0);
        float* right = context.getOutputBlock().getChannelPointer(1);
        for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
        {
            // Copy conversions like this suck, but I can't figure out a good
            // cast conversion that will allow me to pass the float pointer
            // as a double reference.
            double currLeft = left[i];
            double currRight = right[i];
            compressor.process(currLeft, currRight);
            left[i] = static_cast<float>(currLeft);
            right[i] = static_cast<float>(currRight);

        }
    }

    void reset() noexcept override
    {
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        compressor.setAttack(static_cast<double>(params->attack));
        compressor.setRelease(static_cast<double>(params->release));
        compressor.setThresh(static_cast<double>(Decibels::gainToDecibels(params->threshold)));
        compressor.setRatio(1.0 / static_cast<double>(params->ratio));
    }

    // TODO: We may need some sort of parameter smoothing...
    chunkware_simple::SimpleComp compressor;

};
