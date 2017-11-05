/*
  ==============================================================================

    MMStateVariableFilter.h
    Created: 3 Nov 2017 2:29:28am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MMStateVariableFilter :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        dsp::StateVariableFilter::Parameters<float>::Type type =
            dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        float cutoff = 1000.0f;
        float resonance = (1.0f / std::sqrt(2.0f));
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    MMStateVariableFilter() = default;
    ~MMStateVariableFilter() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        sampleRate = spec.sampleRate;
        filter.prepare(spec);
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();
        filter.process(context);
    }

    void reset() noexcept override
    {
        filter.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        filter.state->type = params->type;
        filter.state->setCutOffFrequency(sampleRate, params->cutoff, params->resonance);
    }

    double sampleRate = 0.0;
    dsp::ProcessorDuplicator<
        dsp::StateVariableFilter::Filter<float>,
        dsp::StateVariableFilter::Parameters<float>> filter;
};
