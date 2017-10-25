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

class MMEQPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMEQPluginEditor(MMEQPlugin& processor);
    ~MMEQPluginEditor();

protected:
    void paint(Graphics& g) override;
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    MMParameterSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMEQPluginEditor)
};
