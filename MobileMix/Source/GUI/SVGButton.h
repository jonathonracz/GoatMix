/*
  ==============================================================================

    SVGButton.h
    Created: 23 Oct 2017 4:19:40pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SVGButton :
    public DrawableButton
{
public:
    using DrawableButton::DrawableButton;

    Rectangle<float> getImageBounds() const
    {
        DrawableComposite* svg = static_cast<DrawableComposite*>(getCurrentImage());
        return svg->getDrawableBounds();
    }
};
