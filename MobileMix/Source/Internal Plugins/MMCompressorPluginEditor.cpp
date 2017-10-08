/*
  ==============================================================================

    MMCompressorPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMCompressorPluginEditor.h"

MMCompressorPluginEditor::MMCompressorPluginEditor(MMCompressorPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSliderAttachment = createSliderAttachment(processor.paramCompressor->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMCompressorPluginEditor::~MMCompressorPluginEditor()
{

}

void MMCompressorPluginEditor::paint(Graphics& g)
{
    g.setColour(Colours::blue);
    g.fillAll();
    g.setColour(Colours::green);
    g.drawRect(10, 10, getWidth() - 20, getHeight() - 20);
}

void MMCompressorPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
