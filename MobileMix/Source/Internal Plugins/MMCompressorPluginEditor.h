/*
  ==============================================================================

    MMCompressorPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMCompressorPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"

class MMCompressorPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMCompressorPluginEditor(MMCompressorPlugin& processor);
    ~MMCompressorPluginEditor();

protected:
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    MMParameterSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMCompressorPluginEditor)
};
