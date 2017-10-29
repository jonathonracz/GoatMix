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
#include "../GUI/SimpleMultiLevelMeter.h"

class MMGainPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMGainPluginEditor(MMGainPlugin& processor);
    ~MMGainPluginEditor();

protected:
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;
    MMParameterSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPluginEditor)
};
