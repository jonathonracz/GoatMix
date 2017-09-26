/*
  ==============================================================================

    NestedAudioProcessorInstance.h
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NestedAudioProcessorInstance :
    public AudioPluginInstance
{
public:
    NestedAudioProcessorInstance(AudioProcessorValueTreeState& parentState);
    virtual ~NestedAudioProcessorInstance() {}

protected:
    AudioProcessorValueTreeState& parentState;
};
