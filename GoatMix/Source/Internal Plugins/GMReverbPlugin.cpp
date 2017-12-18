/*
  ==============================================================================

    GMReverbPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMReverbPlugin.h"
#include "GMReverbPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

GMReverbPlugin::GMReverbPlugin(AudioProcessorValueTreeState& state) :
    GMPluginInstance(state)
{
    lowPass.params->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    highPass.params->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
}

void GMReverbPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramRoomSize = state.createAndAddParameter(
        addPrefixToParameterName("Room Size"),
        addPrefixToParameterName("Room Size"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        0.5f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Percent::textToValue);

    paramDamping = state.createAndAddParameter(
        addPrefixToParameterName("Damping"),
        addPrefixToParameterName("Damping"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        0.5f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Percent::textToValue);

    paramWidth = state.createAndAddParameter(
        addPrefixToParameterName("Width"),
        addPrefixToParameterName("Width"),
        ValueStringFuncs::Percent::unit,
        ValueStringFuncs::Percent::range,
        0.5f,
        ValueStringFuncs::Percent::valueToText,
        ValueStringFuncs::Percent::textToValue);

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
        ValueStringFuncs::Percent::textToValue);

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
        ValueStringFuncs::Percent::textToValue);
}

GMPluginInstanceEditor* GMReverbPlugin::createGoatMixEditor()
{
    return new GMReverbPluginEditor(*this);
}

void GMReverbPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
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

void GMReverbPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dryWet.params->wetDry = getUnnormalizedValue(paramDryWet);
    reverb.params->roomSize = getUnnormalizedValue(paramRoomSize);
    reverb.params->damping = getUnnormalizedValue(paramDamping);
    reverb.params->width = getUnnormalizedValue(paramWidth);
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
