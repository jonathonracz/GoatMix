/*
  ==============================================================================

    LinearAudioProcessorModuleEditor.h
    Created: 15 Sep 2017 1:28:59pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LinearAudioProcessorModule.h"

class LinearAudioProcessorModuleEditor :
    public AudioProcessorEditor,
    public AudioProcessorValueTreeState::Listener
{
public:
    LinearAudioProcessorModuleEditor(LinearAudioProcessorModule& processor);
    virtual ~LinearAudioProcessorModuleEditor();

protected:
    LinearAudioProcessorModule& processor;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinearAudioProcessorModuleEditor)
};
