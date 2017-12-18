/*
  ==============================================================================

    GoatMixPluginEditor.h
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GoatMixPluginProcessor.h"
#include "GUI/GMTabbedComponent.h"
#include "GUI/GMTopBar.h"
#include "GUI/GMLookAndFeel.h"
#include "GUI/LongDialogPopup.h"
#include "Core/GoatMixPluginInstanceEditor.h"
#include "GUI/AboutDataManager.h"
#include "GUI/GMTooltipDisplay.h"

/**
*/
class GoatMixAudioProcessorEditor :
    public AudioProcessorEditor,
    public DraggableTabbedComponent::Listener,
    public ValueTree::Listener,
    public GMTopBar::Listener
{
public:
    GoatMixAudioProcessorEditor(GoatMixAudioProcessor&);
    ~GoatMixAudioProcessorEditor();

    void paint(Graphics&) override;
    void resized() override;

private:
    int getIndexOfTabWithName(String name);

    void tabDragStarted(int atIndex) override;
    void tabMovedViaDrag(int fromIndex, int toIndex) override;

    void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override {}
    void valueTreeChildAdded(ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override {};
    void valueTreeChildRemoved(ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override {}
    void valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged) override {}
    void valueTreeRedirected(ValueTree &treeWhichHasBeenChanged) override;

    void undoClicked(GMTopBar* bar) override { processor.undoManager.undo(); }
    void redoClicked(GMTopBar* bar) override { processor.undoManager.redo(); }
    void infoClicked(GMTopBar* bar) override;

    GoatMixAudioProcessor& processor;
    GMTopBar topBar;
    GMTabbedComponent tabs;
    GMLookAndFeel lookAndFeel;
    AboutDataManager aboutData;
    LongDialogPopup aboutMessage;
    GMTooltipDisplay tooltipDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GoatMixAudioProcessorEditor)
};
