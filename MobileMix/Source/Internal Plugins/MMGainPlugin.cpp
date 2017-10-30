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
        NormalisableRange<float>(0.0f, 100.0f, 1.0f),
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
}

void MMGainPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    goniometerSource.process(buffer);
}
