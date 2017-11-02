/*
  ==============================================================================

    MMCompressorPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/MobileMixPluginInstance.h"
#include "../DSP/Compressor.h"

class MMCompressorPlugin :
    public MobileMixPluginInstance
{
public:
    MMCompressorPlugin(AudioProcessorValueTreeState& state);
    ~MMCompressorPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override { return "Compressor"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Compress"); }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramCompressor;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMCompressorPlugin)
};
