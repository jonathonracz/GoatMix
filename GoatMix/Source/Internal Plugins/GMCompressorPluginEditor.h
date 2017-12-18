/*
  ==============================================================================

    GMCompressorPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GMCompressorPlugin.h"
#include "../Core/GMPluginInstanceEditor.h"
#include "../GUI/CompressorPreview.h"
#include "../GUI/SimpleLevelMeter.h"

class GMCompressorPluginEditor :
    public GMPluginInstanceEditor
{
public:
    GMCompressorPluginEditor(GMCompressorPlugin& processor);
    ~GMCompressorPluginEditor();

protected:
    void resized() override;

private:
    CompressorPreview preview;
    Label textGR;
    Label textLGainReduc;
    Label textRGainReduc;
    SimpleLevelMeter meterLGainReduc;
    SimpleLevelMeter meterRGainReduc;

    GMParameterSlider sliderAttack;
    GMParameterSlider sliderRelease;
    GMParameterSlider sliderRatio;
    GMParameterSlider sliderThreshold;
    GMParameterSlider sliderMakeupGain;
    GMParameterSlider sliderDryWet;

    GMSliderAttachment attachAttack;
    GMSliderAttachment attachRelease;
    GMSliderAttachment attachRatio;
    GMSliderAttachment attachThreshold;
    GMSliderAttachment attachMakeupGain;
    GMSliderAttachment attachDryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMCompressorPluginEditor)
};
