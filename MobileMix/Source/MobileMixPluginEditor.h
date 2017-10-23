/*
  ==============================================================================

    MobileMixPluginEditor.h
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MobileMixPluginProcessor.h"
#include "GUI/MMTabbedComponent.h"
#include "GUI/MMTopBar.h"

/**
*/
class MobileMixAudioProcessorEditor :
    public AudioProcessorEditor,
    public DraggableTabbedComponent::Listener,
    public ValueTree::Listener,
    public Timer
{
public:
    MobileMixAudioProcessorEditor(MobileMixAudioProcessor&);
    ~MobileMixAudioProcessorEditor();

    void paint(Graphics&) override;
    void resized() override;

private:
    int getIndexOfTabWithName(String name);

    void tabDragStarted(int atIndex) override;
    void tabMovedViaDrag(int fromIndex, int toIndex) override;
    void timerCallback() override;

    void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override {}
    void valueTreeChildAdded(ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override {};
    void valueTreeChildRemoved(ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override {}
    void valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged) override {}
    void valueTreeRedirected(ValueTree &treeWhichHasBeenChanged) override;

    MobileMixAudioProcessor& processor;
    MMTopBar topBar;
    MMTabbedComponent tabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessorEditor)
};
