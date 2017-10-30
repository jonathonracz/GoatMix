/*
  ==============================================================================

    MMGainPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/MobileMixPluginInstance.h"
#include "../GUI/GoniometerSource.h"

class MMGainPlugin :
    public MobileMixPluginInstance
{
public:
    MMGainPlugin(AudioProcessorValueTreeState& state);
    ~MMGainPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override { return "Gain"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Gain"); }

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    GoniometerSource goniometerSource;

    AudioProcessorParameterWithID* paramGain;
    AudioProcessorParameterWithID* paramGainL;
    AudioProcessorParameterWithID* paramGainR;
    AudioProcessorParameterWithID* paramPan;
    AudioProcessorParameterWithID* paramPhaseDelayL;
    AudioProcessorParameterWithID* paramPhaseDelayR;
    AudioProcessorParameterWithID* paramPhaseInvertL;
    AudioProcessorParameterWithID* paramPhaseInvertR;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPlugin)
};
