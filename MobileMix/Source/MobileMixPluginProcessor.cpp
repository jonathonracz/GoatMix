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

    // We only need the format manager to create the plugins once at load time.
    // They will remain until unload, so we can free them afterward (as opposed
    // to keeping them around as members).
    AudioPluginFormatManager formatManager;
    MobileMixPluginFormat* pluginFormat = new MobileMixPluginFormat(*this, chainTree);
    formatManager.addFormat(pluginFormat);

    OwnedArray<PluginDescription> mobileMixPluginList;
    pluginFormat->getAllPluginsInExpectedParameterOrder(mobileMixPluginList);
    for (int i = 0; i < mobileMixPluginList.size(); ++i)
    {
        String errorMessage;
        // We only have one plugin type registered, so we can be guaranteed this
        // static cast will succeed.
        MobileMixPluginInstance* instance = static_cast<MobileMixPluginInstance*>(formatManager.createPluginInstance(*mobileMixPluginList[i], 0, 0, errorMessage));
        assert(instance && errorMessage.isEmpty());
        instance->registerParameters();
        instance->finalizeParametersAndAddToParentState();
        chain.addNode(instance);
    }
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
    XmlElement stateXML("STATE");
    XmlElement* chainXML = new XmlElement("CHAIN");
    stateXML.addChildElement(chainXML);
    for (int i = 0; i < chain.getNumNodes(); ++i)
    {
        AudioPluginInstance* instance = dynamic_cast<AudioPluginInstance*>(chain.getNode(i)->getProcessor());
        assert(instance); // Otherwise something is very wrong with our state...

        XmlElement* chainNodeXML = new XmlElement("NODE");
        chainXML->addChildElement(chainNodeXML);

        XmlElement* nodeDescriptionXML = new XmlElement("DESCRIPTION");
        chainNodeXML->addChildElement(nodeDescriptionXML);
        nodeDescriptionXML->addChildElement(instance->getPluginDescription().createXml());

        XmlElement* nodeStateXML = new XmlElement("STATE");
        chainNodeXML->addChildElement(nodeStateXML);
        MemoryBlock stateBlock;
        instance->getStateInformation(stateBlock);
        nodeStateXML->addTextElement(stateBlock.toBase64Encoding());
    }

    AudioProcessor::copyXmlToBinary(stateXML, destData);
}

void MobileMixAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> stateXML(AudioProcessor::getXmlFromBinary(data, sizeInBytes));
    XmlElement* chainXML = stateXML->getChildByName("CHAIN");
    assert(chainXML);
    if (!chainXML)
        return;

    for (int i = 0; i < chainXML->getNumChildElements(); ++i)
    {
        XmlElement* nodeFilterXML = chainXML->getChildElement(i);
        assert(nodeFilterXML->getTagName() == "NODE");
        //XmlElement*
    }
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

    /*
    String error;
    AudioPluginInstance* instance;
    for (int i = 0; i <
    assert(instance); // This should never occur because all our plugins are built-in and already instantiated!

    AudioProcessorChain::Node* node = chain.addNode(instance);
    const XmlElement* const state = xml.getChildByName("STATE");
    assert(state); // Possibly deformed XML document...
    MemoryBlock stateBlock;
    stateBlock.fromBase64Encoding(state->getAllSubText());
    node->getProcessor()->setStateInformation(stateBlock.getData(), static_cast<int>(stateBlock.getSize()));
     */
}

int MobileMixAudioProcessor::indexOfNodeWithPluginDescription(const PluginDescription& desc) const
{
    for (int i = 0; i < chain.getNumNodes(); ++i)
    {
        if (static_cast<AudioPluginInstance*>(chain.getNode(i)->getProcessor())->getPluginDescription().isDuplicateOf(desc))
        {
            return i;
        }
    }

    assert(false);
    return -1;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
