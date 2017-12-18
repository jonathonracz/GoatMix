/*
  ==============================================================================

    GMEQPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GMEQPlugin.h"
#include "../Core/GoatMixPluginInstanceEditor.h"
#include "../GUI/Divider.h"
#include "../GUI/EQPreview.h"
#include "../GUI/FFTDisplay.h"
#include "../DSP/SignalSnapshotter.h"
#include "../GUI/FilterCurve.h"

class GMEQPluginEditor :
    public GoatMixPluginInstanceEditor,
    public ComboBox::Listener
{
public:
    GMEQPluginEditor(GMEQPlugin& processor);
    ~GMEQPluginEditor();

protected:
    void resized() override;

private:
    void updateSliderOpacities();
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

    FFTDisplay fft;
    //FilterCurve filterCurve;

    struct EQControls
    {
        GMParameterSlider sliderCutoff;
        GMParameterSlider sliderGain;
        GMParameterSlider sliderQ;
        ComboBox boxType;
        Label text;

        GMSliderAttachment attachCutoff;
        GMSliderAttachment attachGain;
        GMSliderAttachment attachQ;
        GMComboBoxAttachment attachType;
    };

    std::array<EQControls, 4> eqs;
    std::array<Divider, 3> dividers;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMEQPluginEditor)
};
