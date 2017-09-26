/*
  ==============================================================================

    NestedAudioProcessor.h
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NestedAudioProcessor :
    public AudioProcessor
{
public:
    NestedAudioProcessor(AudioProcessor& rootProcessor,
                         AudioProcessorValueTreeState& parentState,
                         const Identifier& stateId);
    virtual ~NestedAudioProcessor() {}

private:
    AudioProcessor& root;
    AudioProcessorValueTreeState& parent;

protected:
    void finalizeParametersAndAddToParent();

    const Identifier stateId;
    AudioProcessorValueTreeState state;
    UndoManager undo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NestedAudioProcessor)
};
