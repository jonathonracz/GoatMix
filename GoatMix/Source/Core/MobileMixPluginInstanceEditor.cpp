/*
  ==============================================================================

    MobileMixPluginInstanceEditor.cpp
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginInstanceEditor.h"

MobileMixPluginInstanceEditor::MobileMixPluginInstanceEditor(MobileMixPluginInstance& _processor) :
    processor(_processor)
{
    bypassButtonAttachment = createButtonAttachment(processor.paramBypass, bypassButton);
}

MobileMixPluginInstanceEditor::MMButtonAttachment MobileMixPluginInstanceEditor::createButtonAttachment(AudioProcessorParameterWithID* parameter, Button& buttonToControl)
{
    return MMButtonAttachment(new AudioProcessorValueTreeState::ButtonAttachment(processor.state, parameter->paramID, buttonToControl));
}

MobileMixPluginInstanceEditor::MMComboBoxAttachment MobileMixPluginInstanceEditor::createComboBoxAttachment(AudioProcessorParameterWithID* parameter, ComboBox& comboBoxToControl)
{
    return MMComboBoxAttachment(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.state, parameter->paramID, comboBoxToControl));
}

MobileMixPluginInstanceEditor::MMSliderAttachment MobileMixPluginInstanceEditor::createSliderAttachment(AudioProcessorParameterWithID* parameter, MMParameterSlider& sliderToControl)
{
    sliderToControl.setRepresentedParameter(parameter, processor.state.getParameterRange(parameter->paramID));
    return MMSliderAttachment(new AudioProcessorValueTreeState::SliderAttachment(processor.state, parameter->paramID, sliderToControl));
}

// From https://forum.juce.com/t/best-way-of-rotating-components/17750/2
void MobileMixPluginInstanceEditor::setVerticalRotated(Component* component, bool clockwise)
{
    float angle = MathConstants<float>::pi / 2.0f;
    if (!clockwise)
        angle *= -1.0f;

    Rectangle<int> verticalBounds = component->getBounds();
    component->setSize(verticalBounds.getHeight(), verticalBounds.getWidth());
    component->setCentrePosition(0, 0);
    component->setTransform(AffineTransform::rotation(angle).translated(verticalBounds.getX() + (verticalBounds.getWidth() / 2.0f),
                                                                        verticalBounds.getY() + (verticalBounds.getHeight() / 2.0f)));
}

void MobileMixPluginInstanceEditor::setUpsideDownRotated(Component* component)
{
    float angle = MathConstants<float>::pi;
    Rectangle<int> verticalBounds = component->getBounds();
    component->setCentrePosition(0, 0);
    component->setTransform(AffineTransform::rotation(angle).translated(verticalBounds.getX() + (verticalBounds.getWidth() / 2.0f),
                                                                        verticalBounds.getY() + (verticalBounds.getHeight() / 2.0f)));
}
