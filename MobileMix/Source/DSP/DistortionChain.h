/*
  ==============================================================================

    DistortionChain.h
    Created: 3 Nov 2017 2:06:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "SampleRepeat.h"
#include "AmplitudeQuantize.h"
#include "Overdrive.h"

/** Class containing our full distortion chain, to make it easier to have in
    multiple places (read: in plugin code, and editor code for preview).
*/
class DistortionChain :
    dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        size_t samplesToRepeat = 0;
        size_t bitDepth = 32;
        float overDriveGainUp = 1.0f;
        float overDriveGainDown = 1.0f;

        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    DistortionChain() = default;
    ~DistortionChain() = default;

    void prepare(const dsp::ProcessSpec& spec) override
    {
        updateParameters();
        chain.prepare(spec);
    }

    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        updateParameters();
        chain.process(context);
    }

    void reset() override
    {
        chain.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        // Trickle parameters down.
        chain.get<0>().params->samplesToRepeat = params->samplesToRepeat;
        chain.get<1>().params->bitDepth = params->bitDepth;
        chain.get<2>().params->gainUp = params->overDriveGainUp;
        chain.get<2>().params->gainDown = params->overDriveGainDown;
    }

    dsp::ProcessorChain<
        SampleRepeat,
        AmplitudeQuantize,
        Overdrive> chain;
};
