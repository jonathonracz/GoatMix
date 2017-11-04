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
    public Slider::Listener
{
public:
    DistortionPreview(DistortionChain::Parameters::Ptr paramsToFollow);
    ~DistortionPreview() {}

private:
    void paint(Graphics& g) override;
    void sliderValueChanged(Slider* slider) override;
    void processPreviewSignal();

    DistortionChain distortion;
    constexpr static const size_t generatorFrequency = 440;
    AudioBuffer<float> freshSignal;
    AudioBuffer<float> processedSignal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionPreview)
};
