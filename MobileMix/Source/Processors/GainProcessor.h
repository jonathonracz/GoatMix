/*
  ==============================================================================

    GainProcessor.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MobileMixAudioProcessor.h"

class GainProcessor :
    public MobileMixAudioProcessor
{
public:
    GainProcessor(AudioProcessor& rootProcessor,
                  AudioProcessorValueTreeState& parentState);
    ~GainProcessor() {}

    AudioProcessorEditor* createEditor() override;
    const String getName() const override;

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainProcessor)
};
