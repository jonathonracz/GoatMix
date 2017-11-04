/*
  ==============================================================================

    AudioProcessorChain.cpp
    Created: 26 Sep 2017 3:46:52pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "AudioProcessorChain.h"

void AudioProcessorChain::clear()
{
    Array<Node::Ptr> emptyChain;
    const ScopedLock lock(getCallbackLock());
    chain.swapWith(emptyChain);
}

AudioProcessorChain::Node* AudioProcessorChain::addNode(AudioProcessor* processor, int insertIndex)
{
    Array<Node::Ptr> newChain(chain);
    Node::Ptr newNode = std::shared_ptr<Node>(new Node(processor));
    newChain.insert(insertIndex, newNode);
    {
        const ScopedLock lock(getCallbackLock());
        chain.swapWith(newChain);
    }
    return newNode.get();
}

struct RemoveRawPointerPredicate
{
    AudioProcessorChain::Node* rawNode;
    bool operator()(AudioProcessorChain::Node::Ptr node) const
    {
        return node.get() == rawNode;
    }
};

bool AudioProcessorChain::removeNode(Node* node)
{
    Array<Node::Ptr> newChain(chain);
    int numRemoved = newChain.removeIf(RemoveRawPointerPredicate{node});
    {
        const ScopedLock lock(getCallbackLock());
        chain.swapWith(newChain);
    }
    return (numRemoved);
}

void AudioProcessorChain::moveNode(int fromIndex, int toIndex)
{
    Array<Node::Ptr> newChain(chain);
    Node::Ptr nodeToMove = newChain.removeAndReturn(fromIndex);
    newChain.insert(toIndex, nodeToMove);

    const ScopedLock lock(getCallbackLock());
    chain.swapWith(newChain);
}

void AudioProcessorChain::prepareToPlay(double sampleRate, int blockSize)
{
    for (Node::Ptr node : chain)
        node->getProcessor()->prepareToPlay(sampleRate, blockSize);
}

void AudioProcessorChain::releaseResources()
{
    for (Node::Ptr node : chain)
        node->getProcessor()->releaseResources();
}

void AudioProcessorChain::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (Node::Ptr node : chain)
        node->getProcessor()->processBlock(buffer, midiMessages);
}

double AudioProcessorChain::getTailLengthSeconds() const
{
    double longestTailLength = 0.0;
    for (Node::Ptr node : chain)
        longestTailLength = std::max(node->getProcessor()->getTailLengthSeconds(), longestTailLength);

    return longestTailLength;
}

void AudioProcessorChain::reset()
{
    const ScopedLock lock(getCallbackLock());
    for (Node::Ptr node : chain)
        node->getProcessor()->reset();
}

void AudioProcessorChain::setNonRealtime(bool isProcessingNonRealtime) noexcept
{
    const ScopedLock lock(getCallbackLock());
    AudioProcessor::setNonRealtime(isProcessingNonRealtime);
    for (Node::Ptr node : chain)
        node->getProcessor()->reset();
}

void AudioProcessorChain::setPlayHead(AudioPlayHead* playhead)
{
    const ScopedLock lock(getCallbackLock());
    AudioProcessor::setPlayHead(playhead);
    for (Node::Ptr node : chain)
        node->getProcessor()->setPlayHead(playhead);
}
