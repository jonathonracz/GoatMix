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
    gainSliderAttachment = createSliderAttachment(processor.paramEQ->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMEQPluginEditor::~MMEQPluginEditor()
{

}

void MMEQPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
