/*
  ==============================================================================

    LinearAudioProcessorGraph.h
    Created: 16 Sep 2017 6:58:30pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LinearAudioProcessorGraph.h"
#include "../GUI/DraggableTabbedComponent.h"

class LinearAudioProcessorGraphEditor :
    public AudioProcessorEditor,
    public ChangeListener
{
public:
    LinearAudioProcessorGraphEditor(LinearAudioProcessorGraph& processor);
    ~LinearAudioProcessorGraphEditor();

protected:
    LinearAudioProcessorGraph& processor;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    void resized() override;

private:
    DraggableTabbedComponent tabs;
};
