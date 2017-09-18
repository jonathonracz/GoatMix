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
    TabbedComponent(TabbedButtonBar::Orientation::TabsAtBottom),
    AudioProcessorEditor(_processor),
    processor(_processor)
{
    processor.addChangeListener(this);
}

LinearAudioProcessorGraphEditor::~LinearAudioProcessorGraphEditor()
{
    processor.removeChangeListener(this);
}

void LinearAudioProcessorGraphEditor::removeTabWithModelUpdate(int tabIndex)
{
    removeTab(tabIndex);
    processor.removeProcessor(tabIndex);
}

void LinearAudioProcessorGraphEditor::moveTabWithModelUpdate(int currentIndex, int newIndex, bool animate)
{
    moveTab(currentIndex, newIndex, animate);
    processor.moveProcessor(currentIndex, newIndex);
}

TabBarButton* LinearAudioProcessorGraphEditor::createTabButton(const String& tabName, int tabIndex)
{
    return new DraggableTabBarButton(tabName, getTabbedButtonBar(), *this);
}

void LinearAudioProcessorGraphEditor::changeListenerCallback(ChangeBroadcaster* source)
{
    // This will only be called by the model if the entire graph has changed
    // (i.e. from a new state load). So we hose this entire view and rebuild
    // the tab list.
    assert(source == &processor);
    LinearAudioProcessorGraph* typedSource = static_cast<LinearAudioProcessorGraph*>(source);
    clearTabs();
    for (int i = 0; i < typedSource->getNumProcessors(); ++i)
    {
        AudioProcessor* processor = typedSource->getAudioProcessorAtIndex(i);
        addTab(processor->getName(), Colours::white, processor->createEditor(), true);
    }
}
