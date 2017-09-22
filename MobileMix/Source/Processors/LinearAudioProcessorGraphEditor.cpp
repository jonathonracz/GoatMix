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

    for (int i = 0; i < processor.getNumProcessors(); ++i)
    {
        AudioProcessor* processorNode = processor.getProcessorAtIndex(i);
        tabs.addTab(processorNode->getName(), Colours::white, processorNode->createEditor(), true);
    }

    tabs.addListener(this);
    addAndMakeVisible(tabs);
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

void LinearAudioProcessorGraphEditor::tabMovedViaDrag(int fromIndex, int toIndex)
{
    processor.moveProcessor(fromIndex, toIndex);
    DBG("Tab dragged from " << fromIndex << " to " << toIndex);
}
