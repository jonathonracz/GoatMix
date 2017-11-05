/*
  ==============================================================================

    MMParameterSlider.h
    Created: 24 Oct 2017 7:16:22pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MMLookAndFeel.h"

class MMParameterSlider :
    public Slider,
    public Label::Listener
{
public:
    MMParameterSlider();
    ~MMParameterSlider() {}

    void setRepresentedParameter(AudioProcessorParameterWithID* parameter,
            NormalisableRange<float> range);

private:
    void paint(Graphics& g) override;
    double getValueFromText(const String &text) override;
    String getTextFromValue(double value) override;

    void labelTextChanged(Label* labelThatHasChanged) override {}
    void editorShown(Label* label, TextEditor& editor) override;

    AudioProcessorParameterWithID* representedParameter = nullptr;
    NormalisableRange<float> representedRange;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMParameterSlider)
};
