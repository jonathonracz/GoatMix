/*
  ==============================================================================

    GainProcessor.h
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "SubProcessor.h"

class GainProcessor :
    public SubProcessor
{
public:
    GainProcessor(AudioProcessor& parentProcessor);
    ~GainProcessor();
    AudioProcessorEditor* createEditor() override;
    const String getName() const override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainProcessor)
};
