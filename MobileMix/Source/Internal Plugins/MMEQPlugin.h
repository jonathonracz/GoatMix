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

class MMEQPlugin :
    public MobileMixPluginInstance
{
public:
    MMEQPlugin(AudioProcessorValueTreeState& state);
    ~MMEQPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override { return "EQ"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Equalize"); }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    
    AudioProcessorParameterWithID* paramFrequency1;
    AudioProcessorParameterWithID* paramGain1;
    AudioProcessorParameterWithID* paramQ1;
    AudioProcessorParameterWithID* paramType1;
    AudioProcessorParameterWithID* paramFrequency2;
    AudioProcessorParameterWithID* paramGain2;
    AudioProcessorParameterWithID* paramQ2;
    AudioProcessorParameterWithID* paramType2;
    AudioProcessorParameterWithID* paramFrequency3;
    AudioProcessorParameterWithID* paramGain3;
    AudioProcessorParameterWithID* paramQ3;
    AudioProcessorParameterWithID* paramType3;
    AudioProcessorParameterWithID* paramFrequency4;
    AudioProcessorParameterWithID* paramGain4;
    AudioProcessorParameterWithID* paramQ4;
    AudioProcessorParameterWithID* paramType4;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMEQPlugin)
};
