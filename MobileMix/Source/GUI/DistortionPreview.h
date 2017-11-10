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
    public Component
{
public:
    DistortionPreview();
    ~DistortionPreview() {}

    DistortionChain::Parameters* getParams() const { return distortion.params.get(); }

private:
    void paint(Graphics& g) override;
    void processPreviewSignal();

    DistortionChain distortion;
    constexpr static const size_t generatorFrequency = 220;
    AudioBuffer<float> freshSignal;
    AudioBuffer<float> processedSignal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionPreview)
};
