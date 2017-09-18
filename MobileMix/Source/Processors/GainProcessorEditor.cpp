/*
  ==============================================================================

    GainProcessorEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GainProcessorEditor.h"

GainProcessorEditor::GainProcessorEditor(SubProcessor& processor) :
    SubProcessorEditor(processor)
{
}

GainProcessorEditor::~GainProcessorEditor()
{

}

void GainProcessorEditor::parameterChanged(const String &parameterID, float newValue)
{

}

void GainProcessorEditor::paint(Graphics& g)
{
    g.setColour(Colours::green);
    g.fillAll();
}
