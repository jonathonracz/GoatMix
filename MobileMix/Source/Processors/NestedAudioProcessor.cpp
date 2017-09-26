/*
  ==============================================================================

    NestedAudioProcessor.cpp
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "NestedAudioProcessor.h"

NestedAudioProcessor::NestedAudioProcessor(AudioProcessor& rootProcessor,
                                           AudioProcessorValueTreeState& parentState,
                                           const Identifier& _stateId) :
    root(rootProcessor),
    parent(parentState),
    stateId(_stateId),
    state(root, &undo)
{
}

void NestedAudioProcessor::finalizeParametersAndAddToParent()
{
    state.state = ValueTree(stateId);
    parent.state.addChild(state.state, -1, &undo);
}
