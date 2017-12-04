/*
  ==============================================================================

    SimpleMultiLevelMeter.h
    Created: 27 Oct 2017 6:22:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "SimpleLevelMeter.h"
#include "../DSP/MultiWindowedMeter.h"

class SimpleMultiLevelMeter :
    public Component
{
public:
    SimpleMultiLevelMeter() {}
    ~SimpleMultiLevelMeter() {}

    void setSource(MultiWindowedMeter* source)
    {
        jassert(source);
        meters.clear();
        for (int i = 0; i < source->meters.size(); ++i)
        {
            meters.add(new SimpleLevelMeter);
            meters.getLast()->setMinGainDisplayValue(minGainDisplay);
            meters.getLast()->setMaxGainDisplayValue(maxGainDisplay);
            meters.getLast()->setSource(source->meters[i]);
            addAndMakeVisible(meters.getLast());
        }
    }

    void setMinGainDisplayValue(float value)
    {
        minGainDisplay = value;
        for (auto& meter : meters)
            meter->setMinGainDisplayValue(value);
    }

    void setMaxGainDisplayValue(float value)
    {
        maxGainDisplay = value;
        for (auto& meter : meters)
            meter->setMaxGainDisplayValue(value);
    }

    void startAnimating(int hz)
    {
        for (auto& meter : meters)
            meter->startTimerHz(hz);
    }

    void stopAnimating()
    {
        for (auto& meter : meters)
            meter->stopTimer();
    }

private:
    void resized() override
    {
        FlexBox flex;
        for (auto& meter : meters)
            flex.items.add(FlexItem(*meter).withFlex(1.0f));
        flex.performLayout(getLocalBounds());
    }

    OwnedArray<SimpleLevelMeter> meters;
    float minGainDisplay = 0.0f;
    float maxGainDisplay = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleMultiLevelMeter)
};
