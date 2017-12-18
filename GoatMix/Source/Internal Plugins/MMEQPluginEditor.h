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
#include "../GUI/EQPreview.h"
#include "../GUI/FFTDisplay.h"
#include "../DSP/SignalSnapshotter.h"
#include "../GUI/FilterCurve.h"

class MMEQPluginEditor :
    public MobileMixPluginInstanceEditor,
    public ComboBox::Listener
{
public:
    MMEQPluginEditor(MMEQPlugin& processor);
    ~MMEQPluginEditor();

protected:
    void resized() override;

private:
    void updateSliderOpacities();
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

    FFTDisplay fft;
    //FilterCurve filterCurve;

    struct EQControls
    {
        MMParameterSlider sliderCutoff;
        MMParameterSlider sliderGain;
        MMParameterSlider sliderQ;
        ComboBox boxType;
        Label text;

        MMSliderAttachment attachCutoff;
        MMSliderAttachment attachGain;
        MMSliderAttachment attachQ;
        MMComboBoxAttachment attachType;
    };

    std::array<EQControls, 4> eqs;
    std::array<Divider, 3> dividers;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMEQPluginEditor)
};
