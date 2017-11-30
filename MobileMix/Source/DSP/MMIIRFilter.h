/*
  ==============================================================================

    MMIIRFilter.h
    Created: 3 Nov 2017 2:29:36am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MMIIRFilter :
    dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        enum FilterMode
        {
            highPass,
            highShelf,
            peak,
            lowShelf,
            lowPass,
        };

        FilterMode mode;
        float cutoff = 1000.0f;
        float q = 1.0f;
        float gain = 1.0f; // Has no effect for low and high pass filters!
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    MMIIRFilter() = default;
    ~MMIIRFilter() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        sampleRate = spec.sampleRate;
        iir.prepare(spec);
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();
        iir.process(context);
    }

    void reset() noexcept override
    {
        iir.reset();
    }

    dsp::IIR::Coefficients<float>::Ptr getActiveCoefficients() const noexcept
    {
        return iir.state;
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        // If a param changed, regenerate coefficients.
        if (params->mode != currentMode ||
            params->cutoff != currentCutoff ||
            params->q != currentQ ||
            params->gain != currentGain)
        {
            switch(params->mode)
            {
                case Parameters::FilterMode::highPass:
                {
                    iir.state = dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, params->cutoff, params->q);
                    break;
                }
                case Parameters::FilterMode::highShelf:
                {
                    iir.state = dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, params->cutoff, params->q, params->gain);
                    break;
                }
                case Parameters::FilterMode::peak:
                {
                    iir.state = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, params->cutoff, params->q, params->gain);
                    break;
                }
                case Parameters::FilterMode::lowShelf:
                {
                    iir.state = dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, params->cutoff, params->q, params->gain);
                    break;
                }
                case Parameters::FilterMode::lowPass:
                {
                    iir.state = dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, params->cutoff, params->q);
                    break;
                }
                default: jassertfalse;
            }

            currentMode = params->mode;
            currentCutoff = params->cutoff;
            currentQ = params->q;
        }
    }

    dsp::ProcessorDuplicator<
        dsp::IIR::Filter<float>,
        dsp::IIR::Coefficients<float>> iir;

    Parameters::FilterMode currentMode;
    float currentCutoff;
    float currentQ;
    float currentGain;
    double sampleRate = 0.0;

    JUCE_DECLARE_WEAK_REFERENCEABLE(MMIIRFilter)
};
