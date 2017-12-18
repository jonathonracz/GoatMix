/*
  ==============================================================================

    GMIIRFilter.h
    Created: 3 Nov 2017 2:29:36am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "SPSCAtomic.h"

class GMIIRFilter :
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

        FilterMode mode = lowPass;
        float cutoff = 1000.0f;
        float q = 1.0f;
        float gain = 1.0f; // Has no effect for low and high pass filters!
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    GMIIRFilter() = default;
    ~GMIIRFilter() = default;

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

    dsp::IIR::Coefficients<float>::Ptr getCoefficients() const noexcept
    {
        return currentCoefficients.get().getCoefficients();
    }

    Parameters::Ptr params = new Parameters;

private:
    class ThreadSafeCoefficients
    {
    public:
        // Call from audio thread.
        ThreadSafeCoefficients(dsp::IIR::Coefficients<float>::Ptr coefficients) noexcept
        {
            jassert(static_cast<size_t>(coefficients->coefficients.size()) <= coeffs.size());
            numCoeffs = std::min(static_cast<size_t>(coefficients->coefficients.size()), coeffs.size());
            std::memcpy(coeffs.data(), coefficients->getRawCoefficients(), numCoeffs);
        }

        // Call from UI thread.
        dsp::IIR::Coefficients<float>::Ptr getCoefficients() const noexcept
        {
            dsp::IIR::Coefficients<float>::Ptr ret(new dsp::IIR::Coefficients<float>);
            ret->coefficients = Array<float>(coeffs.data(), static_cast<int>(numCoeffs));
            return ret;
        }

    private:
        std::array<float, 5> coeffs;
        size_t numCoeffs;
    };

    void updateParameters()
    {
        Parameters::FilterMode newMode = params->mode;
        float newCutoff = params->cutoff;
        float newQ = params->q;
        float newGain = params->gain;

        // If a param changed, regenerate coefficients.
        if (newMode != currentMode ||
            newCutoff != currentCutoff ||
            newQ != currentQ ||
            newGain != currentGain)
        {
            switch(newMode)
            {
                case Parameters::FilterMode::highPass:
                {
                    *iir.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, newCutoff, newQ);
                    break;
                }
                case Parameters::FilterMode::highShelf:
                {
                    *iir.state = *dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, newCutoff, newQ, newGain);
                    break;
                }
                case Parameters::FilterMode::peak:
                {
                    *iir.state = *dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, newCutoff, newQ, newGain);
                    break;
                }
                case Parameters::FilterMode::lowShelf:
                {
                    *iir.state = *dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, newCutoff, newQ, newGain);
                    break;
                }
                case Parameters::FilterMode::lowPass:
                {
                    *iir.state = *dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, newCutoff, newQ);
                    break;
                }
                default: jassertfalse;

                currentMode = newMode;
                currentCutoff = newCutoff;
                currentQ = newQ;
                currentGain = newGain;

                // Copy coefficients to a location accessible by the GUI in a
                // threadsafe way.
                currentCoefficients = ThreadSafeCoefficients(iir.state);
            }
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

    SPSCAtomic<ThreadSafeCoefficients> currentCoefficients;

    JUCE_DECLARE_WEAK_REFERENCEABLE(GMIIRFilter)
};
