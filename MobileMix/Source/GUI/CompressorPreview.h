/*
  ==============================================================================

    CompressorPreview.h
    Created: 3 Nov 2017 1:40:43am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/Compressor.h"

class CompressorPreview :
    public Component,
    public Timer
{
public:
    CompressorPreview(Compressor::Parameters::Ptr params);
    ~CompressorPreview() {}

private:
    void paint(Graphics& g) override;
    void timerCallback() override;

    Compressor::Parameters::Ptr params = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorPreview)
};

