/*
  ==============================================================================

    Overdrive.h
    Created: 2 Nov 2017 2:21:08pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Gain.h"

/** Based on the overdrive from the DSPDemo project. */
class Overdrive :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        float gainUp = 1.0f;
        float gainDown = 1.0f;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    Overdrive() = default;
    ~Overdrive() = default;

    void prepare(const dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;

        auto& bias = overdrive.get<1>();
        bias.setBias(0.4f);

        auto& wavShaper = overdrive.get<2>();
        wavShaper.functionToUse = std::tanh;

        auto& dcFilter = overdrive.get<3>();
        dcFilter.state = dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, 5.0);

        updateParameters();

        overdrive.prepare(spec);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        updateParameters();
        overdrive.process(context);
    }

    void reset() override
    {
        overdrive.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        auto& gainUp = overdrive.get<0>();
        gainUp.params->gain = params->gainUp;

        auto& gainDown = overdrive.get<4>();
        gainDown.params->gain = params->gainDown;
    }

    dsp::ProcessorChain<
        Gain,
        dsp::Bias<float>,
        dsp::WaveShaper<float>,
        dsp::ProcessorDuplicator<
            dsp::IIR::Filter<float>,
            dsp::IIR::Coefficients<float>>,
        Gain> overdrive;

    double sampleRate = 0;
};
