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
    MobileMixPluginInstance(state),
    filterTypes("Bypass", "High Pass", "High Shelf", "Peak", "Low Shelf", "Low Pass")
{
}

void MMEQPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    for (size_t i = 0; i < eqParams.size(); ++i)
    {
        EQParams* eq = &eqParams[i];
        eq->paramCutoff = state.createAndAddParameter(
            addPrefixToParameterName("Cutoff ") + String(i),
            addPrefixToParameterName("Cutoff ") + String(i),
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
            NormalisableRange<float>(0.0f, static_cast<float>(filterTypes.size()), 1.0f),
            0.0f,
            [&](float value){ return ValueStringFuncs::ComboBox::valueToText(value, filterTypes); },
            [&](String text){ return ValueStringFuncs::ComboBox::textToValue(text, filterTypes); });
    }
}

AudioProcessorEditor* MMEQPlugin::createEditor()
{
    return new MMEQPluginEditor(*this);
}

void MMEQPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getTotalNumInputChannels())
    };

    for (size_t i = 0; i < filters.size(); ++i)
        filters[i].prepare(spec);
}

void MMEQPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    for (size_t i = 0; i < filters.size(); ++i)
    {
        filters[i].params->cutoff = getUnnormalizedValue(eqParams[i].paramCutoff);
        filters[i].params->gain = getUnnormalizedValue(eqParams[i].paramGain);
        filters[i].params->q = getUnnormalizedValue(eqParams[i].paramQ);
        filters[i].process(context);
    }
}
