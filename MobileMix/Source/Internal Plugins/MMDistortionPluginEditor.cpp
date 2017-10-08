/*
  ==============================================================================

    MMDistortionPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMDistortionPluginEditor.h"

MMDistortionPluginEditor::MMDistortionPluginEditor(MMDistortionPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSliderAttachment = createSliderAttachment(processor.paramDistortion->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMDistortionPluginEditor::~MMDistortionPluginEditor()
{

}

void MMDistortionPluginEditor::paint(Graphics& g)
{
    g.setColour(Colours::green);
    g.fillAll();
    g.setColour(Colours::red);
    g.drawRect(10, 10, getWidth() - 20, getHeight() - 20);
}

void MMDistortionPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
