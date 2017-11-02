/*
  ==============================================================================

    Pan.h
    Created: 1 Nov 2017 2:12:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class Pan :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        // In degrees, -45.0 <= panAngle <= 45.0.
        float pan = 0.0f;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    Pan() :
        sinApprox(std::function<float(float)>(&std::sinf), -MathConstants<float>::pi / 4.0f, MathConstants<float>::pi / 4.0f, 90),
        cosApprox(std::function<float(float)>(&std::cosf), -MathConstants<float>::pi / 4.0f, MathConstants<float>::pi / 4.0f, 90)
    {
    }

    ~Pan() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        jassert(spec.numChannels >= 2);
        sampleRate = spec.sampleRate;
        reset();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();

        // Simple implementation of pan based on standard 90-degree speaker
        // configuration.
        const float* readL = context.getInputBlock().getChannelPointer(0);
        const float* readR = context.getInputBlock().getChannelPointer(1);
        float* writeL = context.getOutputBlock().getChannelPointer(0);
        float* writeR = context.getOutputBlock().getChannelPointer(1);
        for (int i = 0; i < context.getInputBlock().getNumSamples(); ++i)
        {
            // Notice the pan degree is negative - this is to flip the intuitive
            // degree parameter so positive is left, negative is right (like a
            // 1-dimensional number line).
            float theta = -panSmooth.getNextValue() * (MathConstants<float>::pi / 180.0f);
            float resultL = (cosApprox(theta) * readL[i]) + (sinApprox(theta) * readR[i]);
            float resultR = (-sinApprox(theta) * readL[i]) + (cosApprox(theta) * readR[i]);
            writeL[i] = resultL;
            writeR[i] = resultR;
        }
    }

    void reset() noexcept override
    {
        panSmooth.reset(sampleRate, durationInSeconds);
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        if (panSmooth.getTargetValue() != params->pan)
            panSmooth.setValue(params->pan);
    }

    LinearSmoothedValue<float> panSmooth;
    dsp::LookupTableTransform<float> sinApprox;
    dsp::LookupTableTransform<float> cosApprox;

    double sampleRate = 0.0;
    double durationInSeconds = 0.1;
};
