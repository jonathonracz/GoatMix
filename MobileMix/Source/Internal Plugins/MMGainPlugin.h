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
#include "../GUI/MaxdBLabel.h"
#include "../DSP/DelayLine.h"
#include "../DSP/Gain.h"
#include "../DSP/InvertPhase.h"
#include "../DSP/Pan.h"

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

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

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
    DelayLine delay;
    Gain gain;
    InvertPhase invertPhase;
    Pan pan;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPlugin)
};
