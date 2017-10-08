/*
  ==============================================================================

    MMCompressorPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMCompressorPlugin.h"
#include "../Core/MobileMixPluginEditor.h"

class MMCompressorPluginEditor :
    public MobileMixPluginEditor
{
public:
    MMCompressorPluginEditor(MMCompressorPlugin& processor);
    ~MMCompressorPluginEditor();

protected:
    void paint(Graphics& g) override;
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMCompressorPluginEditor)
};
