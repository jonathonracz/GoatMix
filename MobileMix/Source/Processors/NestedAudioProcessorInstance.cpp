/*
  ==============================================================================

    NestedAudioProcessorInstance.cpp
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "NestedAudioProcessorInstance.h"

NestedAudioProcessorInstance::NestedAudioProcessorInstance(AudioProcessorValueTreeState& _parentState) :
    parentState(_parentState)
{
}
