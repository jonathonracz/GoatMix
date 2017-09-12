/*
  ==============================================================================

    DSPKernel.h
    Created: 11 Sep 2017 8:06:00pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

namespace kernel
{

class DSPKernel
{
public:
    DSPKernel() {}
    virtual ~DSPKernel() {}

    virtual void setSampleRate(double sampleRate) = 0;
    virtual void process(float* samples, int numSamples) = 0;
};

}
