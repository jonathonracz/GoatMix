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
#include <list>

class SimpleMultiLevelMeter :
    public Component
{
public:
    SimpleMultiLevelMeter() {}
    ~SimpleMultiLevelMeter() {}

    void setSource(FFAU::LevelMeterSource* source)
    {
        jassert(source);
        float currMinGain = 0.0f;
        float currMaxGain = 1.0f;
        if (meters.size() > 0)
        {
            currMinGain = meters.front().getMinGainDisplayValue();
            currMaxGain = meters.front().getMaxGainDisplayValue();
        }

        meters.resize(source->getNumChannels());
        for (SimpleLevelMeter& meter : meters)
        {
            meter.setSource(source);
            meter.setMinGainDisplayValue(currMinGain);
            meter.setMaxGainDisplayValue(currMaxGain);
            addAndMakeVisible(meter);
        }
    }

    void setMinGainDisplayValue(float value)
    {
        for (SimpleLevelMeter& meter : meters)
            meter.setMinGainDisplayValue(value);
    }

    void setMaxGainDisplayValue(float value)
    {
        for (SimpleLevelMeter& meter : meters)
            meter.setMaxGainDisplayValue(value);
    }

private:
    void resized() override
    {
        FlexBox flex;
        for (SimpleLevelMeter& meter : meters)
            flex.items.add(FlexItem(meter).withFlex(1.0f));
        flex.performLayout(getLocalBounds());
    }

    std::list<SimpleLevelMeter> meters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleMultiLevelMeter)
};
