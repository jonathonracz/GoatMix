/*
  ==============================================================================

    MMDistortionPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMDistortionPlugin.h"
#include "MMDistortionPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

MMDistortionPlugin::MMDistortionPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMDistortionPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramDownsample = state.createAndAddParameter(
        addPrefixToParameterName("Downsample"),
        addPrefixToParameterName("Downsample"),
        "x",
        NormalisableRange<float>(0.0f, 16.0f, 1.0f),
        0.0f,
        [](float value){ return ValueStringFuncs::Generic::valueToText(value, "x", 0); },
        ValueStringFuncs::Generic::textToValue);

    paramBitDepth = state.createAndAddParameter(
        addPrefixToParameterName("Bit Depth"),
        addPrefixToParameterName("Bit Depth"),
        "bits",
        NormalisableRange<float>(1.0f, 32.0f, 1.0f),
        32.0f,
        [](float value){ return ValueStringFuncs::Generic::valueToText(value, "bits", 0); },
        ValueStringFuncs::Generic::textToValue);

    NormalisableRange<float> odRange = ValueStringFuncs::Gain::range;
    odRange.end = 4.0f;
    paramOverdrive = state.createAndAddParameter(
        addPrefixToParameterName("Overdrive"),
        addPrefixToParameterName("Overdrive"),
        ValueStringFuncs::Gain::unit,
        odRange,
        ValueStringFuncs::Gain::defaultValue,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramGain = state.createAndAddParameter(
        addPrefixToParameterName("Gain"),
        addPrefixToParameterName("Gain"),
        ValueStringFuncs::Gain::unit,
        ValueStringFuncs::Gain::range,
        ValueStringFuncs::Gain::defaultValue,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramLowPass = state.createAndAddParameter(
        addPrefixToParameterName("Low Pass"),
        addPrefixToParameterName("Low Pass"),
        ValueStringFuncs::Filter::unit,
        ValueStringFuncs::Filter::range,
        ValueStringFuncs::Filter::defaultValue,
        ValueStringFuncs::Filter::valueToText,
        ValueStringFuncs::Generic::textToValue);

    paramLowPassEnable = state.createAndAddParameter(
        addPrefixToParameterName("Low Pass Enable"),
        addPrefixToParameterName("Low Pass Enable"),
        {},
        ValueStringFuncs::OnOff::range,
        0.0f,
        ValueStringFuncs::OnOff::valueToText,
        ValueStringFuncs::OnOff::textToValue);
}

AudioProcessorEditor* MMDistortionPlugin::createEditor()
{
    return new MMDistortionPluginEditor(*this);
}

void MMDistortionPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    };

    distortion.prepare(spec);
    lowPass.prepare(spec);
}

void MMDistortionPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    distortion.params->samplesToRepeat = getUnnormalizedValue(paramDownsample);
    distortion.params->bitDepth = getUnnormalizedValue(paramBitDepth);
    distortion.params->overDriveGainUp = getUnnormalizedValue(paramOverdrive);
    distortion.params->overDriveGainDown = getUnnormalizedValue(paramGain);
    lowPass.params->cutoff = getUnnormalizedValue(paramLowPass);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    distortion.process(context);
    if (getUnnormalizedValue(paramLowPassEnable) >= 0.5f)
        lowPass.process(context);
}
