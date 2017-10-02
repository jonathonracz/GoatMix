/*
  ==============================================================================

    GainProcessor.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MobileMixPluginInstance.h"

class GainProcessor :
    public MobileMixPluginInstance
{
public:
    GainProcessor(AudioProcessor& rootProcessor,
                  ValueTree& parentState,
                  bool retrievingDescriptionOnly = false);
    ~GainProcessor() {}

    void registerParameters() override;

    AudioProcessorEditor* createEditor() override;
    const String getName() const override;

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainProcessor)
};
