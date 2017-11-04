/*
  ==============================================================================

    MMEQPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMEQPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"
#include "../GUI/Divider.h"

class MMEQPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMEQPluginEditor(MMEQPlugin& processor);
    ~MMEQPluginEditor();

protected:
    void resized() override;

private:
    
    ComboBox boxType1;
    ComboBox boxType2;
    ComboBox boxType3;
    ComboBox boxType4;
    
    Label text1;
    Label text2;
    Label text3;
    Label text4;
    
    Divider div1;
    Divider div2;
    Divider div3;

    MMParameterSlider sliderFrequency1;
    MMParameterSlider sliderGain1;
    MMParameterSlider sliderQ1;
    MMParameterSlider sliderFrequency2;
    MMParameterSlider sliderGain2;
    MMParameterSlider sliderQ2;
    MMParameterSlider sliderFrequency3;
    MMParameterSlider sliderGain3;
    MMParameterSlider sliderQ3;
    MMParameterSlider sliderFrequency4;
    MMParameterSlider sliderGain4;
    MMParameterSlider sliderQ4;
    
    MMSliderAttachment attachFrequency1;
    MMSliderAttachment attachGain1;
    MMSliderAttachment attachQ1;
    MMSliderAttachment attachFrequency2;
    MMSliderAttachment attachGain2;
    MMSliderAttachment attachQ2;
    MMSliderAttachment attachFrequency3;
    MMSliderAttachment attachGain3;
    MMSliderAttachment attachQ3;
    MMSliderAttachment attachFrequency4;
    MMSliderAttachment attachGain4;
    MMSliderAttachment attachQ4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMEQPluginEditor)
};
