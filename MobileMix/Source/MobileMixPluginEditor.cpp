/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

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
    for (int i = 0; i < processor.chain.getNumNodes(); ++i)
    {
        AudioProcessor* currentProcessor = processor.chain.getNode(i)->getProcessor();
        tabs.addTab(currentProcessor->getName(), Colours::white, currentProcessor->createEditor(), true);
    }

    tabs.addListener(this);
    addAndMakeVisible(tabs);
}

MobileMixAudioProcessorEditor::~MobileMixAudioProcessorEditor()
{
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

void MobileMixAudioProcessorEditor::tabMovedViaDrag(int fromIndex, int toIndex)
{
    // Attempting to move tabs representing processor indices which don't exist...
    assert(fromIndex < processor.chain.getNumNodes() && toIndex < processor.chain.getNumNodes());
    processor.chain.moveNode(fromIndex, toIndex);
    DBG("Tab " << fromIndex << " moved to " << toIndex);
}
