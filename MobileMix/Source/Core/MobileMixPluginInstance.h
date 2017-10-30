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

    virtual void prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock){}
    virtual void processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {}
    virtual void releaseResourcesDerived() {}

    float getUnnormalizedValue(AudioProcessorParameterWithID* param) const;
    float getNormalizedValue(AudioProcessorParameterWithID* param) const;
    const String addPrefixToParameterName(StringRef name) const;
    static const String stripPrefixFromParameterName(const String& name);

    AudioProcessorValueTreeState& state;
    AudioProcessorParameterWithID* paramBypass;
    FFAU::LevelMeterSource meterSource;

private:
    void fillInPluginDescription(PluginDescription &description) const override;

    void releaseResources() override;
    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixPluginInstance)

};
