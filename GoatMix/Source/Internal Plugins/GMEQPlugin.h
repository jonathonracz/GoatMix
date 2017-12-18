/*
  ==============================================================================

    GMEQPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/GMPluginInstance.h"
#include "../DSP/GMIIRFilter.h"
#include "../DSP/SignalSnapshotter.h"
#include <array>

class GMEQPlugin :
    public GMPluginInstance
{
public:
    GMEQPlugin(AudioProcessorValueTreeState& state);
    ~GMEQPlugin() {}

    void registerParameters() override;

    GMPluginInstanceEditor* createGoatMixEditor() override;
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
    std::array<GMIIRFilter, 4> filters;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMEQPlugin)
};
