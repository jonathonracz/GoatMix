/*
  ==============================================================================

    MMLookAndFeel.h
    Created: 24 Oct 2017 2:43:03am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../External/CenteredEditableLabel/CenteredEditableLabel.h"

class MMLookAndFeel :
    public LookAndFeel_V4
{
public:
    enum ColourIds
    {
        background          = 0x67740000,
        outline             = 0x67740001,
        outlineLight        = 0x67740002,

        meterClip           = 0x67740003,
        meterGradientTop    = 0x67740004,
        meterGradientBottom = 0x67740005,

        muteButtonOn        = 0x67740006,
        muteButtonOff       = 0x67740007,

        sliderForeground    = 0x67740008,
        sliderBackground    = 0x67740009,
        sliderText          = 0x67740010,

        muteButtonBg        = 0x67740011,
    };

    MMLookAndFeel();
    ~MMLookAndFeel() {}

    FlexBox getFlexBox() const
    {
        return FlexBox(FlexBox::Direction::row,
                       FlexBox::Wrap::noWrap,
                       FlexBox::AlignContent::center,
                       FlexBox::AlignItems::stretch,
                       FlexBox::JustifyContent::center);
    }

    template<class FlexRecipient>
    FlexItem getFlexItem(const Component& parent, FlexRecipient& recipient) const
    {
        return FlexItem(recipient).withMargin(std::max(parent.getWidth(), parent.getHeight()) * 0.025f).withFlex(1.0f);
    }

    Label* createSliderTextBox(Slider& slider) override;
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;

    const float borderThickness = 2.0f;

private:
    void setColorsFromArray(const uint32* colors, size_t num);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMLookAndFeel)
};
