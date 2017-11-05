/*
  ==============================================================================

    DryWet.h
    Created: 1 Nov 2017 11:58:01pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Gain.h"

class DryWet :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        float wetDry = 100.0f; // Percentage
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    DryWet() = default;
    ~DryWet() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        dryBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
    }

    void copyDrySignal(const AudioBuffer<float>& buffer) noexcept
    {
        dryBuffer.makeCopyOf(buffer, true);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        wetGain.params->gain = params->wetDry / 100.0f;
        dryGain.params->gain = 1.0f - (params->wetDry / 100.0f);

        wetGain.process(context);

        dsp::AudioBlock<float> dryBlock(dryBuffer);
        dsp::ProcessContextReplacing<float> dryContext(dryBlock);
        dryGain.process(dryContext);

        context.getOutputBlock().add(dryBlock);
    }

    void reset() noexcept override
    {
        wetGain.reset();
        dryGain.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    AudioBuffer<float> dryBuffer;
    Gain wetGain;
    Gain dryGain;
};
