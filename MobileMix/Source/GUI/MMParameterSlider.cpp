/*
  ==============================================================================

    MMParameterSlider.cpp
    Created: 30 Oct 2017 3:46:26pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMParameterSlider.h"
#include "../Core/MobileMixPluginInstance.h"

MMParameterSlider::MMParameterSlider() :
    Slider(Slider::SliderStyle::LinearBar, Slider::TextEntryBoxPosition::TextBoxAbove)
{
    setOpaque(true);
}

void MMParameterSlider::setRepresentedParameter(AudioProcessorParameterWithID* parameter,
        NormalisableRange<float> range)
{
    representedParameter = parameter;
    representedRange = range;
}

void MMParameterSlider::paint(Graphics& g)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());
    g.fillAll(lf.findColour(MMLookAndFeel::ColourIds::sliderBackground));
    Slider::paint(g);
    Path border;
    border.addRectangle(getLocalBounds());
    g.setColour(lf.findColour(MMLookAndFeel::ColourIds::outline));
    g.strokePath(border, PathStrokeType(lf.borderThickness * 2.0f));
}

double MMParameterSlider::getValueFromText(const String &text)
{
    if (representedParameter)
        return representedRange.convertFrom0to1(representedParameter->getValueForText(text));

    return Slider::getValueFromText(text);
}

String MMParameterSlider::getTextFromValue(double value)
{
    if (representedParameter)
    {
        return MobileMixPluginInstance::stripPrefixFromParameterName(representedParameter->name)
        + ": " + representedParameter->getText(representedRange.convertTo0to1(static_cast<float>(value)), 0);
    }

    return Slider::getTextFromValue(value);
}

void MMParameterSlider::editorShown(Label* label, TextEditor& editor)
{
    // We use a text keyboard so we can access the negative symbol.
    editor.setKeyboardType(TextInputTarget::VirtualKeyboardType::textKeyboard);
    editor.setText(String(
        MobileMixPluginInstance::stripPrefixFromParameterName(
            label->getText(false)).getFloatValue()));
}
