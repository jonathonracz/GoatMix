/*
  ==============================================================================

    Gain.h
    Created: 11 Sep 2017 8:09:57pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DSPKernel.h"

namespace kernel
{

class Gain :
    public DSPKernel
{
public:
    Gain() : gain(1.0f) {}
    ~Gain() {}

    void setSampleRate(double sampleRate) override
    {
        gain.reset(sampleRate, 0.01);
    }

    void process(float* samples, int numSamples) override
    {
        gain.applyGain(samples, numSamples);
    }

    void setGain(float _gain)
    {
        gain = _gain;
    }

private:
    LinearSmoothedValue<float> gain;
};

}
