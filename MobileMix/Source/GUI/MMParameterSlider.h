/*
  ==============================================================================

    MMParameterSlider.h
    Created: 24 Oct 2017 7:16:22pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/MobileMixPluginInstance.h"
#include "MMLookAndFeel.h"

class MMParameterSlider :
    public Slider,
    public Label::Listener
{
public:
    MMParameterSlider() :
        Slider(Slider::SliderStyle::LinearBar, Slider::TextEntryBoxPosition::TextBoxAbove)
    {
    }

    ~MMParameterSlider() {}

    void setRepresentedParameter(AudioProcessorParameterWithID* parameter)
    {
        representedParameter = parameter;
    }

private:
    void paint(Graphics& g) override
    {
        MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());
        g.fillAll(lf.findColour(MMLookAndFeel::ColourIds::sliderBackground));
        Slider::paint(g);
        Path border;
        border.addRectangle(getLocalBounds());
        g.setColour(lf.findColour(MMLookAndFeel::ColourIds::outline));
        g.strokePath(border, PathStrokeType(lf.borderThickness * 2.0f));
    }

    double getValueFromText(const String &text) override
    {
        if (representedParameter)
            return representedParameter->getValueForText(text);

        return Slider::getValueFromText(text);
    }

    String getTextFromValue(double value) override
    {
        if (representedParameter)
            return MobileMixPluginInstance::stripPrefixFromParameterName(representedParameter->name)
                + ": " + representedParameter->getText(static_cast<float>(value), 0);

        return Slider::getTextFromValue(value);
    }

    void labelTextChanged(Label* labelThatHasChanged) override {}

    void editorShown(Label* label, TextEditor& editor) override
    {
        editor.setText(String(
            MobileMixPluginInstance::stripPrefixFromParameterName(
                label->getText(false)).getFloatValue()));
    }

    /*
    void editorHidden(Label* label, TextEditor& editor) override
    {
    }
     */

    AudioProcessorParameterWithID* representedParameter = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMParameterSlider)
};
