/*
  ==============================================================================

    MobileMixPluginInstanceEditor.cpp
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginInstanceEditor.h"

MobileMixPluginInstanceEditor::MobileMixPluginInstanceEditor(MobileMixPluginInstance& _processor) :
    AudioProcessorEditor(_processor),
    processor(_processor)
{
    bypassButtonAttachment = createButtonAttachment(processor.paramBypass->paramID, bypassButton);
}

MobileMixPluginInstanceEditor::MMButtonAttachment MobileMixPluginInstanceEditor::createButtonAttachment(String parameterID, Button& buttonToControl)
{
    return MMButtonAttachment(new AudioProcessorValueTreeState::ButtonAttachment(processor.state, parameterID, buttonToControl));
}

MobileMixPluginInstanceEditor::MMComboBoxAttachment MobileMixPluginInstanceEditor::createComboBoxAttachment(String parameterID, ComboBox& comboBoxToControl)
{
    return MMComboBoxAttachment(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.state, parameterID, comboBoxToControl));
}

MobileMixPluginInstanceEditor::MMSliderAttachment MobileMixPluginInstanceEditor::createSliderAttachment(String parameterID, MMParameterSlider& sliderToControl)
{
    sliderToControl.setRepresentedParameter(processor.state.getParameter(parameterID));
    return MMSliderAttachment(new AudioProcessorValueTreeState::SliderAttachment(processor.state, parameterID, sliderToControl));
}
