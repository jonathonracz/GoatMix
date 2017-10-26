/*
  ==============================================================================

    MMLookAndFeel.h
    Created: 24 Oct 2017 2:43:03am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MMParameterSlider.h"

class MMLookAndFeel :
    public LookAndFeel_V4,
    public FFAU::LevelMeter::LookAndFeelMethods
{
public:
    MMLookAndFeel()
    {
        setupDefaultMeterColours();
    }

    ~MMLookAndFeel() {}

    Label* createSliderTextBox(Slider& slider) override
    {
        Label* result = LookAndFeel_V4::createSliderTextBox(slider);
        if (MMParameterSlider* mmSlider = dynamic_cast<MMParameterSlider*>(&slider))
        {
            result->addListener(mmSlider); // So we can intercept the label editor add/remove events.

        }
        return result;
    }

    const float borderThickness = 2.0f;

    #include "ff_meters/ff_meters_LookAndFeelMethods.h" // Dear lord

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMLookAndFeel)
};
