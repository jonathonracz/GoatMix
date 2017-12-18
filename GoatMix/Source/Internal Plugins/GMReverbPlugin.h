/*
  ==============================================================================

    GMReverbPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/GoatMixPluginInstance.h"
#include "../DSP/DryWet.h"
#include "../DSP/GMReverb.h"
#include "../DSP/GMStateVariableFilter.h"
#include "../GUI/GoniometerSource.h"

class GMReverbPlugin :
    public GoatMixPluginInstance
{
public:
    GMReverbPlugin(AudioProcessorValueTreeState& state);
    ~GMReverbPlugin() {}

    void registerParameters() override;

    GoatMixPluginInstanceEditor* createGoatMixEditor() override;
    const String getName() const override { return "Reverb"; }
    const String getDisplayName() const override { return UIStrings::Reverb::displayName; }

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

    GMReverb reverb;

private:
    GMStateVariableFilter lowPass;
    GMStateVariableFilter highPass;
    DryWet dryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMReverbPlugin)
};
