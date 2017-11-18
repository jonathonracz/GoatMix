/*
  ==============================================================================

    DistortionPreview.h
    Created: 30 Oct 2017 5:22:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/DistortionChain.h"

class DistortionPreview :
    public Component,
    public ChangeListener,
    public SettableTooltipClient
{
public:
    DistortionPreview(DistortionChain::Parameters::Ptr params, ChangeBroadcaster& paramChangeSource);
    ~DistortionPreview() {}

private:
    void paint(Graphics& g) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    DistortionChain distortion;
    ChangeBroadcaster& paramChangeSource;
    constexpr static const size_t generatorFrequency = 220;
    AudioBuffer<float> freshSignal;
    AudioBuffer<float> processedSignal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionPreview)
};
