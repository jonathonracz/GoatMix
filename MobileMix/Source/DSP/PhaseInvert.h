/*
  ==============================================================================

    PhaseInvert.h
    Created: 11 Sep 2017 9:42:01pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "Gain.h"

namespace kernel
{

class PhaseInvert :
    public DSPKernel
{
public:
    PhaseInvert() {}
    ~PhaseInvert() {}

    void setSampleRate(double sampleRate) override
    {
        gain.setSampleRate(sampleRate);
    }

    void process(float* samples, int numSamples) override
    {
        gain.process(samples, numSamples);
    }

    void setInvertPhase(bool invert)
    {
        if (invert)
        {
            gain.setGain(-1.0f);
        }
        else
        {
            gain.setGain(1.0f);
        }
    }
    
private:
    Gain gain;
};
    
}
