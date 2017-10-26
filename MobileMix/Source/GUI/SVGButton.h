/*
  ==============================================================================

    SVGButton.h
    Created: 23 Oct 2017 4:19:40pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SVGButton :
    public DrawableButton
{
public:
    using DrawableButton::DrawableButton;

    Rectangle<float> getImageBounds() const
    {
        //return getLocalBounds().toFloat();
        DrawableComposite* svg = static_cast<DrawableComposite*>(getCurrentImage());
        return svg->getDrawableBounds();
        //return svg->getContentArea().to;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SVGButton)
};
