/*
  ==============================================================================

    MobileMixPluginInstance.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginInstance.h"

MobileMixPluginInstance::MobileMixPluginInstance(AudioProcessorValueTreeState& _state) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(_state)
{
    meterSource.resize(getMainBusNumOutputChannels(), 0);
}

MobileMixPluginInstance::~MobileMixPluginInstance()
{
}

void MobileMixPluginInstance::registerParameters()
{
    paramBypass = state.createAndAddParameter(addPrefixToParameterName("Bypass"),
                                              addPrefixToParameterName("Bypass"),
                                              "",
                                              NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                              0.0f,
                                              [](float value){ return (value != 1.0f) ? NEEDS_TRANS("False") : NEEDS_TRANS("True"); },
                                              nullptr);
}

bool MobileMixPluginInstance::isBypassed() const
{
    jassert(paramBypass->getValue() == 0.0f || paramBypass->getValue() == 1.0f);
    return static_cast<bool>(paramBypass->getValue());
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
}

void MobileMixPluginInstance::releaseResources()
{
}

void MobileMixPluginInstance::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    meterSource.measureBlock(buffer);
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

void MobileMixPluginInstance::setCurrentProgram(int index)
{
}

const String MobileMixPluginInstance::getProgramName(int index)
{
    return {};
}

void MobileMixPluginInstance::changeProgramName(int index, const String& newName)
{
}

void MobileMixPluginInstance::getStateInformation(MemoryBlock& destData)
{
}

void MobileMixPluginInstance::setStateInformation(const void* data, int sizeInBytes)
{
}

const String MobileMixPluginInstance::addPrefixToParameterName(StringRef name) const
{
    return getName() + ": " + name;
}

const String MobileMixPluginInstance::stripPrefixFromParameterName(const String& name)
{
    return name.substring(name.indexOf(": ") + 2);
}
