/*
  ==============================================================================

    GMPluginInstanceEditor.cpp
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMPluginInstanceEditor.h"

GMPluginInstanceEditor::GMPluginInstanceEditor(GMPluginInstance& _processor) :
    processor(_processor)
{
    bypassButtonAttachment = createButtonAttachment(processor.paramBypass, bypassButton);
}

GMPluginInstanceEditor::GMButtonAttachment GMPluginInstanceEditor::createButtonAttachment(AudioProcessorParameterWithID* parameter, Button& buttonToControl)
{
    return GMButtonAttachment(new AudioProcessorValueTreeState::ButtonAttachment(processor.state, parameter->paramID, buttonToControl));
}

GMPluginInstanceEditor::GMComboBoxAttachment GMPluginInstanceEditor::createComboBoxAttachment(AudioProcessorParameterWithID* parameter, ComboBox& comboBoxToControl)
{
    return GMComboBoxAttachment(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.state, parameter->paramID, comboBoxToControl));
}

GMPluginInstanceEditor::GMSliderAttachment GMPluginInstanceEditor::createSliderAttachment(AudioProcessorParameterWithID* parameter, GMParameterSlider& sliderToControl)
{
    sliderToControl.setRepresentedParameter(parameter, processor.state.getParameterRange(parameter->paramID));
    return GMSliderAttachment(new AudioProcessorValueTreeState::SliderAttachment(processor.state, parameter->paramID, sliderToControl));
}

// From https://forum.juce.com/t/best-way-of-rotating-components/17750/2
void GMPluginInstanceEditor::setVerticalRotated(Component* component, bool clockwise)
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

void GMPluginInstanceEditor::setUpsideDownRotated(Component* component)
{
    float angle = MathConstants<float>::pi;
    Rectangle<int> verticalBounds = component->getBounds();
    component->setCentrePosition(0, 0);
    component->setTransform(AffineTransform::rotation(angle).translated(verticalBounds.getX() + (verticalBounds.getWidth() / 2.0f),
                                                                        verticalBounds.getY() + (verticalBounds.getHeight() / 2.0f)));
}
