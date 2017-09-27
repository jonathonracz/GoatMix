/*
  ==============================================================================

    AudioProcessorChain.h
    Created: 26 Sep 2017 3:46:52pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include "../External/readerwriterqueue/readerwriterqueue.h"

class AudioProcessorChain :
    public AudioProcessor
{
public:
    AudioProcessorChain(int maxNumProcessors);
    ~AudioProcessorChain();

    class Node
    {
    public:
        AudioProcessor* getProcessor() const { return processor.get(); }
        typedef std::shared_ptr<Node> Ref;
    private:
        friend class AudioProcessorChain;
        std::unique_ptr<AudioProcessor> processor;
        Node(AudioProcessor* _processor) :
            processor(processor) {}
    };

    // These can all be called off the audio thread.
    void addProcessor(AudioProcessor* processor, int insertIndex = -1);
    void removeProcessor(int index);
    void moveProcessor(int currentIndex, int newIndex);
    int getNumProcessors() const;
    Node::Ref getProcessorAtIndex(int index) const;

    String getName() { return ""; }
    void prepareToPlay(double sampleRate, int blockSize) override;
    void releaseResources() override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    double getTailLengthSeconds() const override;
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const String& newName) override {}
    void getStateInformation(MemoryBlock& destData) override {}
    void setStateInformation(const void* data, int sizeInBytes) override {}

private:
    enum ModifyAction
    {
        add,
        remove,
        move
    };

    struct ModifyCommand
    {
        ModifyAction action;
        AudioProcessor* newProcessor;
        int index1, index2;
    };

    bool isTransitioning;
    Array<Node::Ref> chain;
    const int maxNumProcessors;
    moodycamel::ReaderWriterQueue<ModifyCommand> commandQueue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorChain)
};
