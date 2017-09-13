/*
  ==============================================================================

    BufferSizeAdaptor.h
    Created: 13 Sep 2017 12:05:17am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

namespace kernel
{

class BufferSizeAdaptor
{
public:
    BufferSizeAdaptor() {}
    virtual ~BufferSizeAdaptor() {}

    virtual void setSampleRate(double sampleRate)
    {

    }

    virtual void process(float* samples, int numSamples)
    {

    }
};

}
