/*
  ==============================================================================

    MobileMixPluginInstance.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginInstance.h"
#include "../GUI/ValueStringFuncs.h"
#include "MobileMixPluginInstanceEditor.h"

MobileMixPluginInstance::MobileMixPluginInstance(AudioProcessorValueTreeState& _state) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(_state)
{
    meterSource.allocateMeters(getMainBusNumInputChannels());
}

MobileMixPluginInstance::~MobileMixPluginInstance()
{
}

void MobileMixPluginInstance::registerParameters()
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

bool MobileMixPluginInstance::isBypassed() const
{
    jassert(paramBypass->getValue() == 0.0f || paramBypass->getValue() == 1.0f);
    return static_cast<bool>(paramBypass->getValue());
}

float MobileMixPluginInstance::getUnnormalizedValue(AudioProcessorParameterWithID* param) const
{
    return *state.getRawParameterValue(param->paramID);
}

float MobileMixPluginInstance::getNormalizedValue(AudioProcessorParameterWithID* param) const
{
    return state.getParameterRange(param->paramID).convertFrom0to1(*state.getRawParameterValue(param->paramID));
}

const String MobileMixPluginInstance::addPrefixToParameterName(StringRef name) const
{
    return getName() + ": " + name;
}

const String MobileMixPluginInstance::stripPrefixFromParameterName(const String& name)
{
    return name.substring(name.indexOf(": ") + 2);
}

void MobileMixPluginInstance::fillInPluginDescription(PluginDescription &description) const
{
    description.name = getName();
    description.uid = description.name.hashCode();
    description.pluginFormatName = "Internal";
    description.manufacturerName = JucePlugin_Manufacturer;
    description.version = JucePlugin_VersionString;
    description.isInstrument = false;
}

void MobileMixPluginInstance::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
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

void MobileMixPluginInstance::releaseResources()
{
    releaseResourcesDerived();
}

void MobileMixPluginInstance::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (paramBypass->getValue() != 1.0f)
        processBlockDerived(buffer, midiMessages);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    meterSource.process(context);
}

bool MobileMixPluginInstance::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool MobileMixPluginInstance::hasEditor() const
{
    return true;
}

bool MobileMixPluginInstance::acceptsMidi() const
{
    return false;
}

bool MobileMixPluginInstance::producesMidi() const
{
    return false;
}

double MobileMixPluginInstance::getTailLengthSeconds() const
{
    return 0.0;
}

int MobileMixPluginInstance::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int MobileMixPluginInstance::getCurrentProgram()
{
    return 0;
}
