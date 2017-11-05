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
#include "../DSP/DryWet.h"
#include "../DSP/Gain.h"
#include "../GUI/GoniometerSource.h"
#include "../DSP/WindowedMeter.h"

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
    
    GoniometerSource graphCompressSource;

    AudioProcessorParameterWithID* paramAttack;
    AudioProcessorParameterWithID* paramRelease;
    AudioProcessorParameterWithID* paramRatio;
    AudioProcessorParameterWithID* paramThreshold;
    AudioProcessorParameterWithID* paramMakeupGain;
    AudioProcessorParameterWithID* paramDryWet;

    WindowedMeter peak;

    Compressor compressor;
    Gain makeup;
    DryWet dryWet;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMCompressorPlugin)
};
