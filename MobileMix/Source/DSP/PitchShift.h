/*
  ==============================================================================

    PitchShift.h
    Created: 11 Sep 2017 11:41:14pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DSPKernel.h"
#include "Math.h"

namespace kernel
{

class PitchShift :
    public DSPKernel
{
public:
    PitchShift() {}
    ~PitchShift() {}

    void setSampleRate(double sampleRate) override
    {
    }

    void process(float* samples, int numSamples) override
    {
    }
};

}
