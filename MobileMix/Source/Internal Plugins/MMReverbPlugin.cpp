/*
  ==============================================================================

    MMReverbPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMReverbPlugin.h"
#include "MMReverbPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

MMReverbPlugin::MMReverbPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
    lowPass.params->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    highPass.params->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
}

void MMReverbPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramRoomSize = state.createAndAddParameter(
        addPrefixToParameterName("Room Size"),
        addPrefixToParameterName("Room Size"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        50.0f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Generic::textToValue);

    paramDamping = state.createAndAddParameter(
        addPrefixToParameterName("Damping"),
        addPrefixToParameterName("Damping"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        50.0f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Generic::textToValue);

    paramWidth = state.createAndAddParameter(
        addPrefixToParameterName("Width"),
        addPrefixToParameterName("Width"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        50.0f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Generic::textToValue);

    paramFreeze = state.createAndAddParameter(
        addPrefixToParameterName("Freeze"),
        addPrefixToParameterName("Freeze"),
        {},
        ValueStringFuncs::OnOff::range,
        0.0f,
        ValueStringFuncs::OnOff::valueToText,
        ValueStringFuncs::OnOff::textToValue);

    paramHighPassEnable = state.createAndAddParameter(
        addPrefixToParameterName("High Pass Enable"),
        addPrefixToParameterName("High Pass Enable"),
        {},
        ValueStringFuncs::OnOff::range,
        0.0f,
        ValueStringFuncs::OnOff::valueToText,
        ValueStringFuncs::OnOff::textToValue);

    paramHighPass = state.createAndAddParameter(
        addPrefixToParameterName("High Pass"),
        addPrefixToParameterName("High Pass"),
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

    paramLowPass = state.createAndAddParameter(addPrefixToParameterName("LowPass"),
        addPrefixToParameterName("Low Pass"),
        ValueStringFuncs::Filter::unit,
        ValueStringFuncs::Filter::range,
        ValueStringFuncs::Filter::defaultValue,
        ValueStringFuncs::Filter::valueToText,
        ValueStringFuncs::Generic::textToValue);

    paramDryWet = state.createAndAddParameter(
        addPrefixToParameterName("Dry/Wet"),
        addPrefixToParameterName("Dry/Wet"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        0.0f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Generic::textToValue);
}

MobileMixPluginInstanceEditor* MMReverbPlugin::createMobileMixEditor()
{
    return new MMReverbPluginEditor(*this);
}

void MMReverbPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    };

    dryWet.prepare(spec);
    reverb.prepare(spec);
    lowPass.prepare(spec);
    highPass.prepare(spec);
}

void MMReverbPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dryWet.params->wetDry = getUnnormalizedValue(paramDryWet) / 100.0f;
    reverb.params->roomSize = getUnnormalizedValue(paramRoomSize) / 100.0f;
    reverb.params->damping = getUnnormalizedValue(paramDamping) / 100.0f;
    reverb.params->width = getUnnormalizedValue(paramWidth) / 100.0f;
    reverb.params->freeze = static_cast<bool>(getUnnormalizedValue(paramFreeze));
    lowPass.params->cutoff = getUnnormalizedValue(paramLowPass);
    highPass.params->cutoff = getUnnormalizedValue(paramHighPass);

    dryWet.copyDrySignal(buffer);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    reverb.process(context);
    if (static_cast<bool>(getUnnormalizedValue(paramLowPassEnable)))
        lowPass.process(context);
    if (static_cast<bool>(getUnnormalizedValue(paramHighPassEnable)))
        highPass.process(context);
    dryWet.process(context);
}
