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
    processor(p)
{
    setSize(ScreenResolutionConstants::iPhone7LogicalY,
        ScreenResolutionConstants::iPhone7LogicalX);
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
}
