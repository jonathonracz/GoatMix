/*
  ==============================================================================

    MMDistortionPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../Core/MobileMixPluginInstance.h"
#include "../DSP/AmplitudeQuantize.h"
#include "../DSP/SampleRepeat.h"
#include "../DSP/Overdrive.h"
#include "../GUI/DistortionPreview.h"

class MMDistortionPlugin :
    public MobileMixPluginInstance
{
public:
    MMDistortionPlugin(AudioProcessorValueTreeState& state);
    ~MMDistortionPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override { return "Distortion"; }
    const String getDisplayName() const override { return NEEDS_TRANS("Distort"); }

    void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorParameterWithID* paramDistortion;

private:
    DistortionPreview preview;

    AmplitudeQuantize quantizer;
    SampleRepeat sampleRepeater;
    Overdrive overdrive;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMDistortionPlugin)
};
