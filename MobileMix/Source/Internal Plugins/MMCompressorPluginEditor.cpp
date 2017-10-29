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
    gainSliderAttachment = createSliderAttachment(processor.paramCompressor->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMCompressorPluginEditor::~MMCompressorPluginEditor()
{

}

void MMCompressorPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
