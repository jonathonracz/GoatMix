/*
  ==============================================================================

    MMLookAndFeel.cpp
    Created: 28 Oct 2017 9:41:24pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMLookAndFeel.h"
#include "MMParameterSlider.h"
#include <array>

MMLookAndFeel::MMLookAndFeel()
{
    const uint32 colors[] = {
        background,         0xfff7f7f7,
        outline,            0xff000000,
        outlineLight,       0xff979797,

        meterClip,          0xffff0a0a,
        meterGradientTop,   0xffc3fa58,
        meterGradientBottom,0xff0bf864,

        muteButtonOn,       0xff00ffff,
        muteButtonOff,      0xff007f7f,

        sliderForeground,   0xff4a90e2,
        sliderBackground,   0xff606060,
        sliderText,         0xfff7f7f7,

        muteButtonBg,       0xff606060,
    };

    setColorsFromArray(colors, sizeof(colors) / sizeof(uint32));

    const uint32 juceColors[] = {
        Slider::ColourIds::trackColourId, findColour(sliderForeground).getARGB(),
        Slider::ColourIds::textBoxBackgroundColourId, findColour(sliderBackground).getARGB(),
        Slider::ColourIds::textBoxTextColourId, findColour(sliderText).getARGB(),
        Slider::ColourIds::textBoxOutlineColourId, findColour(outline).getARGB(),
        TextButton::ColourIds::textColourOnId, findColour(background).getARGB(),
        TextButton::ColourIds::textColourOffId, findColour(outline).getARGB(),
        Label::ColourIds::outlineColourId, Colours::transparentWhite.getARGB(),
        Label::ColourIds::textColourId, findColour(outline).getARGB(),
        Label::ColourIds::backgroundColourId, Colours::transparentBlack.getARGB(),
    };

    setColorsFromArray(juceColors, sizeof(juceColors) / sizeof(uint32));
}

Label* MMLookAndFeel::createSliderTextBox(Slider& slider)
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

void MMLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
    if (isButtonDown || button.getToggleState())
        g.fillAll(findColour(ColourIds::sliderForeground));
    else
        g.fillAll(findColour(ColourIds::background));

    Path outline;
    outline.addRectangle(button.getLocalBounds());
    g.setColour(findColour(ColourIds::outline));
    g.strokePath(outline, PathStrokeType(borderThickness * 2.0f));
}

void MMLookAndFeel::setColorsFromArray(const uint32* colors, size_t num)
{
    for (size_t i = 0; i < num; i += 2)
        setColour(static_cast<int>(colors[i]), Colour(colors[i + 1]));
}
