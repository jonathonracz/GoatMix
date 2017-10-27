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

class MMGainPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMGainPluginEditor(MMGainPlugin& processor);
    ~MMGainPluginEditor();

protected:
    void paint(Graphics& g) override;
    void resized() override;

private:
    FFAU::LevelMeter testMeter;

    MMSliderAttachment gainSliderAttachment;
    MMParameterSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPluginEditor)
};
