/*
  ==============================================================================

    GMDistortionPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMDistortionPlugin.h"
#include "GMDistortionPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

GMDistortionPlugin::GMDistortionPlugin(AudioProcessorValueTreeState& state) :
    GoatMixPluginInstance(state)
{
    meterSource.allocateMeters(getMainBusNumInputChannels());
}

void GMDistortionPlugin::registerParameters()
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
        "bit",
        NormalisableRange<float>(1.0f, 16.0f, 1.0f),
        16.0f,
        [](float value){ return ValueStringFuncs::Generic::valueToText(value, "bit", 0); },
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

GoatMixPluginInstanceEditor* GMDistortionPlugin::createGoatMixEditor()
{
    return new GMDistortionPluginEditor(*this);
}

void GMDistortionPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    };

    meterSource.prepare(spec);
    distortion.prepare(spec);
    lowPass.prepare(spec);
}

void GMDistortionPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    distortion.params->samplesToRepeat = getUnnormalizedValue(paramDownsample);
    distortion.params->bitDepth = getUnnormalizedValue(paramBitDepth);
    distortion.params->overdriveGainUp = getUnnormalizedValue(paramOverdrive);
    distortion.params->overdriveGainDown = getUnnormalizedValue(paramGain);
    lowPass.params->cutoff = getUnnormalizedValue(paramLowPass);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    distortion.process(context);
    meterSource.process(context);
    if (getUnnormalizedValue(paramLowPassEnable) >= 0.5f)
        lowPass.process(context);
}
