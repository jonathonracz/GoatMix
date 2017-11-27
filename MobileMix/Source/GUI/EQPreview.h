/*
  ==============================================================================

    EQPreview.h
    Created: 19 Nov 2017 9:48:55pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "../DSP/RingBuffer.h"
#include "../External/readerwriterqueue/readerwriterqueue.h"

class EQPreview :
    public Component
{
public:
    EQPreview()
    {
    }

    ~EQPreview() {}

private:
    void resized() override
    {

    }

    void paint(Graphics& g) override
    {
    }
};
