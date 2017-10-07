/*
  ==============================================================================

    MMGainPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMGainPluginEditor.h"

MMGainPluginEditor::MMGainPluginEditor(MMGainPlugin& processor) :
    MobileMixPluginEditor(processor)
{
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSliderAttachment = createSliderAttachment(processor.paramGain->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMGainPluginEditor::~MMGainPluginEditor()
{

}

void MMGainPluginEditor::paint(Graphics& g)
{
    g.setColour(Colours::green);
    g.fillAll();
}

void MMGainPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight());
}
