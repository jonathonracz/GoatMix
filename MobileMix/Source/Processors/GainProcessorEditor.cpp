/*
  ==============================================================================

    GainProcessorEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GainProcessorEditor.h"

GainProcessorEditor::GainProcessorEditor(GainProcessor& processor) :
    AudioProcessorEditor(processor)
{
}

GainProcessorEditor::~GainProcessorEditor()
{

}

void GainProcessorEditor::paint(Graphics& g)
{
    g.setColour(Colours::green);
    g.fillAll();
}
