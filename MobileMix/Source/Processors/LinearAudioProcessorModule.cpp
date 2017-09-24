/*
  ==============================================================================

    LinearAudioProcessorModule.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "LinearAudioProcessorModule.h"

LinearAudioProcessorModule::LinearAudioProcessorModule(AudioChannelSet channelLayout) :
    AudioProcessor(BusesProperties()
        .withInput("Input",  channelLayout)
        .withOutput("Output", channelLayout)),
    paramState(*this, nullptr)
{

}

LinearAudioProcessorModule::~LinearAudioProcessorModule()
{
}

void LinearAudioProcessorModule::releaseResources()
{
}

bool LinearAudioProcessorModule::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool LinearAudioProcessorModule::hasEditor() const
{
    return true;
}

bool LinearAudioProcessorModule::acceptsMidi() const
{
    return false;
}

bool LinearAudioProcessorModule::producesMidi() const
{
    return false;
}

double LinearAudioProcessorModule::getTailLengthSeconds() const
{
    return 0.0;
}

int LinearAudioProcessorModule::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int LinearAudioProcessorModule::getCurrentProgram()
{
    return 0;
}

void LinearAudioProcessorModule::setCurrentProgram(int index)
{
}

const String LinearAudioProcessorModule::getProgramName(int index)
{
    return {};
}

void LinearAudioProcessorModule::changeProgramName(int index, const String& newName)
{
}

void LinearAudioProcessorModule::getStateInformation(MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> stateXML(paramState.state.createXml());
    if (stateXML)
        AudioProcessor::copyXmlToBinary(*stateXML, destData);
}

void LinearAudioProcessorModule::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> stateXML(AudioProcessor::getXmlFromBinary(data, sizeInBytes));
    if (stateXML)
        paramState.state.fromXml(*stateXML);
}
