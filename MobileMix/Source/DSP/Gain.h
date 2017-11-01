/*
  ==============================================================================

    Gain.h
    Created: 31 Oct 2017 3:46:44pm
    Author:  Jonathon Racz

  =============================================================================
*/

#pragma once

#include "JuceHeader.h"

class Gain :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        public dsp::ProcessorState
    {
        float gain = 1.0f;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    Gain() = default;
    ~Gain() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        gain.prepare(spec);
        gain.processor.setRampDurationSeconds(0.1); // TODO: Test and tweak this.
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        gain.processor.setGainLinear(params->gain);
        gain.process(context);
    }

    void reset() noexcept override
    {
        gain.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    dsp::ProcessorWrapper<dsp::Gain<float>> gain;

};
