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
    gainSliderAttachment = createSliderAttachment(processor.paramReverb, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMReverbPluginEditor::~MMReverbPluginEditor()
{

}

void MMReverbPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
