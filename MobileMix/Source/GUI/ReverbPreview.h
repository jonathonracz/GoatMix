/*
  ==============================================================================

    ReverbPreview.h
    Created: 3 Nov 2017 1:40:27am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/MMReverb.h"

class ReverbPreview :
    public Component,
    public Slider::Listener,
    public ChangeListener
{
public:
    ReverbPreview(MMReverb::Parameters::Ptr paramsToFollow);
    ~ReverbPreview() {}

private:
    void paint(Graphics& g) override;
    void sliderValueChanged(Slider* slider) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void processPreviewSignal();

    MMReverb reverb;
    AudioFormatManager formatManager;
    AudioThumbnailCache cache;
    AudioThumbnail thumbnail;
    AudioBuffer<float> buffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbPreview)
};
