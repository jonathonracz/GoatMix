/*
  ==============================================================================

    GMDistortionPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/GMPluginInstance.h"
#include "../DSP/DistortionChain.h"
#include "../DSP/GMStateVariableFilter.h"
#include "../DSP/MultiWindowedMeter.h"

class GMDistortionPlugin :
    public GMPluginInstance
{
public:
    GMDistortionPlugin(AudioProcessorValueTreeState& state);
    ~GMDistortionPlugin() {}

    void registerParameters() override;

    GMPluginInstanceEditor* createGoatMixEditor() override;
    const String getName() const override { return "Distortion"; }
    const String getDisplayName() const override { return UIStrings::Distortion::displayName; }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramDownsample;
    AudioProcessorParameterWithID* paramBitDepth;
    AudioProcessorParameterWithID* paramOverdrive;
    AudioProcessorParameterWithID* paramGain;
    AudioProcessorParameterWithID* paramLowPass;
    AudioProcessorParameterWithID* paramLowPassEnable;

    MultiWindowedMeter meterSource;

    DistortionChain distortion;

private:
    GMStateVariableFilter lowPass;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMDistortionPlugin)
};
