/*
  ==============================================================================

    GMGainPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GMGainPlugin.h"
#include "../Core/GoatMixPluginInstanceEditor.h"
#include "../GUI/GMParameterSlider.h"
#include "../GUI/GMShapeButton.h"
#include "../GUI/SimpleLevelMeter.h"
#include "../GUI/Goniometer.h"
#include "../GUI/Divider.h"
#include "../GUI/SpanningLabel.h"

class GMGainPluginEditor :
    public GoatMixPluginInstanceEditor
{
public:
    GMGainPluginEditor(GMGainPlugin& processor);
    ~GMGainPluginEditor();

private:
    void resized() override;

    Goniometer goniometer;
    MaxdBLabel maxdBLabel;
    MaxdBLabel leftdBLabel;
    MaxdBLabel rightdBLabel;

    SpanningLabel labelNegL;
    SpanningLabel labelPosL;
    SpanningLabel labelNegR;
    SpanningLabel labelPosR;

    SimpleLevelMeter meterNegL;
    SimpleLevelMeter meterPosL;
    SimpleLevelMeter meterNegR;
    SimpleLevelMeter meterPosR;
    Divider div;

    GMParameterSlider sliderGain;
    GMParameterSlider sliderGainL;
    GMParameterSlider sliderGainR;
    GMParameterSlider sliderPan;
    GMParameterSlider sliderPhaseDelayL;
    GMParameterSlider sliderPhaseDelayR;
    GMShapeButton buttonPhaseInvertL;
    GMShapeButton buttonPhaseInvertR;

    GMSliderAttachment attachGain;
    GMSliderAttachment attachGainL;
    GMSliderAttachment attachGainR;
    GMSliderAttachment attachPan;
    GMSliderAttachment attachPhaseDelayL;
    GMSliderAttachment attachPhaseDelayR;
    GMButtonAttachment attachPhaseInvertL;
    GMButtonAttachment attachPhaseInvertR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMGainPluginEditor)
};
