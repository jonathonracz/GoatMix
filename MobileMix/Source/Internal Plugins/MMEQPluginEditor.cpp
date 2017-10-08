/*
  ==============================================================================

    MMEQPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMEQPluginEditor.h"

MMEQPluginEditor::MMEQPluginEditor(MMEQPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSliderAttachment = createSliderAttachment(processor.paramEQ->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMEQPluginEditor::~MMEQPluginEditor()
{

}

void MMEQPluginEditor::paint(Graphics& g)
{
    g.setColour(Colours::green);
    g.fillAll();
    g.setColour(Colours::red);
    g.drawRect(10, 10, getWidth() - 20, getHeight() - 20);
}

void MMEQPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
