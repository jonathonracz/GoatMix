/*
  ==============================================================================

    DistortionPreview.cpp
    Created: 30 Oct 2017 5:22:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "DistortionPreview.h"
#include "MMLookAndFeel.h"

void DistortionPreview::paint(Graphics& g)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    // Center line
    {
        g.setColour(findColour(MMLookAndFeel::ColourIds::outlineLight));
        g.fillRect(Rectangle<int>(0,
                                  (getHeight() / 2) - lf.borderThickness / 2,
                                  getWidth(),
                                  lf.borderThickness));
    }

    g.setColour(findColour(MMLookAndFeel::ColourIds::outline));

    // Outer border
    {
        Path outline;
        outline.addRectangle(getLocalBounds());
        g.strokePath(outline, PathStrokeType(lf.borderThickness));
    }

    // Preview wave
    
}
