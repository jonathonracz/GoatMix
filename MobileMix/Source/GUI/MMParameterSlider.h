/*
  ==============================================================================

    MMParameterSlider.h
    Created: 24 Oct 2017 7:16:22pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MMParameterSlider :
    public Slider
{
public:
    MMParameterSlider() :
        Slider(Slider::SliderStyle::LinearBar, Slider::TextEntryBoxPosition::TextBoxAbove)
    {
    }

    ~MMParameterSlider() {}

};
