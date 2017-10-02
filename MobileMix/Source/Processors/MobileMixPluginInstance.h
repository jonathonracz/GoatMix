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
    public AudioPluginInstance
{
public:
    MobileMixPluginInstance(AudioProcessor& rootProcessor,
                            ValueTree& parentState,
                            bool retrievingDescriptionOnly = false);
    virtual ~MobileMixPluginInstance();

    /** Override this to add your own parameters to the state tree. Be sure to
        call this base class instance first and
        state.finalizeParametersAndAddToParent() when finshed!
        (TODO: This design kinda sucks.)
    */
    virtual void registerParameters();

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
    NestedAudioProcessorState state;

    const String addPrefixToParameterName(StringRef name) const;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixPluginInstance)

};
