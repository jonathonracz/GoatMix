/*
  ==============================================================================

    MobileMixPluginInstance.h
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MobileMixPluginInstance :
    public AudioPluginInstance
{
public:
    MobileMixPluginInstance(AudioProcessorValueTreeState& state);
    virtual ~MobileMixPluginInstance();

    /** Override this to add your own parameters to the state tree. You do NOT
        need to call this base class implementation.
    */
    virtual void registerParameters();

    virtual const String getDisplayName() const { return "NO DISPLAY NAME"; };

    /** Call this in your derived processBlock() and avoid actually doing
        anything to the signal if you're bypassed.
    */
    bool isBypassed() const;

    void fillInPluginDescription(PluginDescription &description) const override;

    /** This MUST be called at the end of your derived prepareToPlay! */
    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;

    void releaseResources() override;

    /** This MUST be called at the end of your derived processBlock! */
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

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

    AudioProcessorValueTreeState& state;
    AudioProcessorParameterWithID* paramBypass;
    FFAU::LevelMeterSource meterSource;

    const String addPrefixToParameterName(StringRef name) const;
    static const String stripPrefixFromParameterName(const String& name);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixPluginInstance)

};
