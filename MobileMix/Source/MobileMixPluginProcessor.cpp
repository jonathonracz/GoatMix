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

MobileMixAudioProcessor::MobileMixAudioProcessor() :
    AudioProcessor(BusesProperties()
        .withInput("Input", AudioChannelSet::stereo(), true)
        .withOutput("Output", AudioChannelSet::stereo(), true)),
    chainTree("CHAIN"),
    params(*this, &undoManager)
{
    // Add top-level parameters here (currently none).

    // We only need the format manager to create the plugins once at load time.
    // They will remain until unload, so we can free them afterward (as opposed
    // to keeping them around as members).
    AudioPluginFormatManager formatManager;
    MobileMixPluginFormat* pluginFormat = new MobileMixPluginFormat(params);
    formatManager.addFormat(pluginFormat);

    OwnedArray<PluginDescription> mobileMixPluginList;
    pluginFormat->getAllPluginsInExpectedParameterOrder(mobileMixPluginList);
    for (int i = 0; i < mobileMixPluginList.size(); ++i)
    {
        String errorMessage;
        // We only have one plugin type registered, so we can be guaranteed this
        // static cast will succeed.
        MobileMixPluginInstance* instance = static_cast<MobileMixPluginInstance*>(formatManager.createPluginInstance(*mobileMixPluginList[i], 0, 0, errorMessage));
        jassert(instance && errorMessage.isEmpty());
        instance->MobileMixPluginInstance::registerParameters();
        instance->registerParameters();
        chain.addNode(instance);
        chainTree.getOrCreateChildWithName(instance->getName(), nullptr);
    }

    ValueTree rootState("ROOT");
    rootState.addChild(chainTree, -1, nullptr);
    rootState.addListener(this);
    params.state = rootState;
    addListener(this);
}

MobileMixAudioProcessor::~MobileMixAudioProcessor()
{
    chainTree.removeListener(this);
    params.state.removeListener(this);
}

void MobileMixAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    chain.prepareToPlay(sampleRate, samplesPerBlock);
}

void MobileMixAudioProcessor::releaseResources()
{
}

bool MobileMixAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // We're assuming EVERYTHING in this plugin will ALWAYS be stereo.
    return ((layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::stereo()));
}

void MobileMixAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    chain.processBlock(buffer, midiMessages);
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
    return static_cast<int>(presets.size());
}

int MobileMixAudioProcessor::getCurrentProgram()
{
    return currentPresetIndex;
}

void MobileMixAudioProcessor::setCurrentProgram(int index)
{
    currentPresetIndex = index;
    setStateInformation(presets[index].data, presets[index].dataSize);
}

const String MobileMixAudioProcessor::getProgramName(int index)
{
    return presets[index].name;
}

void MobileMixAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void MobileMixAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    suspendProcessing(true);
    std::unique_ptr<XmlElement> xml(params.state.createXml());
    AudioProcessor::copyXmlToBinary(*xml, destData);
    suspendProcessing(false);
}

void MobileMixAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    suspendProcessing(true);

    if (sizeInBytes > 0)
    {
        std::unique_ptr<XmlElement> xml(AudioProcessor::getXmlFromBinary(data, sizeInBytes));
        ValueTree newState = ValueTree::fromXml(*xml);
        if (newState.isValid())
            params.state = newState;
        undoManager.clearUndoHistory();
    }

    suspendProcessing(false);
}

int MobileMixAudioProcessor::indexOfNodeWithName(String name) const
{
    for (int i = 0; i < chain.getNumNodes(); ++i)
        if (chain.getNode(i)->getProcessor()->getName() == name)
            return i;

    jassert(false);
    return -1;
}

void MobileMixAudioProcessor::valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    jassert(parentTreeWhoseChildrenHaveMoved == chainTree);
    if (parentTreeWhoseChildrenHaveMoved == chainTree)
    {
        chain.moveNode(oldIndex, newIndex);
    }
}

void MobileMixAudioProcessor::valueTreeRedirected(ValueTree &treeWhichHasBeenChanged)
{
    if (treeWhichHasBeenChanged == params.state)
    {
        jassert(params.state.isValid());
        chainTree = params.state.getChildWithName("CHAIN"); // Will trigger this again with the below condition.
    }
    else if (treeWhichHasBeenChanged == chainTree)
    {
        jassert(chainTree.isValid());
        // If we ever add nodes and need backwards compatibility, this will need to be removed.
        jassert(chainTree.getNumChildren() == chain.getNumNodes());
        for (int i = 0; i < chainTree.getNumChildren(); ++i)
        {
            ValueTree chainNodeTree = chainTree.getChild(i);
            int currentNodeIndex = indexOfNodeWithName(chainNodeTree.getType().toString());
            if (currentNodeIndex > -1 && currentNodeIndex != i)
            {
                chain.moveNode(currentNodeIndex, i);
            }
        }
    }
}

void MobileMixAudioProcessor::audioProcessorParameterChangeGestureBegin(AudioProcessor* processor, int parameterIndex)
{
    // Even though this is called from the audio thread without a lock we're
    // going to call this "close enough" given the amount of time left to
    // complete this project. It's not allocating or anything, just creating
    // a minor race condition.
    undoManager.beginNewTransaction("Parameter change");
}

void MobileMixAudioProcessor::audioProcessorParameterChangeGestureEnd(AudioProcessor* processor, int parameterIndex)
{
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
