/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/**
*/
class MobileMixAudioProcessor :
    public AudioProcessor
{
public:
    MobileMixAudioProcessor();
    ~MobileMixAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void incrementNodeAtOrderedIndex(int index);
    void decrementNodeAtOrderedIndex(int index);

private:
    AudioProcessorGraph::Node* getNodeWithOrderedIndex(int index);
    void moveNodeFromBetweenCurrentPairToBetweenNewPair(AudioProcessorGraph::Node* node,
        AudioProcessorGraph::Node* newPrevious,
        AudioProcessorGraph::Node* newNext);
    void connect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst);
    void disconnect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst);

    AudioProcessorGraph graph;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessor)
};
