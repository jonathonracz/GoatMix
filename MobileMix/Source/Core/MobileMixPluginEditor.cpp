/*
  ==============================================================================

    MobileMixPluginEditor.cpp
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginEditor.h"

MobileMixPluginEditor::MobileMixPluginEditor(MobileMixPluginInstance& _processor) :
    AudioProcessorEditor(_processor),
    processor(_processor)
{
    bypassButtonAttachment = createButtonAttachment(processor.paramBypass->paramID, bypassButton);
}

MobileMixPluginEditor::MMButtonAttachment MobileMixPluginEditor::createButtonAttachment(String parameterID, Button& buttonToControl)
{
    return MMButtonAttachment(new AudioProcessorValueTreeState::ButtonAttachment(processor.state, parameterID, buttonToControl));
}

MobileMixPluginEditor::MMComboBoxAttachment MobileMixPluginEditor::createComboBoxAttachment(String parameterID, ComboBox& comboBoxToControl)
{
    return MMComboBoxAttachment(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.state, parameterID, comboBoxToControl));
}

MobileMixPluginEditor::MMSliderAttachment MobileMixPluginEditor::createSliderAttachment(String parameterID, Slider& sliderToControl)
{
    return MMSliderAttachment(new AudioProcessorValueTreeState::SliderAttachment(processor.state, parameterID, sliderToControl));
}
