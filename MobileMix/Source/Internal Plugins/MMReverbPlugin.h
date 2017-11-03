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
#include "../DSP/DryWet.h"
#include "../DSP/MMReverb.h"

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
    DryWet dryWet;
    MMReverb reverb;
    dsp::ProcessorDuplicator<
        dsp::StateVariableFilter::Filter<float>,
        dsp::StateVariableFilter::Parameters<float>> lowPass;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPlugin)
};
