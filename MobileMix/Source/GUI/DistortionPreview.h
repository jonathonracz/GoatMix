/*
  ==============================================================================

    DistortionPreview.h
    Created: 30 Oct 2017 5:22:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/DistortionChain.h"

class DistortionPreview :
    public Component
{
public:
    DistortionPreview() {}
    ~DistortionPreview() {}

private:
    void paint(Graphics& g) override;

    DistortionChain previewDSP;

};
