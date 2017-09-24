/*
  ==============================================================================

    LinearAudioProcessorModuleEditor.cpp
    Created: 15 Sep 2017 1:28:59pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "LinearAudioProcessorModuleEditor.h"

LinearAudioProcessorModuleEditor::LinearAudioProcessorModuleEditor(LinearAudioProcessorModule& _processor) :
    AudioProcessorEditor(_processor),
    processor(_processor)
{
}

LinearAudioProcessorModuleEditor::~LinearAudioProcessorModuleEditor()
{
}
