/*
  ==============================================================================

    MMGainPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMGainPlugin.h"
#include "../Core/MobileMixPluginEditor.h"

class MMGainPluginEditor :
    public MobileMixPluginEditor
{
public:
    MMGainPluginEditor(MMGainPlugin& processor);
    ~MMGainPluginEditor();

protected:
    void paint(Graphics& g) override;
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMGainPluginEditor)
};
