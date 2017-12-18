/*
  ==============================================================================

    GMShapeButton.h
    Created: 28 Oct 2017 10:44:32pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class GMShapeButton :
    public Button
{
public:
    GMShapeButton(const void* svgData, size_t svgSize, bool isToggle = true, bool hasBackground = true, const String& name = {});
    ~GMShapeButton() {}

    void setOverrideColors(uint32 upColorId, uint32 downColorId);
    void setInternalShapeBounds(Rectangle<int> bounds);

protected:
    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

    Path shape;
    uint32 upColorId = 0;
    uint32 downColorId = 0;
    bool hasBackground;
    Rectangle<int> shapeBounds;
};
