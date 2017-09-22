/*
  ==============================================================================

    LinearAudioProcessorGraph.cpp
    Created: 16 Sep 2017 6:58:30pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "LinearAudioProcessorGraphEditor.h"
#include "../GUI/DraggableTabBarButton.h"

LinearAudioProcessorGraphEditor::LinearAudioProcessorGraphEditor(LinearAudioProcessorGraph& _processor) :
    AudioProcessorEditor(_processor),
    processor(_processor),
    tabs(TabbedButtonBar::Orientation::TabsAtBottom)
{
    processor.addChangeListener(this);
    addAndMakeVisible(tabs);
    tabs.addTabWithNotification("1", Colours::white, new TextEditor, true);
    tabs.addTabWithNotification("2", Colours::white, new TextEditor, true);
    tabs.addTabWithNotification("3", Colours::white, new TextEditor, true);
    tabs.addTabWithNotification("4", Colours::white, new TextEditor, true);
}

LinearAudioProcessorGraphEditor::~LinearAudioProcessorGraphEditor()
{
    processor.removeChangeListener(this);
}

void LinearAudioProcessorGraphEditor::changeListenerCallback(ChangeBroadcaster* source)
{

}

void LinearAudioProcessorGraphEditor::resized()
{
    tabs.setSize(getWidth(), getHeight());
}
