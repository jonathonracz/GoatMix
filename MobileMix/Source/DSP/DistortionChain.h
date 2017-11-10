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
        float overdriveGainUp = 1.0f;
        float overdriveGainDown = 1.0f;

        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    DistortionChain() = default;
    ~DistortionChain() = default;

    void prepare(const dsp::ProcessSpec& spec) override
    {
        downsample.prepare(spec);
        depth.prepare(spec);
        overdrive.prepare(spec);
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        updateParameters();
        downsample.process(context);
        depth.process(context);
        overdrive.process(context);
    }

    void reset() override
    {
        downsample.reset();
        depth.reset();
        overdrive.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        // Trickle parameters down.
        downsample.params->samplesToRepeat = params->samplesToRepeat;
        depth.params->bitDepth = params->bitDepth;
        overdrive.params->gainUp = params->overdriveGainUp;
        overdrive.params->gainDown = params->overdriveGainDown;
    }

    SampleRepeat downsample;
    AmplitudeQuantize depth;
    Overdrive overdrive;
};
