/*
  ==============================================================================

    MMDistortionPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMDistortionPluginEditor.h"

MMDistortionPluginEditor::MMDistortionPluginEditor(MMDistortionPlugin& processor) :
    MobileMixPluginInstanceEditor(processor),
    preview(processor.distortion.params)
{
    gainSliderAttachment = createSliderAttachment(processor.paramDistortion, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMDistortionPluginEditor::~MMDistortionPluginEditor()
{

}

void MMDistortionPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
