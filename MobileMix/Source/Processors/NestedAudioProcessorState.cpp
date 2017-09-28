/*
  ==============================================================================

    NestedAudioProcessorState.cpp
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "NestedAudioProcessorState.h"

NestedAudioProcessorState::NestedAudioProcessorState(AudioProcessor& rootProcessor,
                                                     AudioProcessorValueTreeState& parentState) :
    root(rootProcessor),
    parent(parentState),
    state(root, &undo)
{
}

void NestedAudioProcessorState::finalizeParametersAndAddToParent(const Identifier& rootId)
{
    state.state = ValueTree(rootId);
    parent.state.addChild(state.state, -1, &undo);
}
