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
        ValueStringFuncs::Gain::range,
        1.0f,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramGainL = state.createAndAddParameter(
        addPrefixToParameterName("Gain L"),
        addPrefixToParameterName("Gain L"),
        ValueStringFuncs::Gain::unit,
        ValueStringFuncs::Gain::range,
        1.0f,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramGainR = state.createAndAddParameter(
        addPrefixToParameterName("Gain R"),
        addPrefixToParameterName("Gain R"),
        ValueStringFuncs::Gain::unit,
        ValueStringFuncs::Gain::range,
        1.0f,
        ValueStringFuncs::Gain::valueToText,
        ValueStringFuncs::Gain::textToValue);

    paramPan = state.createAndAddParameter(
        addPrefixToParameterName("Pan"),
        addPrefixToParameterName("Pan"),
        ValueStringFuncs::Pan::unit,
        NormalisableRange<float>(-45.0f, 45.0f, 1.0f),
        0.0f,
        [](float value){ return ValueStringFuncs::Generic::valueToText(value, ValueStringFuncs::Pan::unit, 0); },
        ValueStringFuncs::Generic::textToValue);

    paramPhaseDelayL = state.createAndAddParameter(
        addPrefixToParameterName("Phase Delay L"),
        addPrefixToParameterName("Phase Delay L"),
        ValueStringFuncs::Milliseconds::unit,
        NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        [](float value){ return ValueStringFuncs::Generic::valueToText(value, ValueStringFuncs::Milliseconds::unit, 0); },
        ValueStringFuncs::Generic::textToValue);

    paramPhaseDelayR = state.createAndAddParameter(
        addPrefixToParameterName("Phase Delay R"),
        addPrefixToParameterName("Phase Delay R"),
        ValueStringFuncs::Milliseconds::unit,
        NormalisableRange<float>(0.0f, 1000.0f, 1.0f),
        0.0f,
        [](float value){ return ValueStringFuncs::Generic::valueToText(value, ValueStringFuncs::Milliseconds::unit, 0); },
        ValueStringFuncs::Generic::textToValue);

    paramPhaseInvertL = state.createAndAddParameter(
        addPrefixToParameterName("Phase Invert L"),
        addPrefixToParameterName("Phase Invert L"),
        {},
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        0.0f,
        ValueStringFuncs::OnOff::valueToText,
        ValueStringFuncs::OnOff::textToValue);

    paramPhaseInvertR = state.createAndAddParameter(
        addPrefixToParameterName("Phase Invert R"),
        addPrefixToParameterName("Phase Invert R"),
        {},
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        0.0f,
        ValueStringFuncs::OnOff::valueToText,
        ValueStringFuncs::OnOff::textToValue);
}

AudioProcessorEditor* MMGainPlugin::createEditor()
{
    return new MMGainPluginEditor(*this);
}

void MMGainPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec stereoSpec {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    };

    dsp::ProcessSpec monoSpec {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        1
    };

    delayL.params->maxDelay = static_cast<size_t>(sampleRate / 10.0); // 100 ms max delay
    delayR.params->maxDelay = static_cast<size_t>(sampleRate / 10.0);

    gainL.prepare(monoSpec);
    gainR.prepare(monoSpec);
    gainCenter.prepare(stereoSpec);
    pan.prepare(stereoSpec);
    delayL.prepare(monoSpec);
    delayR.prepare(monoSpec);
    invertPhaseL.prepare(monoSpec);
    invertPhaseR.prepare(monoSpec);
}

void MMGainPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // Update parameters
    gainL.params->gain = getUnnormalizedValue(paramGainL);
    gainR.params->gain = getUnnormalizedValue(paramGainR);
    gainCenter.params->gain = getUnnormalizedValue(paramGain);
    pan.params->pan = getUnnormalizedValue(paramPan);
    delayL.params->samplesToDelay = getUnnormalizedValue(paramPhaseDelayL);
    delayR.params->samplesToDelay = getUnnormalizedValue(paramPhaseDelayR);
    invertPhaseL.params->invert = getUnnormalizedValue(paramPhaseInvertL);
    invertPhaseR.params->invert = getUnnormalizedValue(paramPhaseInvertR);

    // Create processing blocks
    dsp::AudioBlock<float> blockStereo(buffer);
    dsp::ProcessContextReplacing<float> contextStereo(blockStereo);

    dsp::AudioBlock<float> blockL = blockStereo.getSingleChannelBlock(0);
    dsp::ProcessContextReplacing<float> contextL(blockL);

    dsp::AudioBlock<float> blockR = blockStereo.getSingleChannelBlock(1);
    dsp::ProcessContextReplacing<float> contextR(blockR);

    // Run processing
    gainL.process(contextL);
    gainR.process(contextR);
    gainCenter.process(contextStereo);
    pan.process(contextStereo);
    delayL.process(contextL);
    invertPhaseL.process(contextL);
    delayR.process(contextR);
    invertPhaseR.process(contextR);
    goniometerSource.process(buffer);
}
