/*
  ==============================================================================

    MMGainPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMGainPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"
#include "../GUI/MMParameterSlider.h"
#include "../GUI/MMShapeButton.h"
#include "../GUI/SimpleMultiLevelMeter.h"
#include "../GUI/Goniometer.h"
#include "../GUI/Divider.h"

class MMGainPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMGainPluginEditor(MMGainPlugin& processor);
    ~MMGainPluginEditor();

protected:
    void resized() override;

private:
    Goniometer goniometer;
    MaxdBLabel maxdBLabel;
    
    SimpleMultiLevelMeter smlMeterL;
    SimpleMultiLevelMeter smlMeterR;
    Divider div;

    MMParameterSlider sliderGain;
    MMParameterSlider sliderGainL;
    MMParameterSlider sliderGainR;
    MMParameterSlider sliderPan;
    MMParameterSlider sliderPhaseDelayL;
    MMParameterSlider sliderPhaseDelayR;
    MMShapeButton buttonPhaseInvertL;
    MMShapeButton buttonPhaseInvertR;

    MMSliderAttachment attachGain;
    MMSliderAttachment attachGainL;
    MMSliderAttachment attachGainR;
    MMSliderAttachment attachPan;
    MMSliderAttachment attachPhaseDelayL;
    MMSliderAttachment attachPhaseDelayR;
    MMButtonAttachment attachPhaseInvertL;
    MMButtonAttachment attachPhaseInvertR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPluginEditor)
};
