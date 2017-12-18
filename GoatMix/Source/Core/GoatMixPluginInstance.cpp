/*
  ==============================================================================

    GoatMixPluginInstance.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GoatMixPluginInstance.h"
#include "../GUI/ValueStringFuncs.h"
#include "GoatMixPluginInstanceEditor.h"

GoatMixPluginInstance::GoatMixPluginInstance(AudioProcessorValueTreeState& _state) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(_state)
{
    meterSource.allocateMeters(getMainBusNumInputChannels());
}

GoatMixPluginInstance::~GoatMixPluginInstance()
{
}

void GoatMixPluginInstance::registerParameters()
{
    paramBypass = state.createAndAddParameter(
        addPrefixToParameterName("Bypass"),
        addPrefixToParameterName("Bypass"),
        {},
        ValueStringFuncs::OnOff::range,
        0.0f,
        ValueStringFuncs::OnOff::valueToText,
        ValueStringFuncs::OnOff::textToValue);
}

bool GoatMixPluginInstance::isBypassed() const
{
    jassert(paramBypass->getValue() == 0.0f || paramBypass->getValue() == 1.0f);
    return static_cast<bool>(paramBypass->getValue());
}

float GoatMixPluginInstance::getUnnormalizedValue(AudioProcessorParameterWithID* param) const
{
    return *state.getRawParameterValue(param->paramID);
}

float GoatMixPluginInstance::getNormalizedValue(AudioProcessorParameterWithID* param) const
{
    return state.getParameterRange(param->paramID).convertFrom0to1(*state.getRawParameterValue(param->paramID));
}

const String GoatMixPluginInstance::addPrefixToParameterName(StringRef name) const
{
    return getName() + ": " + name;
}

const String GoatMixPluginInstance::stripPrefixFromParameterName(const String& name)
{
    return name.substring(name.indexOf(": ") + 2);
}

void GoatMixPluginInstance::fillInPluginDescription(PluginDescription &description) const
{
    description.name = getName();
    description.uid = description.name.hashCode();
    description.pluginFormatName = "Internal";
    description.manufacturerName = JucePlugin_Manufacturer;
    description.version = JucePlugin_VersionString;
    description.isInstrument = false;
}

void GoatMixPluginInstance::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    preparedSampleRate = sampleRate;
    preparedBlockSize = maximumExpectedSamplesPerBlock;
    meterSource.prepare(dsp::ProcessSpec{
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    });
    prepareToPlayDerived(sampleRate, maximumExpectedSamplesPerBlock);
}

void GoatMixPluginInstance::releaseResources()
{
    releaseResourcesDerived();
}

void GoatMixPluginInstance::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (paramBypass->getValue() != 1.0f)
        processBlockDerived(buffer, midiMessages);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    meterSource.process(context);
}

bool GoatMixPluginInstance::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool GoatMixPluginInstance::hasEditor() const
{
    return true;
}

bool GoatMixPluginInstance::acceptsMidi() const
{
    return false;
}

bool GoatMixPluginInstance::producesMidi() const
{
    return false;
}

double GoatMixPluginInstance::getTailLengthSeconds() const
{
    return 0.0;
}

int GoatMixPluginInstance::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int GoatMixPluginInstance::getCurrentProgram()
{
    return 0;
}
