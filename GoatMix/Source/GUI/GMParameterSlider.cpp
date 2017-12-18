/*
  ==============================================================================

    GMParameterSlider.cpp
    Created: 30 Oct 2017 3:46:26pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMParameterSlider.h"
#include "../Core/GoatMixPluginInstance.h"

GMParameterSlider::GMParameterSlider() :
    Slider(Slider::SliderStyle::LinearBar, Slider::TextEntryBoxPosition::TextBoxAbove)
{
    setOpaque(true);
}

void GMParameterSlider::setRepresentedParameter(AudioProcessorParameterWithID* parameter,
        NormalisableRange<float> range)
{
    representedParameter = parameter;
    representedRange = range;
}

void GMParameterSlider::paint(Graphics& g)
{
    GMLookAndFeel& lf = static_cast<GMLookAndFeel&>(getLookAndFeel());
    g.fillAll(lf.findColour(GMLookAndFeel::ColourIds::sliderBackground));
    Slider::paint(g);
    Path border;
    border.addRectangle(getLocalBounds());
    g.setColour(lf.findColour(GMLookAndFeel::ColourIds::outline));
    g.strokePath(border, PathStrokeType(lf.borderThickness * 2.0f));
}

double GMParameterSlider::getValueFromText(const String &text)
{
    if (representedParameter)
        return representedRange.convertFrom0to1(representedParameter->getValueForText(text));

    return Slider::getValueFromText(text);
}

String GMParameterSlider::getTextFromValue(double value)
{
    if (representedParameter)
    {
        return GoatMixPluginInstance::stripPrefixFromParameterName(representedParameter->name)
            + ": " + representedParameter->getText(representedRange.convertTo0to1(static_cast<float>(value)), 0);
    }

    return Slider::getTextFromValue(value);
}

void GMParameterSlider::editorShown(Label* label, TextEditor& editor)
{
    // We use a text keyboard so we can access the negative symbol.
    editor.setText(String(
        GoatMixPluginInstance::stripPrefixFromParameterName(
            label->getText(false)).getFloatValue()));
}
