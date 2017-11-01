/*
  ==============================================================================

    InvertPhase.h
    Created: 1 Nov 2017 2:04:24am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Gain.h"

class InvertPhase :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        public dsp::ProcessorState
    {
        bool invert = false;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    InvertPhase() = default;
    ~InvertPhase() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        gain.prepare(spec);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        gain.params->gain = (params->invert) ? -1.0f : 1.0f;
        gain.process(context);
    }

    void reset() noexcept override
    {
        gain.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    Gain gain;

};
