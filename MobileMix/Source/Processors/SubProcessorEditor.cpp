/*
  ==============================================================================

    SubProcessorEditor.cpp
    Created: 15 Sep 2017 1:28:59pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "SubProcessorEditor.h"

SubProcessorEditor::SubProcessorEditor(SubProcessor& _processor) :
    AudioProcessorEditor(_processor),
    processor(_processor)
{
}

SubProcessorEditor::~SubProcessorEditor()
{
}
