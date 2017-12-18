/*
  ==============================================================================

    GMShapeButton.cpp
    Created: 28 Oct 2017 10:44:32pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMShapeButton.h"
#include "GMLookAndFeel.h"

GMShapeButton::GMShapeButton(const void* svgData, size_t svgSize, bool isToggle, bool _hasBackground, const String& name) :
    Button(name),
    hasBackground(_hasBackground)
{
    setBufferedToImage(true);
    std::unique_ptr<Drawable> drawable(Drawable::createFromImageData(svgData, svgSize));
    shape = drawable->getOutlineAsPath();
    setClickingTogglesState(isToggle); // Make it toggle by default
}

void GMShapeButton::setOverrideColors(uint32 _upColorId, uint32 _downColorId)
{
    upColorId = _upColorId;
    downColorId = _downColorId;
}

void GMShapeButton::setInternalShapeBounds(Rectangle<int> bounds)
{
    shapeBounds = bounds;
}

void GMShapeButton::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    GMLookAndFeel& lf = static_cast<GMLookAndFeel&>(getLookAndFeel());

    if (getToggleState())
    {
        if (hasBackground)
            lf.drawButtonBackground(g, *this, lf.findColour(GMLookAndFeel::ColourIds::sliderForeground), isMouseOverButton, isButtonDown);

        g.setColour(lf.findColour((downColorId) ? downColorId : GMLookAndFeel::ColourIds::outline));
    }
    else
    {
        if (hasBackground)
            lf.drawButtonBackground(g, *this, Colours::transparentWhite, isMouseOverButton, isButtonDown);

        g.setColour(lf.findColour((upColorId) ? upColorId : GMLookAndFeel::ColourIds::outline));
    }

    Rectangle<int> bounds = (shapeBounds.isEmpty()) ? getLocalBounds() : shapeBounds;
    shape.scaleToFit(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), true);
    g.fillPath(shape);
}
