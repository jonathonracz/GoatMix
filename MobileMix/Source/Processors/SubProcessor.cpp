/*
  ==============================================================================

    SubProcessor.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "SubProcessor.h"

SubProcessor::SubProcessor() :
    AudioProcessor(BusesProperties()
        .withInput("Input",  AudioChannelSet::stereo(), true)
        .withOutput("Output", AudioChannelSet::stereo(), true)),
    paramState(*this, nullptr)
{

}

SubProcessor::~SubProcessor()
{
}

void SubProcessor::releaseResources()
{
}

bool SubProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::stereo());
}

bool SubProcessor::hasEditor() const
{
    return true;
}

bool SubProcessor::acceptsMidi() const
{
    return false;
}

bool SubProcessor::producesMidi() const
{
    return false;
}

double SubProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SubProcessor::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int SubProcessor::getCurrentProgram()
{
    return 0;
}

void SubProcessor::setCurrentProgram(int index)
{
}

const String SubProcessor::getProgramName(int index)
{
    return {};
}

void SubProcessor::changeProgramName(int index, const String& newName)
{
}

void SubProcessor::getStateInformation(MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> stateXML(paramState.state.createXml());
    if (stateXML)
        AudioProcessor::copyXmlToBinary(*stateXML, destData);
}

void SubProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> stateXML(AudioProcessor::getXmlFromBinary(data, sizeInBytes));
    if (stateXML)
        paramState.state.fromXml(*stateXML);
}
