/*
  ==============================================================================

    SubProcessorEditor.h
    Created: 15 Sep 2017 1:28:59pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SubProcessor.h"

class SubProcessorEditor :
    public AudioProcessorEditor,
    public AudioProcessorValueTreeState::Listener
{
public:
    SubProcessorEditor(SubProcessor& processor);
    virtual ~SubProcessorEditor();

protected:
    SubProcessor& processor;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SubProcessorEditor)
};
