/*
  ==============================================================================

    MMShapeButton.cpp
    Created: 28 Oct 2017 10:44:32pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMShapeButton.h"
#include "MMLookAndFeel.h"

MMShapeButton::MMShapeButton(const String& name, const void* svgData, size_t svgSize, bool isToggle, bool _hasBackground) :
    Button(name),
    hasBackground(_hasBackground)
{
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

    if (hasBackground)
    {
        if (isButtonDown || getToggleState())
        {
            g.fillAll(lf.findColour(MMLookAndFeel::ColourIds::sliderForeground));
            g.setColour(lf.findColour((downColorId) ? downColorId : MMLookAndFeel::ColourIds::sliderText));
        }
        else
        {
            g.fillAll(lf.findColour(MMLookAndFeel::ColourIds::background));
            g.setColour(lf.findColour((upColorId) ? upColorId : MMLookAndFeel::ColourIds::outline));
        }
    }
    else
    {
        if (isButtonDown || getToggleState())
        {
            g.setColour(lf.findColour((downColorId) ? downColorId : MMLookAndFeel::ColourIds::outline));
        }
        else
        {
            g.setColour(lf.findColour((upColorId) ? upColorId : MMLookAndFeel::ColourIds::outline));
        }
    }

    Rectangle<int> bounds = (shapeBounds.isEmpty()) ? getLocalBounds() : shapeBounds;
    shape.scaleToFit(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), true);
    g.fillPath(shape);

    if (hasBackground)
    {
        Path outline;
        outline.addRectangle(getLocalBounds());
        g.setColour(lf.findColour((downColorId) ? downColorId : MMLookAndFeel::ColourIds::outline));
        g.strokePath(outline, PathStrokeType(lf.borderThickness * 2.0f));
    }
}
