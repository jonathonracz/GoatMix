/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP/Gain.h"
#include "DSP/PitchShift.h"
#include "DSP/BufferSizeAdaptor.h"

#include "Processors/GainProcessor.h"

const char* orderedIndexValueKey = "orderedIndex";

MobileMixAudioProcessor::MobileMixAudioProcessor()
{
    AudioProcessorGraph::Node* inputNode = graph.addNode(new juce::AudioProcessorGraph::AudioGraphIOProcessor(juce::AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType::audioInputNode));
    inputNode->properties.set(orderedIndexValueKey, 0);
    AudioProcessorGraph::Node* gainNode = graph.addNode(new GainProcessor);
    gainNode->properties.set(orderedIndexValueKey, 1);
    AudioProcessorGraph::Node* compressorNode = graph.addNode(new GainProcessor);
    compressorNode->properties.set(orderedIndexValueKey, 2);
    AudioProcessorGraph::Node* eqNode = graph.addNode(new GainProcessor);
    eqNode->properties.set(orderedIndexValueKey, 3);
    AudioProcessorGraph::Node* distortionNode = graph.addNode(new GainProcessor);
    distortionNode->properties.set(orderedIndexValueKey, 4);
    AudioProcessorGraph::Node* pitchNode = graph.addNode(new GainProcessor);
    pitchNode->properties.set(orderedIndexValueKey, 5);
    AudioProcessorGraph::Node* reverbNode = graph.addNode(new GainProcessor);
    reverbNode->properties.set(orderedIndexValueKey, 6);
    AudioProcessorGraph::Node* outputNode = graph.addNode(new GainProcessor);
    outputNode->properties.set(orderedIndexValueKey, 7);

    // String our initial node layout together programatically.
    for (int i = 0; i < graph.getNumNodes() - 1; ++i)
    {
        connect(getNodeWithOrderedIndex(i), getNodeWithOrderedIndex(i + 1));
    }
}

MobileMixAudioProcessor::~MobileMixAudioProcessor()
{
}

void MobileMixAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    graph.prepareToPlay(sampleRate, samplesPerBlock);
}

void MobileMixAudioProcessor::releaseResources()
{
    graph.releaseResources();
}

bool MobileMixAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // We're assuming EVERYTHING in this plugin will ALWAYS be stereo.
    return (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::stereo());
}

void MobileMixAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    graph.processBlock(buffer, midiMessages);
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

AudioProcessorGraph::Node* MobileMixAudioProcessor::getNodeWithOrderedIndex(int index)
{
    assert(index < graph.getNumNodes());
    for (int i = 0; i < graph.getNumNodes(); ++i)
    {
        AudioProcessorGraph::Node* potentialNode = graph.getNode(i);
        if (potentialNode->properties[orderedIndexValueKey].equals(i))
        {
            return potentialNode;
        }
    }
    assert(false); // Inconsistent state!
}

void MobileMixAudioProcessor::moveNodeFromBetweenCurrentPairToBetweenNewPair(AudioProcessorGraph::Node* node,
    AudioProcessorGraph::Node* newPrevious,
    AudioProcessorGraph::Node* newNext)
{
    int nodeIdx = node->properties[orderedIndexValueKey];
    assert(nodeIdx > 0 && nodeIdx < graph.getNumNodes() - 1);

    AudioProcessorGraph::Node* currentPrevious = getNodeWithOrderedIndex(nodeIdx - 1);
    AudioProcessorGraph::Node* currentNext = getNodeWithOrderedIndex(nodeIdx + 1);

    disconnect(currentPrevious, node);
    disconnect(node, currentNext);
    connect(currentPrevious, currentNext);

    disconnect(newPrevious, newNext);
    connect(newPrevious, node);
    connect(node, newNext);
}

void MobileMixAudioProcessor::incrementNodeAtOrderedIndex(int index)
{
    assert(index > 0 && index < graph.getNumNodes() - 2);
    AudioProcessorGraph::Node* node = getNodeWithOrderedIndex(index);
    AudioProcessorGraph::Node* newPrevious = getNodeWithOrderedIndex(index + 1);
    AudioProcessorGraph::Node* newNext = getNodeWithOrderedIndex(index + 2);
    moveNodeFromBetweenCurrentPairToBetweenNewPair(node, newPrevious, newNext);
}

void MobileMixAudioProcessor::decrementNodeAtOrderedIndex(int index)
{
    assert(index > 1 && index < graph.getNumNodes() - 1);
    AudioProcessorGraph::Node* node = getNodeWithOrderedIndex(index);
    AudioProcessorGraph::Node* newPrevious = getNodeWithOrderedIndex(index - 1);
    AudioProcessorGraph::Node* newNext = getNodeWithOrderedIndex(index - 2);
    moveNodeFromBetweenCurrentPairToBetweenNewPair(node, newPrevious, newNext);
}

void MobileMixAudioProcessor::connect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst)
{
    assert(src && dst);
    assert(src->getProcessor()->getMainBusNumOutputChannels() == dst->getProcessor()->getMainBusNumInputChannels());
    int connectionsToMake = std::min(src->getProcessor()->getMainBusNumOutputChannels(), dst->getProcessor()->getMainBusNumInputChannels());
    for (int i = 0; i < connectionsToMake; ++i)
        assert(graph.addConnection(src->nodeId, i, dst->nodeId, i));
}

void MobileMixAudioProcessor::disconnect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst)
{
    assert(src && dst);
    assert(src->getProcessor()->getMainBusNumOutputChannels() == dst->getProcessor()->getMainBusNumInputChannels());
    int connectionsToRemove = std::min(src->getProcessor()->getMainBusNumOutputChannels(), dst->getProcessor()->getMainBusNumInputChannels());
    for (int i = 0; i < connectionsToRemove; ++i)
        assert(graph.removeConnection(src->nodeId, i, dst->nodeId, i));
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
