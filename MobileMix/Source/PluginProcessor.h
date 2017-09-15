/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/**
*/
class MobileMixAudioProcessor :
    public AudioProcessorGraph
{
public:
    MobileMixAudioProcessor();
    ~MobileMixAudioProcessor();

    bool hasEditor() const override;
    AudioProcessorEditor* createEditor() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

private:
    AudioProcessorValueTreeState parameters;
    AudioGraphIOProcessor input;
    AudioGraphIOProcessor output;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MobileMixAudioProcessor)
};
