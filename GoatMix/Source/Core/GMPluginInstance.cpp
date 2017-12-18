/*
  ==============================================================================

    GMPluginInstance.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMPluginInstance.h"
#include "../GUI/ValueStringFuncs.h"
#include "GMPluginInstanceEditor.h"

GMPluginInstance::GMPluginInstance(AudioProcessorValueTreeState& _state) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(_state)
{
    meterSource.allocateMeters(getMainBusNumInputChannels());
}

GMPluginInstance::~GMPluginInstance()
{
}

void GMPluginInstance::registerParameters()
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

bool GMPluginInstance::isBypassed() const
{
    jassert(paramBypass->getValue() == 0.0f || paramBypass->getValue() == 1.0f);
    return static_cast<bool>(paramBypass->getValue());
}

float GMPluginInstance::getUnnormalizedValue(AudioProcessorParameterWithID* param) const
{
    return *state.getRawParameterValue(param->paramID);
}

float GMPluginInstance::getNormalizedValue(AudioProcessorParameterWithID* param) const
{
    return state.getParameterRange(param->paramID).convertFrom0to1(*state.getRawParameterValue(param->paramID));
}

const String GMPluginInstance::addPrefixToParameterName(StringRef name) const
{
    return getName() + ": " + name;
}

const String GMPluginInstance::stripPrefixFromParameterName(const String& name)
{
    return name.substring(name.indexOf(": ") + 2);
}

void GMPluginInstance::fillInPluginDescription(PluginDescription &description) const
{
    description.name = getName();
    description.uid = description.name.hashCode();
    description.pluginFormatName = "Internal";
    description.manufacturerName = JucePlugin_Manufacturer;
    description.version = JucePlugin_VersionString;
    description.isInstrument = false;
}

void GMPluginInstance::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
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

void GMPluginInstance::releaseResources()
{
    releaseResourcesDerived();
}

void GMPluginInstance::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (paramBypass->getValue() != 1.0f)
        processBlockDerived(buffer, midiMessages);

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    meterSource.process(context);
}

bool GMPluginInstance::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool GMPluginInstance::hasEditor() const
{
    return true;
}

bool GMPluginInstance::acceptsMidi() const
{
    return false;
}

bool GMPluginInstance::producesMidi() const
{
    return false;
}

double GMPluginInstance::getTailLengthSeconds() const
{
    return 0.0;
}

int GMPluginInstance::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int GMPluginInstance::getCurrentProgram()
{
    return 0;
}
