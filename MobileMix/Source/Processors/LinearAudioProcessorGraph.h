/*
  ==============================================================================

    LinearAudioProcessorGraph.h
    Created: 17 Sep 2017 11:46:41am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class LinearAudioProcessorGraph :
    public AudioProcessor,
    public ChangeBroadcaster
{
public:
    LinearAudioProcessorGraph(AudioChannelSet channelLayout);
    ~LinearAudioProcessorGraph();

    void addProcessor(AudioProcessor* processor, int insertIndex = -1);
    void removeProcessor(int index);
    void moveProcessor(int currentIndex, int newIndex);
    int getNumProcessors() const;
    AudioProcessor* getAudioProcessorAtIndex(int index) const;

    const String getName() const override;
    void prepareToPlay(double sampleRate, int blockSize) override;
    void releaseResources() override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    double getTailLengthSeconds() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool hasEditor() const override;
    AudioProcessorEditor* createEditor() override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int) override;
    const String getProgramName(int) override;
    void changeProgramName(int, const String&) override;
    void getStateInformation(juce::MemoryBlock& data) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    const AudioChannelSet acceptedChannelLayout;

protected:
    bool isBusesLayoutSupported(const BusesLayout& layout) const override;

private:
    AudioProcessorGraph::Node* getNodeWithOrderedIndex(int index) const;
    AudioProcessorGraph::Node* getNodeWithOrderedIndexIncludingIO(int index) const;
    void connect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst);
    void disconnect(AudioProcessorGraph::Node* src, AudioProcessorGraph::Node* dst);

    AudioProcessorGraph graph;
    AudioProcessorGraph::Node* input;
    AudioProcessorGraph::Node* output;
};
