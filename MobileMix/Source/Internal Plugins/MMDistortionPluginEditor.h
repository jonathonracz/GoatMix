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
#include "../GUI/SimpleLevelMeter.h"
#include "../GUI/MMShapeButton.h"

class MMDistortionPluginEditor :
    public MobileMixPluginInstanceEditor,
    public Slider::Listener,
    public ChangeBroadcaster
{
public:
    MMDistortionPluginEditor(MMDistortionPlugin& processor);
    ~MMDistortionPluginEditor();

protected:
    void resized() override;

private:
    void sliderValueChanged(Slider* slider) override;

    DistortionPreview preview;
    SimpleLevelMeter meterL;
    SimpleLevelMeter meterR;
    Label labelDB;
    Label labelL;
    Label labelR;
    
    MMParameterSlider sliderDownsample;
    MMParameterSlider sliderBitDepth;
    MMParameterSlider sliderOverdrive;
    MMParameterSlider sliderGain;
    MMParameterSlider sliderLowPass;
    MMShapeButton buttonLowPassEnable;
    
    MMSliderAttachment attachDownsample;
    MMSliderAttachment attachBitDepth;
    MMSliderAttachment attachOverdrive;
    MMSliderAttachment attachGain;
    MMSliderAttachment attachLowPass;
    MMButtonAttachment attachLowPassEnable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMDistortionPluginEditor)
};
