/*
  ==============================================================================

    SpanningLabel.h
    Created: 5 Dec 2017 7:11:09pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SpanningLabel :
    public Component
{
public:
    enum LayoutDirection
    {
        horizontalTop,
        horizontalCenter,
        horizontalBottom,
        verticalLeft,
        verticalCenter,
        verticalRight,
    };

    SpanningLabel() {}
    ~SpanningLabel() {}

    void setRange(NormalisableRange<float> _range) noexcept
    {
        range = _range;
        repaint();
    }

    NormalisableRange<float> getRange() const noexcept
    {
        return range;
    }

    void setNumIntermediatePoints(int _numIntermediatePoints) noexcept
    {
        jassert(_numIntermediatePoints >= 0);
        numIntermediatePoints = _numIntermediatePoints;
        repaint();
    }

    int getNumIntermediatePoints() const noexcept
    {
        return numIntermediatePoints;
    }

    void setValueToTextFunction(const std::function<String(float)>& function) noexcept
    {
        valueToTextFunction = function;
    }

    LayoutDirection getLayoutDirection() const noexcept
    {
        return layoutDirection;
    }

    void setLayoutDirection(LayoutDirection direction) noexcept
    {
        layoutDirection = direction;
        repaint();
    }

private:
    void paint(Graphics& g) noexcept override
    {
        Font font = g.getCurrentFont();

        Justification justification(Justification::Flags::centred);
        switch (layoutDirection)
        {
            case horizontalTop:     justification = Justification(Justification::Flags::top); break;
            case horizontalCenter:  justification = Justification(Justification::Flags::verticallyCentred); break;
            case horizontalBottom:  justification = Justification(Justification::Flags::bottom); break;
            case verticalLeft:      justification = Justification(Justification::Flags::left); break;
            case verticalCenter:    justification = Justification(Justification::Flags::horizontallyCentred); break;
            case verticalRight:     justification = Justification(Justification::Flags::right); break;
            default: jassertfalse;
        }

        if (layoutDirection == horizontalTop ||
            layoutDirection == horizontalCenter ||
            layoutDirection == horizontalBottom)
        {
            float firstValueWidth = font.getStringWidthFloat(valueToTextFunction(range.convertFrom0to1(0.0f)));
            float lastValueWidth = font.getStringWidthFloat(valueToTextFunction(range.convertFrom0to1(1.0f)));
            float symmetricEdgeWidth = std::max(firstValueWidth, lastValueWidth) / 2.0f;

            Array<float> xCenterPoints;
            xCenterPoints.ensureStorageAllocated(numIntermediatePoints + 2);
            xCenterPoints.add(symmetricEdgeWidth);
            float centerPointDelta = (getWidth() - (symmetricEdgeWidth * 2.0f)) / numIntermediatePoints;
            for (int i = 0; i < numIntermediatePoints; ++i)
            {
                xCenterPoints.add(symmetricEdgeWidth + (i * centerPointDelta));
            }
            xCenterPoints.add(getWidth() - symmetricEdgeWidth);

            for (int i = 0; i < xCenterPoints.size(); ++i)
            {
                float proportionAlongCenterPoints = (xCenterPoints[i] - xCenterPoints.getFirst()) / (xCenterPoints.getLast() - xCenterPoints.getFirst());
                String valueString = valueToTextFunction(range.convertFrom0to1(proportionAlongCenterPoints));
                Rectangle<float> textBounds = Rectangle<float>(font.getStringWidthFloat(valueString), static_cast<float>(getHeight())).withCentre({ xCenterPoints[i], getHeight() / 2.0f });
                g.drawText(valueString, textBounds, justification);
            }
        }
        else // Vertical
        {
            Array<float> yCenterPoints;
            yCenterPoints.ensureStorageAllocated(numIntermediatePoints + 2);
            float halfFontHeight = font.getHeight() / 2.0f;
            yCenterPoints.add(halfFontHeight);
            float centerPointDelta = (getHeight() - (halfFontHeight * 2.0f)) / numIntermediatePoints;
            for (int i = 0; i < numIntermediatePoints; ++i)
            {
                yCenterPoints.add(halfFontHeight + (i * centerPointDelta));
            }
            yCenterPoints.add(getHeight() - halfFontHeight);

            for (int i = 0; i < yCenterPoints.size(); ++i)
            {
                float proportionAlongCenterPoints = (yCenterPoints[i] - yCenterPoints.getFirst()) / (yCenterPoints.getLast() - yCenterPoints.getFirst());
                String valueString = valueToTextFunction(range.convertFrom0to1(proportionAlongCenterPoints));
                Rectangle<float> textBounds = Rectangle<float>(static_cast<float>(getWidth()), font.getHeight()).withCentre({ getWidth() / 2.0f, yCenterPoints[i] });
                g.drawText(valueString, textBounds, justification);
            }
        }
    }

    NormalisableRange<float> range;
    int numIntermediatePoints = 0;
    std::function<String(float)> valueToTextFunction = [](float value){ return String(value); };
    LayoutDirection layoutDirection = horizontalCenter;
};
