/*
  ==============================================================================

    MMDistortionPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMDistortionPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"
#include "../GUI/DistortionPreview.h"
#include "../GUI/Goniometer.h"
#include "../GUI/SimpleLevelMeter.h"

class MMDistortionPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMDistortionPluginEditor(MMDistortionPlugin& processor);
    ~MMDistortionPluginEditor();

protected:
    void resized() override;

private:
    Goniometer graphDistortion;
    SimpleLevelMeter meterL;
    SimpleLevelMeter meterR;
    Label labelL;
    Label labelR;
    
    MMParameterSlider sliderDownsample;
    MMParameterSlider sliderBitDepth;
    MMParameterSlider sliderTone;
    MMParameterSlider sliderDrive;
    MMParameterSlider sliderClipThreshold1;
    MMParameterSlider sliderLowPass;
    MMParameterSlider sliderClipThreshold2;
    
    MMSliderAttachment attachDownsample;
    MMSliderAttachment attachBitDepth;
    MMSliderAttachment attachTone;
    MMSliderAttachment attachDrive;
    MMSliderAttachment attachClipThreshold1;
    MMSliderAttachment attachLowPass;
    MMSliderAttachment attachClipThreshold2;
    
    //MMShapeButton buttonLowPass;

    DistortionPreview preview;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMDistortionPluginEditor)
};
