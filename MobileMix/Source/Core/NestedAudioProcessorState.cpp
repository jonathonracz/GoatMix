/*
  ==============================================================================

    NestedAudioProcessorState.cpp
    Created: 25 Sep 2017 12:14:04am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "NestedAudioProcessorState.h"

NestedAudioProcessorState::NestedAudioProcessorState(AudioProcessor& rootProcessor,
                                                     ValueTree& parentState) :
    state(rootProcessor, &undo),
    root(rootProcessor),
    parent(parentState)
{
}

void NestedAudioProcessorState::finalizeParametersAndAddToParent(const Identifier& rootId)
{
    state.state = ValueTree(rootId);
    parent.addChild(state.state, -1, &undo);
}
