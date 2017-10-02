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
                              ValueTree& parentState);
    virtual ~NestedAudioProcessorState() {}

    AudioProcessorValueTreeState state;

private:
    AudioProcessor& root;
    ValueTree& parent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NestedAudioProcessorState)

protected:
    void finalizeParametersAndAddToParent(const Identifier& rootId);

    UndoManager undo;
};
