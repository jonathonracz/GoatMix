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
#include "../GUI/ReverbPreview.h"
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
    ReverbPreview preview;
    MMShapeButton buttonHighPass;
    MMShapeButton buttonLowPass;
    
    TextButton tbFreeze = TextButton("Freeze");
    
    MMParameterSlider sliderRoomSize;
    MMParameterSlider sliderDamping;
    MMParameterSlider sliderWidth;
    MMParameterSlider sliderHighPass;
    MMParameterSlider sliderLowPass;
    MMParameterSlider sliderDryWet;
    
    MMSliderAttachment attachRoomSize;
    MMSliderAttachment attachDamping;
    MMSliderAttachment attachWidth;
    MMButtonAttachment attachFreeze;
    MMButtonAttachment attachHighPassEnable;
    MMSliderAttachment attachHighPass;
    MMButtonAttachment attachLowPassEnable;
    MMSliderAttachment attachLowPass;
    MMSliderAttachment attachDryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPluginEditor)
};
