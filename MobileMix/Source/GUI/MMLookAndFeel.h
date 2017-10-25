/*
  ==============================================================================

    MMLookAndFeel.h
    Created: 24 Oct 2017 2:43:03am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

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

    const float borderThickness = 2.0f;

    #include "ff_meters/ff_meters_LookAndFeelMethods.h" // Dear lord
};
