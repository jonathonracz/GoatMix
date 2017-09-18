/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Processors/LinearAudioProcessorGraphEditor.h"

/**
*/
class MobileMixAudioProcessorEditor :
    public AudioProcessorEditor
{
public:
    MobileMixAudioProcessorEditor(MobileMixAudioProcessor&);
    ~MobileMixAudioProcessorEditor();

    void paint(Graphics&) override;
    void resized() override;

private:
    MobileMixAudioProcessor& processor;
    LinearAudioProcessorGraphEditor* linearGraphEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessorEditor)
};
