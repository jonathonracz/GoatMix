/*
  ==============================================================================

    Goniometer.h
    Created: 29 Oct 2017 7:22:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/RingBuffer.h"

class GoniometerSource;

class Goniometer :
    public Component,
    public Timer
{
public:
    Goniometer();
    ~Goniometer() {}

    void setSource(GoniometerSource* source);
    void setNumPointsInPath(int numPoints);

private:
    void paint(Graphics& g) override;
    void resized() override;
    void timerCallback() override;

    WeakReference<GoniometerSource> source = nullptr;
    Image background;
    Image paths;
    RingBuffer<Point<float>> pathCoordsForDrawing;
    bool wasResized = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Goniometer)
};
