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
    friend class MobileMixPluginInstance;
    void finalizeParametersAndAddToParent(const Identifier& rootId);

    AudioProcessor& root;
    ValueTree& parent;
    UndoManager undo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NestedAudioProcessorState)
};
