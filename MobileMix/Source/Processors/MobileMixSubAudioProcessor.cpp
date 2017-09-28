/*
  ==============================================================================

    MobileMixSubAudioProcessor.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixSubAudioProcessor.h"

MobileMixSubAudioProcessor::MobileMixSubAudioProcessor(AudioProcessor& rootProcessor,
                                                 AudioProcessorValueTreeState& parentState) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(rootProcessor, parentState)
{
}

MobileMixSubAudioProcessor::~MobileMixSubAudioProcessor()
{
}

void MobileMixSubAudioProcessor::fillInPluginDescription(PluginDescription &description) const
{
    description.name = getName();
    description.uid = description.name.hashCode();
    description.pluginFormatName = "Internal";
    description.manufacturerName = "GoatAudio";
    description.version = "1.0";
    description.isInstrument = false;
}

void MobileMixSubAudioProcessor::releaseResources()
{
}

bool MobileMixSubAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool MobileMixSubAudioProcessor::hasEditor() const
{
    return true;
}

bool MobileMixSubAudioProcessor::acceptsMidi() const
{
    return false;
}

bool MobileMixSubAudioProcessor::producesMidi() const
{
    return false;
}

double MobileMixSubAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MobileMixSubAudioProcessor::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int MobileMixSubAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MobileMixSubAudioProcessor::setCurrentProgram(int index)
{
}

const String MobileMixSubAudioProcessor::getProgramName(int index)
{
    return {};
}

void MobileMixSubAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void MobileMixSubAudioProcessor::getStateInformation(MemoryBlock& destData)
{
}

void MobileMixSubAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}
