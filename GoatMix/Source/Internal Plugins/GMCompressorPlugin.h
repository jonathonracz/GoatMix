/*
  ==============================================================================

    GMCompressorPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/GMPluginInstance.h"
#include "../DSP/Compressor.h"
#include "../DSP/DryWet.h"
#include "../DSP/Gain.h"
#include "../DSP/WindowedMeter.h"

class GMCompressorPlugin :
    public GMPluginInstance
{
public:
    GMCompressorPlugin(AudioProcessorValueTreeState& state);
    ~GMCompressorPlugin() {}

    void registerParameters() override;

    GMPluginInstanceEditor* createGoatMixEditor() override;
    const String getName() const override { return "Compressor"; }
    const String getDisplayName() const override { return UIStrings::Compressor::displayName; }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramAttack;
    AudioProcessorParameterWithID* paramRelease;
    AudioProcessorParameterWithID* paramRatio;
    AudioProcessorParameterWithID* paramThreshold;
    AudioProcessorParameterWithID* paramMakeupGain;
    AudioProcessorParameterWithID* paramDryWet;

    WindowedMeter meter;
    Compressor compressor;
    Gain makeup;
    DryWet dryWet;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMCompressorPlugin)
};
