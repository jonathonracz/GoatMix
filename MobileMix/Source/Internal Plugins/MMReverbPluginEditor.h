/*
  ==============================================================================

    MMReverbPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMReverbPlugin.h"
#include "../GUI/MMShapeButton.h"
#include "../GUI/Goniometer.h"
#include "../Core/MobileMixPluginInstanceEditor.h"

class MMReverbPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMReverbPluginEditor(MMReverbPlugin& processor);
    ~MMReverbPluginEditor();

protected:
    void resized() override;

private:
    
    Goniometer graphReverb;
    //MMShapeButton buttonHighPass;
    //MMShapeButton buttonLowPass;
    
    MMParameterSlider sliderTrim;
    MMParameterSlider sliderHighPass;
    MMParameterSlider sliderLowPass;
    MMParameterSlider sliderLength;
    MMParameterSlider sliderDryWet;
    
    MMSliderAttachment attachTrim;
    MMSliderAttachment attachHighPass;
    MMSliderAttachment attachLowPass;
    MMSliderAttachment attachLength;
    MMSliderAttachment attachDryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPluginEditor)
};
