/*
  ==============================================================================

    AudioProcessorChain.cpp
    Created: 26 Sep 2017 3:46:52pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "AudioProcessorChain.h"

AudioProcessorChain::AudioProcessorChain(int _maxNumProcessors) :
    isTransitioning(false),
    maxNumProcessors(_maxNumProcessors),
    commandQueue(64)
{
    chain.ensureStorageAllocated(maxNumProcessors);
}

AudioProcessorChain::~AudioProcessorChain()
{
}

void AudioProcessorChain::addProcessor(AudioProcessor* processor, int insertIndex)
{
    // If you hit this assertion, then the command queue is overflowed and
    // should be made larger.
    assert(commandQueue.try_enqueue(ModifyCommand{add, processor, insertIndex, 0}));
}

void AudioProcessorChain::removeProcessor(int index)
{
    // If you hit this assertion, then the command queue is overflowed and
    // should be made larger.
    assert(commandQueue.try_enqueue(ModifyCommand{remove, nullptr, index, 0}));
}

void AudioProcessorChain::moveProcessor(int currentIndex, int newIndex)
{
    // If you hit this assertion, then the command queue is overflowed and
    // should be made larger.
    assert(commandQueue.try_enqueue(ModifyCommand{move, nullptr, currentIndex, newIndex}));
}

int AudioProcessorChain::getNumProcessors() const
{
    return chain.size();
}

void AudioProcessorChain::prepareToPlay(double sampleRate, int blockSize)
{
    for (AudioProcessor *processor : chain)
        processor->prepareToPlay(sampleRate, blockSize);
}

void AudioProcessorChain::releaseResources()
{
    for (AudioProcessor *processor : chain)
        processor->releaseResources();
}

void AudioProcessorChain::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (AudioProcessor *processor : chain)
        processor->processBlock(buffer, midiMessages);

    if (!isTransitioning && commandQueue.size_approx())
    {
        isTransitioning = true;
        buffer.applyGainRamp(0, buffer.getNumSamples(), 1.0f, 0.0f);
        // Apply all our pending changes to the chain.
        ModifyCommand currentCommand;
        for (size_t i = 0; i < commandQueue.size_approx(); ++i)
        {
            if (!commandQueue.try_dequeue(currentCommand))
                break;

            switch (currentCommand.action)
            {
                case add:
                {
                    // Adding another processor would cause allocation on the audio thread!
                    assert(chain.size() < maxNumProcessors);
                    if (chain.size() < maxNumProcessors)
                        chain.insert(currentCommand.index1, currentCommand.newProcessor);
                    break;
                }
                case remove:
                {
                    chain.remove(currentCommand.index1);
                    break;
                }
                case move:
                {
                    chain.move(currentCommand.index1, currentCommand.index2);
                    break;
                }
                default:
                {
                    assert(false);
                    break;
                }
            }
        }
    }
    else if (isTransitioning)
    {
        buffer.applyGainRamp(0, buffer.getNumSamples(), 0.0f, 1.0f);
        isTransitioning = false;
    }
}

double AudioProcessorChain::getTailLengthSeconds() const
{
    double longestTailLength = 0.0;
    for (AudioProcessor *processor : chain)
        longestTailLength = std::max(processor->getTailLengthSeconds(), longestTailLength);

    return longestTailLength;
}
