/*
  ==============================================================================

    MobileMixPluginEditor.cpp
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginProcessor.h"
#include "MobileMixPluginEditor.h"
#include "GUI/ScreenResolutionConstants.h"

MobileMixAudioProcessorEditor::MobileMixAudioProcessorEditor(MobileMixAudioProcessor& p) :
    AudioProcessorEditor(&p),
    processor(p),
    tabs(TabbedButtonBar::Orientation::TabsAtBottom)
{
    setSize(ScreenResolutionConstants::iPhone7LogicalY,
        ScreenResolutionConstants::iPhone7LogicalX);
    processor.params.state.addListener(this);
    for (int i = 0; i < processor.chain.getNumNodes(); ++i)
    {
        assert(processor.chainTree.getChild(i).getType() == Identifier(processor.chain.getNode(i)->getProcessor()->getName()));
        AudioProcessor* currentProcessor = processor.chain.getNode(i)->getProcessor();
        tabs.addTab(currentProcessor->getName(), Colours::white, currentProcessor->createEditor(), true);
    }

    tabs.addListener(this);
    addAndMakeVisible(tabs);
    startTimerHz(30); // 30 FPS refresh rate.
}

MobileMixAudioProcessorEditor::~MobileMixAudioProcessorEditor()
{
    processor.params.state.removeListener(this);
}

void MobileMixAudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MobileMixAudioProcessorEditor::resized()
{
    tabs.setBounds(getBounds());
}

int MobileMixAudioProcessorEditor::getIndexOfTabWithName(String name)
{
    TabbedButtonBar& bar = tabs.getTabbedButtonBar();
    for (int i = 0; i < bar.getNumTabs(); ++i)
        if (bar.getTabButton(i)->getName() == name)
            return i;

    assert(false);
    return -1;
}

void MobileMixAudioProcessorEditor::tabMovedViaDrag(int fromIndex, int toIndex)
{
    // Attempting to move tabs representing processor indices which don't exist...
    assert(fromIndex < processor.chain.getNumNodes() && toIndex < processor.chain.getNumNodes());
    assert(fromIndex < processor.chainTree.getNumChildren() && toIndex < processor.chainTree.getNumChildren());
    processor.chainTree.moveChild(fromIndex, toIndex, nullptr);
    DBG("Tab " << fromIndex << " moved to " << toIndex);
}

void MobileMixAudioProcessorEditor::timerCallback()
{
    repaint();
}

void MobileMixAudioProcessorEditor::valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    if (parentTreeWhoseChildrenHaveMoved == processor.chainTree)
    {
        tabs.moveTab(oldIndex, newIndex);
    }
}

void MobileMixAudioProcessorEditor::valueTreeRedirected(ValueTree &treeWhichHasBeenChanged)
{
    if (treeWhichHasBeenChanged == processor.chainTree)
    {
        // We need to rebuild our tabs.
        for (int i = 0; i < processor.chainTree.getNumChildren(); ++i)
        {
            int currentTabIndex = getIndexOfTabWithName(processor.chainTree.getChild(i).getType().toString());
            if (currentTabIndex > -1 && currentTabIndex != i)
            {
                tabs.moveTab(currentTabIndex, i);
            }
        }
    }
}
