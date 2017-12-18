/*
  ==============================================================================

    GMReverbPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GMReverbPlugin.h"
#include "../GUI/GMShapeButton.h"
#include "../GUI/ReverbPreview.h"
#include "../Core/GoatMixPluginInstanceEditor.h"

class GMReverbPluginEditor :
    public GoatMixPluginInstanceEditor,
    public Slider::Listener,
    public Button::Listener,
    public ChangeBroadcaster
{
public:
    GMReverbPluginEditor(GMReverbPlugin& processor);
    ~GMReverbPluginEditor();

protected:
    void resized() override;

private:
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override {}
    void buttonStateChanged(Button* button) override;

    ReverbPreview preview;
    GMShapeButton buttonHighPass;
    GMShapeButton buttonLowPass;

    TextButton tbFreeze;

    GMParameterSlider sliderRoomSize;
    GMParameterSlider sliderDamping;
    GMParameterSlider sliderWidth;
    GMParameterSlider sliderHighPass;
    GMParameterSlider sliderLowPass;
    GMParameterSlider sliderDryWet;

    GMSliderAttachment attachRoomSize;
    GMSliderAttachment attachDamping;
    GMSliderAttachment attachWidth;
    GMButtonAttachment attachFreeze;
    GMButtonAttachment attachHighPassEnable;
    GMSliderAttachment attachHighPass;
    GMButtonAttachment attachLowPassEnable;
    GMSliderAttachment attachLowPass;
    GMSliderAttachment attachDryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMReverbPluginEditor)
};
