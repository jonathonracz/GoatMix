/*
  ==============================================================================

    MMMuteButton.h
    Created: 24 Oct 2017 1:54:38am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MMMuteButton :
    public ShapeButton
{
public:
    MMMuteButton(const String& name) :
        ShapeButton(name, Colour(0xff00ffff), Colour(0xff00ffff), Colour(0xff007f7f))
    {
        Path bypassShape = Drawable::createFromImageData(BinaryData::power_svg, BinaryData::power_svgSize)->getOutlineAsPath();
        setShape(bypassShape, false, true, false);
        setClickingTogglesState(true); // Make it toggle
    }

    ~MMMuteButton() {}

    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override
    {
        ShapeButton::paintButton(g, false, getToggleState());
    }
};
