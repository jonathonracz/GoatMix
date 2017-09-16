/*
  ==============================================================================

    SubProcessor.h
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/**
 Sub-processor for the main processor. This represents the backend of one of the
 tabs of our main view.
 */
class SubProcessor :
    public AudioProcessor
{
public:
    SubProcessor();
    ~SubProcessor();

    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    bool hasEditor() const override;

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

protected:
    AudioProcessorValueTreeState paramState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SubProcessor)
};
