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
    double getValueFromText(const String &text) override
    {
        if (representedParameter)
            return representedParameter->getValueForText(text);

        return Slider::getValueFromText(text);
    }

    String getTextFromValue(double value) override
    {
        if (representedParameter)
            return MobileMixPluginInstance::stripPrefixFromParameterName(representedParameter->name) + ": " + representedParameter->getText(static_cast<float>(value), 0);

        return Slider::getTextFromValue(value);
    }

    void labelTextChanged(Label* labelThatHasChanged) override {}

    void editorShown(Label* label, TextEditor& editor) override
    {
        editor.setText(String(editor.getText().getFloatValue()));
    }

    void editorHidden(Label* label, TextEditor& editor) override
    {
    }

    AudioProcessorParameterWithID* representedParameter = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMParameterSlider)
};
