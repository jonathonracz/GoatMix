/*
  ==============================================================================

    LinearAudioProcessorGraph.cpp
    Created: 17 Sep 2017 11:46:41am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "LinearAudioProcessorGraph.h"
#include "LinearAudioProcessorGraphEditor.h"
//#include "GainProcessor.h"

const char* orderedIndexProperty = "orderedIndex";

LinearAudioProcessorGraph::LinearAudioProcessorGraph(AudioChannelSet channelLayout) :
    AudioProcessor(BusesProperties()
                   .withInput("Input",  AudioChannelSet::stereo())
                   .withOutput("Output", AudioChannelSet::stereo()))
{
    input = graph.addNode(new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType::audioInputNode));
    output = graph.addNode(new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType::audioOutputNode));
    connect(input, output);

    //addProcessor(new GainProcessor);
    //addProcessor(new GainProcessor);
}

LinearAudioProcessorGraph::~LinearAudioProcessorGraph()
{
}

void LinearAudioProcessorGraph::addProcessor(AudioProcessor* processor, int insertIndex)
{
    AudioProcessorGraph::Node* beforeNode = getNodeWithOrderedIndexIncludingIO(getNumProcessors());
    disconnect(beforeNode, output);

    int newOrderedProcessorIndex = getNumProcessors();
    AudioProcessorGraph::Node* newNode = graph.addNode(processor);
    newNode->properties.set(orderedIndexProperty, newOrderedProcessorIndex);

    connect(beforeNode, newNode);
    connect(newNode, output);
    if (insertIndex != -1)
        moveProcessor(newOrderedProcessorIndex, insertIndex);
}

void LinearAudioProcessorGraph::removeProcessor(int index)
{
    AudioProcessorGraph::Node* processor = getNodeWithOrderedIndex(index);
    AudioProcessorGraph::Node* processorBefore = getNodeWithOrderedIndexIncludingIO(index - 1);
    AudioProcessorGraph::Node* processorAfter = getNodeWithOrderedIndexIncludingIO(index + 1);
    graph.removeNode(processor);
    connect(processorBefore, processorAfter);

    // Decrement all ordered processor indices.
    for (int i = 0; i < graph.getNumNodes(); ++i)
    {
        AudioProcessorGraph::Node* currentNode = graph.getNode(i);
        if (currentNode->properties.contains(orderedIndexProperty) &&
            static_cast<int>(currentNode->properties[orderedIndexProperty]) > index)
        {
            currentNode->properties.set(orderedIndexProperty, static_cast<int>(currentNode->properties[orderedIndexProperty]) - 1);
        }
    }
}

void LinearAudioProcessorGraph::moveProcessor(int currentIndex, int newIndex)
{
    if (currentIndex == newIndex)
        return;

    AudioProcessorGraph::Node* movingNode = getNodeWithOrderedIndex(currentIndex);
    AudioProcessorGraph::Node* movingNodeBefore = getNodeWithOrderedIndexIncludingIO(currentIndex - 1);
    AudioProcessorGraph::Node* movingNodeAfter = getNodeWithOrderedIndexIncludingIO(currentIndex + 1);
    disconnect(movingNodeBefore, movingNode);
    disconnect(movingNode, movingNodeAfter);
    connect(movingNodeBefore, movingNodeAfter);

    AudioProcessorGraph::Node* newBeforeNode;
    AudioProcessorGraph::Node* newAfterNode;
    if (currentIndex < newIndex)
    {
        newBeforeNode = getNodeWithOrderedIndex(currentIndex);
        newAfterNode = getNodeWithOrderedIndexIncludingIO(currentIndex + 1);
        for (int i = 0; i < graph.getNumNodes(); ++i)
        {
            AudioProcessorGraph::Node* currentNode = graph.getNode(i);
            if (currentNode->properties.contains(orderedIndexProperty) &&
                static_cast<int>(currentNode->properties[orderedIndexProperty]) > currentIndex &&
                static_cast<int>(currentNode->properties[orderedIndexProperty]) <= newIndex)
            {
                currentNode->properties.set(orderedIndexProperty, static_cast<int>(currentNode->properties[orderedIndexProperty]) - 1);
            }
        }
    }
    else
    {
        newBeforeNode = getNodeWithOrderedIndexIncludingIO(currentIndex - 1);
        newAfterNode = getNodeWithOrderedIndex(currentIndex);
        for (int i = 0; i < graph.getNumNodes(); ++i)
        {
            AudioProcessorGraph::Node* currentNode = graph.getNode(i);
            if (currentNode->properties.contains(orderedIndexProperty) &&
                static_cast<int>(currentNode->properties[orderedIndexProperty]) < currentIndex &&
                static_cast<int>(currentNode->properties[orderedIndexProperty]) >= newIndex)
            {
                currentNode->properties.set(orderedIndexProperty, static_cast<int>(currentNode->properties[orderedIndexProperty]) + 1);
            }
        }
    }
    disconnect(newBeforeNode, newAfterNode);
    connect(newBeforeNode, movingNode);
    connect(movingNode, newAfterNode);
}

int LinearAudioProcessorGraph::getNumProcessors() const
{
    return graph.getNumNodes() - 2;
}

AudioProcessor* LinearAudioProcessorGraph::getAudioProcessorAtIndex(int index) const
{
    return getNodeWithOrderedIndex(index)->getProcessor();
}

const String LinearAudioProcessorGraph::getName() const
{
    return graph.getName();
}

void LinearAudioProcessorGraph::prepareToPlay(double sampleRate, int blockSize)
{
    graph.prepareToPlay(sampleRate, blockSize);
}

void LinearAudioProcessorGraph::releaseResources()
{
    graph.releaseResources();
}

void LinearAudioProcessorGraph::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    graph.processBlock(buffer, midiMessages);
}

double LinearAudioProcessorGraph::getTailLengthSeconds() const
{
    return graph.getTailLengthSeconds();
}

bool LinearAudioProcessorGraph::acceptsMidi() const
{
    return false;
}

bool LinearAudioProcessorGraph::producesMidi() const
{
    return false;
}

bool LinearAudioProcessorGraph::hasEditor() const
{
    return true;
}

AudioProcessorEditor* LinearAudioProcessorGraph::createEditor()
{
    LinearAudioProcessorGraphEditor* ret = new LinearAudioProcessorGraphEditor(*this);
    sendChangeMessage(); // Sends a change message to the editor we just created.
    return ret;
}

int LinearAudioProcessorGraph::getNumPrograms()
{
    return 1;
}

int LinearAudioProcessorGraph::getCurrentProgram()
{
    return 0;
}

void LinearAudioProcessorGraph::setCurrentProgram(int)
{
}

const String LinearAudioProcessorGraph::getProgramName(int)
{
    return {};
}

void LinearAudioProcessorGraph::changeProgramName(int, const String&)
{
}

void LinearAudioProcessorGraph::getStateInformation(juce::MemoryBlock& data)
{
    graph.getStateInformation(data);
    sendChangeMessage();
}

void LinearAudioProcessorGraph::setStateInformation(const void* data, int sizeInBytes)
{
    graph.setStateInformation(data, sizeInBytes);
}

bool LinearAudioProcessorGraph::isBusesLayoutSupported(const BusesLayout& layout) const
{
    return layout.getMainInputChannelSet() == acceptedChannelLayout &&
            layout.getMainOutputChannelSet() == acceptedChannelLayout;
}

AudioProcessorGraph::Node* LinearAudioProcessorGraph::getNodeWithOrderedIndex(int index) const
{
    assert(index < graph.getNumNodes());
    for (int i = 0; i < graph.getNumNodes(); ++i)
    {
        AudioProcessorGraph::Node* potentialNode = graph.getNode(i);
        if (potentialNode->properties[orderedIndexProperty].equals(i))
        {
            return potentialNode;
        }
    }
    assert(false); // Inconsistent state!
}

AudioProcessorGraph::Node* LinearAudioProcessorGraph::getNodeWithOrderedIndexIncludingIO(int index) const
{
    if (index == -1)
        return input;
    else if (index == getNumProcessors())
        return output;
    else
        return getNodeWithOrderedIndex(index);
}

void LinearAudioProcessorGraph::connect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst)
{
    assert(src && dst);
    assert(src->getProcessor()->getMainBusNumOutputChannels() == dst->getProcessor()->getMainBusNumInputChannels());
    int connectionsToMake = std::min(src->getProcessor()->getMainBusNumOutputChannels(), dst->getProcessor()->getMainBusNumInputChannels());
    for (int i = 0; i < connectionsToMake; ++i)
        assert(graph.addConnection(src->nodeId, i, dst->nodeId, i));
}

void LinearAudioProcessorGraph::disconnect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst)
{
    assert(src && dst);
    assert(src->getProcessor()->getMainBusNumOutputChannels() == dst->getProcessor()->getMainBusNumInputChannels());
    int connectionsToRemove = std::min(src->getProcessor()->getMainBusNumOutputChannels(), dst->getProcessor()->getMainBusNumInputChannels());
    for (int i = 0; i < connectionsToRemove; ++i)
        assert(graph.removeConnection(src->nodeId, i, dst->nodeId, i));
}
