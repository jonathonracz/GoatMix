/*
  ==============================================================================

    MMCompressorPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMCompressorPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"
#include "../GUI/Goniometer.h"
#include "../GUI/SimpleLevelMeter.h"

class MMCompressorPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMCompressorPluginEditor(MMCompressorPlugin& processor);
    ~MMCompressorPluginEditor();

protected:
    void resized() override;

private:
    
    Goniometer graphCompress;
    Label textGR;
    Label textLGainReduc;
    Label textRGainReduc;
    SimpleLevelMeter meterLGainReduc;
    SimpleLevelMeter meterRGainReduc;

    MMParameterSlider sliderAttack;
    MMParameterSlider sliderRelease;
    MMParameterSlider sliderRatio;
    MMParameterSlider sliderThreshold;
    MMParameterSlider sliderMakeupGain;
    MMParameterSlider sliderDryWet;
    
    MMSliderAttachment attachAttack;
    MMSliderAttachment attachRelease;
    MMSliderAttachment attachRatio;
    MMSliderAttachment attachThreshold;
    MMSliderAttachment attachMakeupGain;
    MMSliderAttachment attachDryWet;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMCompressorPluginEditor)
};
