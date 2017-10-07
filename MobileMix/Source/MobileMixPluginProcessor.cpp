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
    // Add top-level parameters here (currently none).

    params.state = ValueTree("ROOT");
    params.state.addChild(chainTree, -1, nullptr);

    params.state.addListener(this);

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
        instance->MobileMixPluginInstance::registerParameters();
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
    std::unique_ptr<XmlElement> xml(params.state.createXml());
    AudioProcessor::copyXmlToBinary(*xml, destData);
}

void MobileMixAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    AudioProcessor::getXmlFromBinary(data, sizeInBytes);
}

int MobileMixAudioProcessor::indexOfNodeWithName(String name) const
{
    for (int i = 0; i < chain.getNumNodes(); ++i)
        if (chain.getNode(i)->getProcessor()->getName() == name)
            return i;

    assert(false);
    return -1;
}

void MobileMixAudioProcessor::valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    assert(parentTreeWhoseChildrenHaveMoved == chainTree);
    if (parentTreeWhoseChildrenHaveMoved == chainTree)
    {
        assert(chainTree.getChild(newIndex).getType() == Identifier(chain.getNode(oldIndex)->getProcessor()->getName()));
        chain.moveNode(oldIndex, newIndex);
    }
}

void MobileMixAudioProcessor::valueTreeRedirected(ValueTree &treeWhichHasBeenChanged)
{
    if (treeWhichHasBeenChanged == params.state)
    {
        assert(params.state.isValid());
        chainTree = params.state.getChildWithName("CHAIN"); // Will trigger this again with the below condition.
    }
    else if (treeWhichHasBeenChanged == chainTree)
    {
        assert(chainTree.isValid());
        // If we ever add nodes and need backwards compatibility, this will need to be removed.
        assert(chainTree.getNumChildren() == chain.getNumNodes());
        for (int i = 0; i < chainTree.getNumChildren(); ++i)
        {
            ValueTree chainNodeTree = chainTree.getChild(i);
            int currentNodeIndex = indexOfNodeWithName(chainNodeTree.getType().toString());
            if (currentNodeIndex > -1)
            {
                static_cast<MobileMixPluginInstance*>(chain.getNode(currentNodeIndex)->getProcessor())->getParameterState().state = chainNodeTree;
                if (currentNodeIndex != i)
                    chain.moveNode(currentNodeIndex, i);
            }
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
