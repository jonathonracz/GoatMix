/*
  ==============================================================================

    MobileMixAudioProcessor.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixAudioProcessor.h"

MobileMixAudioProcessor::MobileMixAudioProcessor(AudioProcessor& rootProcessor,
                                                 AudioProcessorValueTreeState& parentState) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(rootProcessor, parentState)
{
}

MobileMixAudioProcessor::~MobileMixAudioProcessor()
{
}

void MobileMixAudioProcessor::fillInPluginDescription(PluginDescription &description) const
{
    description.name = getName();
    description.uid = description.name.hashCode();
    description.pluginFormatName = "Internal";
    description.manufacturerName = "GoatAudio";
    description.version = "1.0";
    description.isInstrument = false;
}

void MobileMixAudioProcessor::releaseResources()
{
}

bool MobileMixAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool MobileMixAudioProcessor::hasEditor() const
{
    return true;
}

bool MobileMixAudioProcessor::acceptsMidi() const
{
    return false;
}

bool MobileMixAudioProcessor::producesMidi() const
{
    return false;
}

double MobileMixAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MobileMixAudioProcessor::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int MobileMixAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MobileMixAudioProcessor::setCurrentProgram(int index)
{
}

const String MobileMixAudioProcessor::getProgramName(int index)
{
    return {};
}

void MobileMixAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void MobileMixAudioProcessor::getStateInformation(MemoryBlock& destData)
{
}

void MobileMixAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}
