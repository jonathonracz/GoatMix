/*
  ==============================================================================

    MobileMixPluginProcessor.h
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Core/AudioProcessorChain.h"
#include "Core/MobileMixPluginFormat.h"

/**
*/
class MobileMixAudioProcessor :
    public AudioProcessor,
    public ValueTree::Listener,
    public AudioProcessorListener
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

    UndoManager undoManager;
    AudioProcessorChain chain;
    ValueTree chainTree;
    AudioProcessorValueTreeState params;

private:
    int indexOfNodeWithName(String name) const;

    void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override {}
    void valueTreeChildAdded(ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override {};
    void valueTreeChildRemoved(ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override {}
    void valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged) override {}
    void valueTreeRedirected(ValueTree &treeWhichHasBeenChanged) override;

    void audioProcessorParameterChanged(AudioProcessor* processor, int parameterIndex, float newValue) override {}
    void audioProcessorChanged(AudioProcessor* processor) override {}
    void audioProcessorParameterChangeGestureBegin(AudioProcessor* processor, int parameterIndex) override;
    void audioProcessorParameterChangeGestureEnd(AudioProcessor* processor, int parameterIndex) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessor)
};
