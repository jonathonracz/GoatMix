/*
  ==============================================================================

    MobileMixPluginInstance.h
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "NestedAudioProcessorState.h"

class MobileMixPluginInstance :
    public AudioPluginInstance,
    public AudioProcessorValueTreeState::Listener
{
public:
    MobileMixPluginInstance(AudioProcessor& rootProcessor,
                            ValueTree& parentState);
    virtual ~MobileMixPluginInstance();

    AudioProcessorValueTreeState& getParameterState();

    /** Override this to add your own parameters to the state tree. You do NOT
        need to call this base class implementation.
    */
    virtual void registerParameters();

    /** If you override this, be sure to call this base implementation! */
    void parameterChanged(const String& parameterID, float newValue) override;

    void fillInPluginDescription(PluginDescription &description) const override;
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
    const String addPrefixToParameterName(StringRef name) const;

private:
    friend class MobileMixAudioProcessor;
    void finalizeParametersAndAddToParentState();

    NestedAudioProcessorState state;
    AudioProcessorParameterWithID* paramBypass;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixPluginInstance)

};
