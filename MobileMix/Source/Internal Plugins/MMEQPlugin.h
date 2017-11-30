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
#include "../DSP/MMIIRFilter.h"
#include "../DSP/SignalSnapshotter.h"
#include <array>

class MMEQPlugin :
    public MobileMixPluginInstance
{
public:
    MMEQPlugin(AudioProcessorValueTreeState& state);
    ~MMEQPlugin() {}

    void registerParameters() override;

    MobileMixPluginInstanceEditor* createMobileMixEditor() override;
    const String getName() const override { return "EQ"; }
    const String getDisplayName() const override { return UIStrings::EQ::displayName; }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    struct EQParams
    {
        AudioProcessorParameterWithID* paramCutoff;
        AudioProcessorParameterWithID* paramGain;
        AudioProcessorParameterWithID* paramQ;
        AudioProcessorParameterWithID* paramType;
    };

    std::array<EQParams, 4> eqParams;
    const StringArray filterTypes;
    SignalSnapshotter snapshotter;

private:
    std::array<MMIIRFilter, 4> filters;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMEQPlugin)
};
