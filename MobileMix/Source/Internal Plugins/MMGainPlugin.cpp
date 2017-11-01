/*
  ==============================================================================

    MMGainPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMGainPlugin.h"
#include "MMGainPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

MMGainPlugin::MMGainPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMGainPlugin::registerParameters()
{
    paramGain = state.createAndAddParameter(
        addPrefixToParameterName("Gain"),
        addPrefixToParameterName("Gain"),
        ValueStringFuncs::Gain::unit,
        NormalisableRange<float>(0.0f, 2.0f, 0.01f),
        1.0f,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramGainL = state.createAndAddParameter(
        addPrefixToParameterName("Gain L"),
        addPrefixToParameterName("Gain L"),
        ValueStringFuncs::Gain::unit,
        NormalisableRange<float>(0.0f, 2.0f, 0.01f),
        1.0f,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramGainR = state.createAndAddParameter(
        addPrefixToParameterName("Gain R"),
        addPrefixToParameterName("Gain R"),
        ValueStringFuncs::Gain::unit,
        NormalisableRange<float>(0.0f, 2.0f, 0.01f),
        1.0f,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramPan = state.createAndAddParameter(
        addPrefixToParameterName("Pan"),
        addPrefixToParameterName("Pan"),
        "%",
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.5f,
        nullptr,
        nullptr);

    paramPhaseDelayL = state.createAndAddParameter(
        addPrefixToParameterName("Phase Delay L"),
        addPrefixToParameterName("Phase Delay L"),
        "ms",
        NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        nullptr,
        nullptr);

    paramPhaseDelayR = state.createAndAddParameter(
        addPrefixToParameterName("Phase Delay R"),
        addPrefixToParameterName("Phase Delay R"),
        "ms",
        NormalisableRange<float>(0.0f, 1000.0f, 1.0f),
        0.0f,
        nullptr,
        nullptr);

    paramPhaseInvertL = state.createAndAddParameter(
        addPrefixToParameterName("Phase Invert L"),
        addPrefixToParameterName("Phase Invert L"),
        {},
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        0.0f,
        nullptr,
        nullptr);

    paramPhaseInvertR = state.createAndAddParameter(
        addPrefixToParameterName("Phase Invert R"),
        addPrefixToParameterName("Phase Invert R"),
        {},
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        0.0f,
        nullptr,
        nullptr);
}

AudioProcessorEditor* MMGainPlugin::createEditor()
{
    return new MMGainPluginEditor(*this);
}

void MMGainPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec spec {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    };

    delay.params->maxDelay = static_cast<size_t>(sampleRate); // 1 second max delay
    delay.prepare(spec);
    gain.prepare(spec);
}

void MMGainPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    delay.params->samplesToDelay = static_cast<size_t>((getUnnormalizedValue(paramPhaseDelayR) / 1000.0f) * getPreparedSampleRate());
    gain.params->gain = getUnnormalizedValue(paramGain);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    delay.process(context);
    gain.process(context);
    goniometerSource.process(buffer);
}
