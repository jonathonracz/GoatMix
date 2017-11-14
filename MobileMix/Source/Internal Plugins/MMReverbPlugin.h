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
#include "../DSP/MMStateVariableFilter.h"
#include "../GUI/GoniometerSource.h"

class MMReverbPlugin :
    public MobileMixPluginInstance
{
public:
    MMReverbPlugin(AudioProcessorValueTreeState& state);
    ~MMReverbPlugin() {}

    void registerParameters() override;

    MobileMixPluginInstanceEditor* createMobileMixEditor() override;
    const String getName() const override { return "Reverb"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Reverb"); }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramRoomSize;
    AudioProcessorParameterWithID* paramDamping;
    AudioProcessorParameterWithID* paramWidth;
    AudioProcessorParameterWithID* paramFreeze;
    AudioProcessorParameterWithID* paramLowPass;
    AudioProcessorParameterWithID* paramLowPassEnable;
    AudioProcessorParameterWithID* paramHighPass;
    AudioProcessorParameterWithID* paramHighPassEnable;
    AudioProcessorParameterWithID* paramDryWet;

    MMReverb reverb;

private:
    MMStateVariableFilter lowPass;
    MMStateVariableFilter highPass;
    DryWet dryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPlugin)
};
