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

// From https://forum.juce.com/t/best-way-of-rotating-components/17750/2
void MobileMixPluginInstanceEditor::setVerticalRotatedWithBounds(Component* component, Rectangle<int> verticalBounds, bool clockwise)
{
    float angle = MathConstants<float>::pi / 2.0f;
    if (!clockwise)
        angle *= -1.0f;

    component->setSize(verticalBounds.getHeight(), verticalBounds.getWidth());
    component->setCentrePosition(0, 0);
    component->setTransform(AffineTransform::rotation(angle).translated(verticalBounds.getWidth() / 2.0f, verticalBounds.getHeight() / 2.0f));
}
