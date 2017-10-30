/*
  ==============================================================================

    MMReverbPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/MobileMixPluginInstance.h"

class MMReverbPlugin :
    public MobileMixPluginInstance
{
public:
    MMReverbPlugin(AudioProcessorValueTreeState& state);
    ~MMReverbPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override { return "Reverb"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Reverb"); }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramReverb;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPlugin)
};
