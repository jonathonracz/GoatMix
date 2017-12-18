/*
  ==============================================================================

    MMShapeButton.cpp
    Created: 28 Oct 2017 10:44:32pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMShapeButton.h"
#include "MMLookAndFeel.h"

MMShapeButton::MMShapeButton(const void* svgData, size_t svgSize, bool isToggle, bool _hasBackground, const String& name) :
    Button(name),
    hasBackground(_hasBackground)
{
    setBufferedToImage(true);
    std::unique_ptr<Drawable> drawable(Drawable::createFromImageData(svgData, svgSize));
    shape = drawable->getOutlineAsPath();
    setClickingTogglesState(isToggle); // Make it toggle by default
}

void MMShapeButton::setOverrideColors(uint32 _upColorId, uint32 _downColorId)
{
    upColorId = _upColorId;
    downColorId = _downColorId;
}

void MMShapeButton::setInternalShapeBounds(Rectangle<int> bounds)
{
    shapeBounds = bounds;
}

void MMShapeButton::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    if (getToggleState())
    {
        if (hasBackground)
            lf.drawButtonBackground(g, *this, lf.findColour(MMLookAndFeel::ColourIds::sliderForeground), isMouseOverButton, isButtonDown);

        g.setColour(lf.findColour((downColorId) ? downColorId : MMLookAndFeel::ColourIds::outline));
    }
    else
    {
        if (hasBackground)
            lf.drawButtonBackground(g, *this, Colours::transparentWhite, isMouseOverButton, isButtonDown);

        g.setColour(lf.findColour((upColorId) ? upColorId : MMLookAndFeel::ColourIds::outline));
    }

    Rectangle<int> bounds = (shapeBounds.isEmpty()) ? getLocalBounds() : shapeBounds;
    shape.scaleToFit(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), true);
    g.fillPath(shape);
}
