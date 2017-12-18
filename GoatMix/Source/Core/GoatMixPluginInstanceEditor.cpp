/*
  ==============================================================================

    GoatMixPluginInstanceEditor.cpp
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GoatMixPluginInstanceEditor.h"

GoatMixPluginInstanceEditor::GoatMixPluginInstanceEditor(GoatMixPluginInstance& _processor) :
    processor(_processor)
{
    bypassButtonAttachment = createButtonAttachment(processor.paramBypass, bypassButton);
}

GoatMixPluginInstanceEditor::GMButtonAttachment GoatMixPluginInstanceEditor::createButtonAttachment(AudioProcessorParameterWithID* parameter, Button& buttonToControl)
{
    return GMButtonAttachment(new AudioProcessorValueTreeState::ButtonAttachment(processor.state, parameter->paramID, buttonToControl));
}

GoatMixPluginInstanceEditor::GMComboBoxAttachment GoatMixPluginInstanceEditor::createComboBoxAttachment(AudioProcessorParameterWithID* parameter, ComboBox& comboBoxToControl)
{
    return GMComboBoxAttachment(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.state, parameter->paramID, comboBoxToControl));
}

GoatMixPluginInstanceEditor::GMSliderAttachment GoatMixPluginInstanceEditor::createSliderAttachment(AudioProcessorParameterWithID* parameter, GMParameterSlider& sliderToControl)
{
    sliderToControl.setRepresentedParameter(parameter, processor.state.getParameterRange(parameter->paramID));
    return GMSliderAttachment(new AudioProcessorValueTreeState::SliderAttachment(processor.state, parameter->paramID, sliderToControl));
}

// From https://forum.juce.com/t/best-way-of-rotating-components/17750/2
void GoatMixPluginInstanceEditor::setVerticalRotated(Component* component, bool clockwise)
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

void GoatMixPluginInstanceEditor::setUpsideDownRotated(Component* component)
{
    float angle = MathConstants<float>::pi;
    Rectangle<int> verticalBounds = component->getBounds();
    component->setCentrePosition(0, 0);
    component->setTransform(AffineTransform::rotation(angle).translated(verticalBounds.getX() + (verticalBounds.getWidth() / 2.0f),
                                                                        verticalBounds.getY() + (verticalBounds.getHeight() / 2.0f)));
}
