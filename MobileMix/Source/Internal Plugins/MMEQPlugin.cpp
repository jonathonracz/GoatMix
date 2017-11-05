/*
  ==============================================================================

    MMEQPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMEQPlugin.h"
#include "MMEQPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

MMEQPlugin::MMEQPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMEQPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    for (size_t i = 0; i < eqParams.size(); ++i)
    {
        EQParams* eq = &eqParams[i];
        eq->paramFrequency = state.createAndAddParameter(
            addPrefixToParameterName("Frequency ") + String(i),
            addPrefixToParameterName("Frequency ") + String(i),
            ValueStringFuncs::Filter::unit,
            ValueStringFuncs::Filter::range,
            ValueStringFuncs::Filter::defaultValue,
            [](float value){ return ValueStringFuncs::Generic::valueToText(value, ValueStringFuncs::Filter::unit, 0); },
            ValueStringFuncs::Generic::textToValue);

        eq->paramGain = state.createAndAddParameter(
            addPrefixToParameterName("Gain ") + String(i),
            addPrefixToParameterName("Gain ") + String(i),
            ValueStringFuncs::Gain::unit,
            ValueStringFuncs::Gain::range,
            ValueStringFuncs::Gain::defaultValue,
            ValueStringFuncs::Gain::valueToText,
            ValueStringFuncs::Gain::textToValue);

        eq->paramQ = state.createAndAddParameter(
            addPrefixToParameterName("Q ") + String(i),
            addPrefixToParameterName("Q ") + String(i),
            "",
            NormalisableRange<float>(0.0f, 1.0f, 0.1f),
            1.0f,
            nullptr,
            nullptr);

        eq->paramType = state.createAndAddParameter(
            addPrefixToParameterName("Type ") + String(i),
            addPrefixToParameterName("Type ") + String(i),
            "",
            NormalisableRange<float>(0.0f, 1.0f, 0.1f),
            1.0f,
            nullptr,
            nullptr);
    }
}

AudioProcessorEditor* MMEQPlugin::createEditor()
{
    return new MMEQPluginEditor(*this);
}

void MMEQPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
}

void MMEQPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}
