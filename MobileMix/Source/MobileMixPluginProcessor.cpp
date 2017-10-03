/*
  ==============================================================================

    MobileMixPluginProcessor.cpp
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginProcessor.h"
#include "MobileMixPluginEditor.h"

#include "Core/MobileMixPluginFormat.h"
#include "Internal Plugins/MMGainPlugin.h"

MobileMixAudioProcessor::MobileMixAudioProcessor() :
    chainTree("CHAIN"),
    params(*this, nullptr)
{
    params.state = ValueTree("ROOT");
    params.state.addChild(chainTree, -1, nullptr);

    formatManager.addFormat(new MobileMixPluginFormat(*this, chainTree));
}

MobileMixAudioProcessor::~MobileMixAudioProcessor()
{
}

void MobileMixAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}

void MobileMixAudioProcessor::releaseResources()
{
}

bool MobileMixAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // We're assuming EVERYTHING in this plugin will ALWAYS be stereo.
    return (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::stereo());
}

void MobileMixAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
}

AudioProcessorEditor* MobileMixAudioProcessor::createEditor()
{
    return new MobileMixAudioProcessorEditor(*this);
}

bool MobileMixAudioProcessor::hasEditor() const
{
    return true;
}

const String MobileMixAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MobileMixAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool MobileMixAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double MobileMixAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MobileMixAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
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

static XmlElement* nodeToXML(AudioProcessorChain::Node* const node)
{
    AudioPluginInstance* instance = dynamic_cast<AudioPluginInstance*>(node->getProcessor());
    assert(instance); // Otherwise something is very wrong with our state...
    XmlElement* nodeXML = new XmlElement("FILTER");
    nodeXML->addChildElement(instance->getPluginDescription().createXml());

    XmlElement* stateXML = new XmlElement("STATE");
    MemoryBlock stateBlock;
    instance->getStateInformation(stateBlock);
    stateXML->addTextElement(stateBlock.toBase64Encoding());
    nodeXML->addChildElement(stateXML);

    // We could also save bus state here too, but since we're doing strictly
    // stereo-only we're going to ignore it.
    return nodeXML;
}

void MobileMixAudioProcessor::xmlToNode(const XmlElement& xml)
{
    PluginDescription description;
    forEachXmlChildElement(xml, element)
    {
        if (description.loadFromXml(*element))
            break;
    }

    String error;
    AudioPluginInstance* instance = formatManager.createPluginInstance(description, chain.getSampleRate(), chain.getBlockSize(), error);
    assert(instance); // This should never occur because all our plugins are built-in!

    AudioProcessorChain::Node* node = chain.addNode(instance);
    const XmlElement* const state = xml.getChildByName("STATE");
    assert(state); // Possibly deformed XML document...
    MemoryBlock stateBlock;
    stateBlock.fromBase64Encoding(state->getAllSubText());
    node->getProcessor()->setStateInformation(stateBlock.getData(), static_cast<int>(stateBlock.getSize()));
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
