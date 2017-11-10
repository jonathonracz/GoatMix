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
#include "../DSP/WindowedMeter.h"

class CompressorPreview :
    public Component,
    public Timer
{
public:
    CompressorPreview(Compressor::Parameters::Ptr params, WindowedMeter& meter);
    ~CompressorPreview() {}

private:
    void paint(Graphics& g) override;
    void timerCallback() override;

    Compressor::Parameters::Ptr params = nullptr;
    WindowedMeter& meter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorPreview)
};

