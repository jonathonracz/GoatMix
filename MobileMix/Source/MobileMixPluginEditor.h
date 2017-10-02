/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MobileMixPluginProcessor.h"
#include "GUI/DraggableTabbedComponent.h"

/**
*/
class MobileMixAudioProcessorEditor :
    public AudioProcessorEditor,
    public DraggableTabbedComponent::Listener
{
public:
    MobileMixAudioProcessorEditor(MobileMixAudioProcessor&);
    ~MobileMixAudioProcessorEditor();

    void paint(Graphics&) override;
    void resized() override;

private:
    void tabMovedViaDrag(int fromIndex, int toIndex) override;
    
    MobileMixAudioProcessor& processor;
    DraggableTabbedComponent tabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessorEditor)
};
