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
