/*
  ==============================================================================

    MobileMixSubAudioProcessor.h
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "NestedAudioProcessorState.h"

class MobileMixSubAudioProcessor :
    public AudioPluginInstance
{
public:
    MobileMixSubAudioProcessor(AudioProcessor& rootProcessor,
                            AudioProcessorValueTreeState& parentState);
    virtual ~MobileMixSubAudioProcessor();

    void fillInPluginDescription(PluginDescription &description) const override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    bool hasEditor() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

protected:
    NestedAudioProcessorState state;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixSubAudioProcessor)
};
