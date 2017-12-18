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
    ReferenceCountedArray<Node> emptyChain;
    const ScopedLock lock(getCallbackLock());
    chain.swapWith(emptyChain);
}

AudioProcessorChain::Node* AudioProcessorChain::addNode(AudioProcessor* processor, int insertIndex)
{
    ReferenceCountedArray<Node> newChain(chain);
    Node::Ptr newNode(new Node(processor));
    newChain.insert(insertIndex, newNode);
    {
        const ScopedLock lock(getCallbackLock());
        chain.swapWith(newChain);
    }
    return newNode.get();
}

void AudioProcessorChain::removeNode(Node* node)
{
    ReferenceCountedArray<Node> newChain(chain);
    newChain.removeObject(node);
    const ScopedLock lock(getCallbackLock());
    chain.swapWith(newChain);
}

void AudioProcessorChain::moveNode(int fromIndex, int toIndex)
{
    ReferenceCountedArray<Node> newChain(chain);
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
    for (int i = 0; i < chain.size(); ++i)
        chain[i]->getProcessor()->processBlock(buffer, midiMessages);
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
