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

class LinearAudioProcessorGraphEditor :
    public TabbedComponent,
    public AudioProcessorEditor,
    public ChangeListener
{
public:
    LinearAudioProcessorGraphEditor(LinearAudioProcessorGraph& processor);
    ~LinearAudioProcessorGraphEditor();

    void removeTabWithModelUpdate(int tabIndex);
    void moveTabWithModelUpdate(int currentIndex, int newIndex, bool animate = false);

    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;

    void changeListenerCallback(ChangeBroadcaster* source) override;

protected:
    LinearAudioProcessorGraph& processor;
};
