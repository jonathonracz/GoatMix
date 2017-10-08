/*
  ==============================================================================

    MMReverbPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMReverbPlugin.h"
#include "../Core/MobileMixPluginEditor.h"

class MMReverbPluginEditor :
    public MobileMixPluginEditor
{
public:
    MMReverbPluginEditor(MMReverbPlugin& processor);
    ~MMReverbPluginEditor();

protected:
    void paint(Graphics& g) override;
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPluginEditor)
};
