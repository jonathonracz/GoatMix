/*
  ==============================================================================

    GMDistortionPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GMDistortionPlugin.h"
#include "../Core/GoatMixPluginInstanceEditor.h"
#include "../GUI/DistortionPreview.h"
#include "../GUI/SimpleMultiLevelMeter.h"
#include "../GUI/GMShapeButton.h"

class GMDistortionPluginEditor :
    public GoatMixPluginInstanceEditor,
    public Slider::Listener,
    public ChangeBroadcaster
{
public:
    GMDistortionPluginEditor(GMDistortionPlugin& processor);
    ~GMDistortionPluginEditor();

protected:
    void resized() override;

private:
    void sliderValueChanged(Slider* slider) override;

    DistortionPreview preview;
    SimpleMultiLevelMeter meter;
    
    GMParameterSlider sliderDownsample;
    GMParameterSlider sliderBitDepth;
    GMParameterSlider sliderOverdrive;
    GMParameterSlider sliderGain;
    GMParameterSlider sliderLowPass;
    GMShapeButton buttonLowPassEnable;
    
    GMSliderAttachment attachDownsample;
    GMSliderAttachment attachBitDepth;
    GMSliderAttachment attachOverdrive;
    GMSliderAttachment attachGain;
    GMSliderAttachment attachLowPass;
    GMButtonAttachment attachLowPassEnable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMDistortionPluginEditor)
};
