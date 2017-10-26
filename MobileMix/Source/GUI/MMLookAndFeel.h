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
#include "../External/CenteredEditableLabel/CenteredEditableLabel.h"

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
        if (MMParameterSlider* mmSlider = dynamic_cast<MMParameterSlider*>(&slider))
        {
            Label* l = new CenteredEditableLabel();

            // Duplicate behavior from LookAndFeel_V2 through gross copy/paste...
            l->setJustificationType(Justification::centred);
            l->setKeyboardType(TextInputTarget::decimalKeyboard);

            l->setColour(Label::textColourId, slider.findColour(Slider::textBoxTextColourId));
            l->setColour(Label::backgroundColourId,
                         (slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                         ? Colours::transparentBlack
                         : slider.findColour(Slider::textBoxBackgroundColourId));
            l->setColour(Label::outlineColourId, slider.findColour(Slider::textBoxOutlineColourId));
            l->setColour(TextEditor::textColourId, slider.findColour(Slider::textBoxTextColourId));
            l->setColour(TextEditor::backgroundColourId,
                         slider.findColour (Slider::textBoxBackgroundColourId)
                         .withAlpha((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                                    ? 0.7f : 1.0f));
            l->setColour(TextEditor::outlineColourId, slider.findColour(Slider::textBoxOutlineColourId));
            l->setColour(TextEditor::highlightColourId, slider.findColour(Slider::textBoxHighlightColourId));

            l->addListener(mmSlider); // So we can intercept the label editor add/remove events.
            return l;
        }

        return LookAndFeel_V4::createSliderTextBox(slider);
    }

    const float borderThickness = 2.0f;

    #include "ff_meters/ff_meters_LookAndFeelMethods.h" // Dear lord

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMLookAndFeel)
};
