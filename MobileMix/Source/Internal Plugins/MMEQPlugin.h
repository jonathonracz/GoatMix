/*
  ==============================================================================

    MMEQPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/MobileMixPluginInstance.h"

class MMEQPlugin :
    public MobileMixPluginInstance
{
public:
    MMEQPlugin(AudioProcessorValueTreeState& state);
    ~MMEQPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override { return "EQ"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Equalize"); }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramEQ;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMEQPlugin)
};
