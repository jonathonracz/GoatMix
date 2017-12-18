/*
  ==============================================================================

    ReverbPreview.h
    Created: 3 Nov 2017 1:40:27am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/GMReverb.h"

class ReverbPreview :
    public Component,
    public SettableTooltipClient,
    public ChangeListener,
    public AudioProcessorValueTreeState::Listener
{
public:
    ReverbPreview(AudioProcessorValueTreeState& state, String roomSizeID,
        String dampingID, String widthID, String freezeID);
    ~ReverbPreview() {}

private:
    void paint(Graphics& g) override;
    void parameterChanged(const String& parameterID, float newValue) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void processPreviewSignal();

    AudioProcessorValueTreeState& state;
    String roomSizeID;
    String dampingID;
    String widthID;
    String freezeID;

    dsp::ProcessSpec spec;
    GMReverb reverb;
    AudioFormatManager formatManager;
    AudioThumbnailCache cache;
    AudioThumbnail thumbnail;
    AudioBuffer<float> buffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbPreview)
};
