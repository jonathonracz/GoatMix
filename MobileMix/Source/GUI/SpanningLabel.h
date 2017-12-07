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

    NormalisableRange<float> getRange() const noexcept
    {
        return range;
    }

    void setRange(NormalisableRange<float> _range) noexcept
    {
        range = _range;
        repaint();
    }

    int getNumIntermediatePoints() const noexcept
    {
        return numIntermediatePoints;
    }

    void setNumIntermediatePoints(int _numIntermediatePoints) noexcept
    {
        jassert(_numIntermediatePoints >= 0);
        numIntermediatePoints = _numIntermediatePoints;
        repaint();
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

    bool getReversedOrder() const noexcept
    {
        return reversedOrder;
    }

    void setReversedOrder(bool reversed) noexcept
    {
        reversedOrder = reversed;
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

        float firstValueHalfSize;
        float lastValueHalfSize;
        float spanDimensionSize;
        bool isVertical;

        if (layoutDirection == horizontalTop ||
            layoutDirection == horizontalCenter ||
            layoutDirection == horizontalBottom)
        {
            firstValueHalfSize = font.getStringWidthFloat(valueToTextFunction(range.convertFrom0to1(0.0f)));
            lastValueHalfSize = font.getStringWidthFloat(valueToTextFunction(range.convertFrom0to1(1.0f)));
            spanDimensionSize = static_cast<float>(getWidth());
            isVertical = false;
        }
        else // Vertical
        {
            firstValueHalfSize = lastValueHalfSize = font.getHeight() / 2.0f;
            spanDimensionSize = static_cast<float>(getHeight());
            isVertical = true;
        }

        Array<float> centerPoints;
        centerPoints.ensureStorageAllocated(numIntermediatePoints + 2);
        centerPoints.add(firstValueHalfSize);
        float centerPointDelta = spanDimensionSize / (numIntermediatePoints + 1);
        for (int i = 1; i < (numIntermediatePoints + 1); ++i)
        {
            centerPoints.add(i * centerPointDelta);
        }
        centerPoints.add(spanDimensionSize - lastValueHalfSize);

        for (int i = 0; i < centerPoints.size(); ++i)
        {
            float proportionAlongCenterPoints = (i * centerPointDelta) / spanDimensionSize;

            if (reversedOrder)
                proportionAlongCenterPoints = 1.0f - proportionAlongCenterPoints;

            String valueString = valueToTextFunction(range.convertFrom0to1(proportionAlongCenterPoints));
            Rectangle<float> textBounds;
            if (isVertical)
            {
                textBounds = Rectangle<float>(static_cast<float>(getWidth()), firstValueHalfSize * 2.0f).withCentre({ getWidth() / 2.0f, centerPoints[i] });
            }
            else
            {
                textBounds = Rectangle<float>(font.getStringWidthFloat(valueString), static_cast<float>(getHeight())).withCentre({ centerPoints[i], getHeight() / 2.0f });
            }

            g.drawFittedText(valueString, textBounds, justification, 1);
        }
    }

    NormalisableRange<float> range = { 0.0f, 1.0f };
    int numIntermediatePoints = 0;
    std::function<String(float)> valueToTextFunction = [](float value){ return String(value); };
    LayoutDirection layoutDirection = horizontalCenter;
    bool reversedOrder = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpanningLabel)
};
