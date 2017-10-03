/*
  ==============================================================================

    MMGainPlugin.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Core/MobileMixPluginInstance.h"

class MMGainPlugin :
    public MobileMixPluginInstance
{
public:
    MMGainPlugin(AudioProcessor& rootProcessor, ValueTree& parentState);
    ~MMGainPlugin() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override;

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

private:
    dsp::ProcessorDuplicator<dsp::Gain<float>, <#typename StateType#>>

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPlugin)
};
