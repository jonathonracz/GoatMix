/*
  ==============================================================================

    MMReverbPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMReverbPluginEditor.h"

MMReverbPluginEditor::MMReverbPluginEditor(MMReverbPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSliderAttachment = createSliderAttachment(processor.paramReverb->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMReverbPluginEditor::~MMReverbPluginEditor()
{

}

void MMReverbPluginEditor::paint(Graphics& g)
{
    g.setColour(Colours::red);
    g.fillAll();
    g.setColour(Colours::blue);
    g.drawRect(10, 10, getWidth() - 20, getHeight() - 20);
}

void MMReverbPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
