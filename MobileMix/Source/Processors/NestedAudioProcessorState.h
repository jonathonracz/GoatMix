/*
  ==============================================================================

    NestedAudioProcessorState.h
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NestedAudioProcessorState
{
public:
    NestedAudioProcessorState(AudioProcessor& rootProcessor,
                              AudioProcessorValueTreeState& parentState);
    virtual ~NestedAudioProcessorState() {}

private:
    AudioProcessor& root;
    AudioProcessorValueTreeState& parent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NestedAudioProcessorState)

protected:
    void finalizeParametersAndAddToParent(const Identifier& rootId);

    AudioProcessorValueTreeState state;
    UndoManager undo;
};
