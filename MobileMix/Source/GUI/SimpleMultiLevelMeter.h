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
#include "../DSP/WindowedMeter.h"
#include <list>

class SimpleMultiLevelMeter :
    public Component
{
public:
    SimpleMultiLevelMeter() {}
    ~SimpleMultiLevelMeter() {}

    void setSource(FFAU::LevelMeterSource* source)
    {
        setSourceInternal(source);
    }

    void setSource(WindowedMeter* source)
    {
        setSourceInternal(source);
    }

    void setMinGainDisplayValue(float value)
    {
        minGainDisplay = value;
        for (SimpleLevelMeter& meter : meters)
            meter.setMinGainDisplayValue(value);
    }

    void setMaxGainDisplayValue(float value)
    {
        maxGainDisplay = value;
        for (SimpleLevelMeter& meter : meters)
            meter.setMaxGainDisplayValue(value);
    }

    void startAnimating(int hz)
    {
        for (SimpleLevelMeter& meter : meters)
            meter.startTimerHz(hz);
    }

    void stopAnimating()
    {
        for (SimpleLevelMeter& meter : meters)
            meter.stopTimer();
    }

private:
    void resized() override
    {
        FlexBox flex;
        for (SimpleLevelMeter& meter : meters)
            flex.items.add(FlexItem(meter).withFlex(1.0f));
        flex.performLayout(getLocalBounds());
    }

    template<class SourceType>
    void setSourceInternal(SourceType source)
    {
        jassert(source);
        meters.resize(source->getNumChannels());
        int index = 0;
        for (auto meter = meters.begin(); meter != meters.end(); ++meter)
        {
            meter->setSource(source);
            meter->setChannel(index);
            meter->setMinGainDisplayValue(minGainDisplay);
            meter->setMaxGainDisplayValue(maxGainDisplay);
            addAndMakeVisible(*meter);
            index++;
        }
    }

    std::list<SimpleLevelMeter> meters;
    float minGainDisplay = 0.0f;
    float maxGainDisplay = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleMultiLevelMeter)
};
