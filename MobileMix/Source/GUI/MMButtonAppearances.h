/*
  ==============================================================================

    MMButtonAppearances.h
    Created: 21 Oct 2017 11:11:00pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Used for undo/redo, preset bar chevrons
class MMStaticButton :
    public LookAndFeel_V4
{
    void drawDrawableButton(Graphics& g, DrawableButton& button, bool isMouseOverButton,
        bool isButtonDown) override
    {

    }
};
