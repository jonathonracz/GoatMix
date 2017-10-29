/*
  ==============================================================================

    MMReverbPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMReverbPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"

class MMReverbPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMReverbPluginEditor(MMReverbPlugin& processor);
    ~MMReverbPluginEditor();

protected:
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    MMParameterSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMReverbPluginEditor)
};
