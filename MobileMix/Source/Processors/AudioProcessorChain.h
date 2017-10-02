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

class AudioProcessorChain :
    public AudioProcessor
{
public:
    AudioProcessorChain() {}
    ~AudioProcessorChain() {}

    class Node
    {
    public:
        AudioProcessor* getProcessor() const { return processor.get(); }
        typedef std::shared_ptr<Node> Ptr;
    private:
        friend class AudioProcessorChain;
        std::unique_ptr<AudioProcessor> processor;
        Node(AudioProcessor* _processor) : processor(_processor) {}
    };

    /** These should all be called on the message thread. */
    void clear();
    int getNumNodes() const noexcept { return chain.size(); };
    Node* getNode(int index) const noexcept { return chain[index].get(); }
    Node* addNode(AudioProcessor* processor, int insertIndex = -1);
    bool removeNode(Node* node);
    void moveNode(int fromIndex, int toIndex);

    /** AudioProcessor overrides. */
    const String getName() const override { return ""; }
    void prepareToPlay(double sampleRate, int blockSize) override;
    void releaseResources() override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    bool supportsDoublePrecisionProcessing() const override { return false; }
    double getTailLengthSeconds() const override;

    void reset() override;
    void setNonRealtime(bool isProcessingNonRealtime) noexcept override;
    void setPlayHead(AudioPlayHead* playhead) override;

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return true; }
    bool hasEditor() const override { return false; }
    AudioProcessorEditor* createEditor() override { return nullptr; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const String& newName) override {}
    void getStateInformation(MemoryBlock& destData) override {}
    void setStateInformation(const void* data, int sizeInBytes) override {}

private:
    Array<Node::Ptr> chain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorChain)
};
