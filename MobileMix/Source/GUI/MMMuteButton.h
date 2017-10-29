/*
  ==============================================================================

    MMMuteButton.h
    Created: 24 Oct 2017 1:54:38am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MMLookAndFeel.h"

class MMMuteButton :
    public ShapeButton
{
public:
    MMMuteButton(const String& name) :
        ShapeButton(name, Colours::transparentWhite, Colours::transparentWhite, Colours::transparentWhite)
    {
        MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());
        setColours(lf.findColour(MMLookAndFeel::ColourIds::muteButtonOn),
                   lf.findColour(MMLookAndFeel::ColourIds::muteButtonOn),
                   lf.findColour(MMLookAndFeel::ColourIds::muteButtonOff));

        std::unique_ptr<Drawable> bypassDrawable(Drawable::createFromImageData(BinaryData::power_svg, BinaryData::power_svgSize));
        Path bypassShape = bypassDrawable->getOutlineAsPath();
        setShape(bypassShape, false, false, false);
        setClickingTogglesState(true); // Make it toggle
    }

    ~MMMuteButton() {}

    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override
    {
        ShapeButton::paintButton(g, false, getToggleState());
    }
};
