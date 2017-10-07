/*
  ==============================================================================

    MobileMixPluginProcessor.h
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Core/AudioProcessorChain.h"
#include "Core/MobileMixPluginFormat.h"

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

    AudioProcessorChain chain;

private:
    static XmlElement* nodeToXML(AudioProcessorChain::Node* const node);
    void xmlToNode(const XmlElement& xml);

    int indexOfNodeWithPluginDescription(const PluginDescription& desc) const;

    ValueTree chainTree;
    AudioProcessorValueTreeState params;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessor)
};
