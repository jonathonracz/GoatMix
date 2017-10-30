/*
  ==============================================================================

    Goniometer.cpp
    Created: 29 Oct 2017 7:22:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "Goniometer.h"
#include "MMLookAndFeel.h"
#include "GoniometerSource.h"

Goniometer::Goniometer() :
    pathCoordsForDrawing(256),
    imageBuffers(10)
{
    startTimerHz(30);
}

void Goniometer::setSource(GoniometerSource* _source)
{
    source = _source;
    source->clearBuffer();
}

void Goniometer::setNumPointsInPath(int numPoints)
{
    pathCoordsForDrawing.setCapacity(numPoints);
}

void Goniometer::paint(Graphics& g)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    // Draw background
    {
        Path guidelines;
        guidelines.addEllipse(getLocalBounds().toFloat());
        Rectangle<float> innerGuide = getLocalBounds().toFloat().withSizeKeepingCentre(getWidth() / 2.0f, getHeight() / 2.0f);
        guidelines.addEllipse(innerGuide);
        guidelines.addLineSegment(Line<float>(0.0f, 0.0f, static_cast<float>(getWidth()), static_cast<float>(getHeight())), lf.borderThickness);
        guidelines.addLineSegment(Line<float>(static_cast<float>(getWidth()), 0.0f, 0.0f, static_cast<float>(getHeight())), lf.borderThickness);
        g.setColour(findColour(MMLookAndFeel::ColourIds::outlineLight));
        g.strokePath(guidelines, PathStrokeType(lf.borderThickness));
    }

    {
        Path border;
        border.addRectangle(getLocalBounds());
        g.setColour(findColour(MMLookAndFeel::ColourIds::outline));
        g.strokePath(border, PathStrokeType(lf.borderThickness * 2.0f));
    }

    // Pull as many samples as we can from the intermediate buffer and turn them
    // into normalized x/y coordinates rotated 45 degrees.
    Point<float> newPoint;
    while (source && source->getNextPoint(newPoint))
        pathCoordsForDrawing.push(newPoint);

    Path drawPath;
    drawPath.preallocateSpace(pathCoordsForDrawing.numElements());
    Point<float> componentSpacePoint;
    for (int i = 0; i < pathCoordsForDrawing.numElements(); ++i)
    {
        componentSpacePoint.x = pathCoordsForDrawing[i].x * getWidth() / 2.0f;
        componentSpacePoint.y = pathCoordsForDrawing[i].y * getHeight() / 2.0f;
        componentSpacePoint = componentSpacePoint.rotatedAboutOrigin((7.0f * MathConstants<float>::pi) / 4.0f);
        componentSpacePoint.x += (getWidth() / 2.0f);
        componentSpacePoint.y += (getHeight() / 2.0f);
        if (i == 0)
            drawPath.startNewSubPath(componentSpacePoint);
        else
            drawPath.lineTo(componentSpacePoint);
    }

    {
        Image newPathTarget = imageBuffers.pop();
        Graphics pathRender(newPathTarget);
        pathRender.setColour(findColour(MMLookAndFeel::ColourIds::outline));
        pathRender.strokePath(drawPath, PathStrokeType(lf.borderThickness / 2.0f));
        imageBuffers.push(newPathTarget);
    }

    for (int i = 0; i < imageBuffers.numElements(); ++i)
    {
        imageBuffers[i].multiplyAllAlphas(0.98f);
        g.drawImageAt(imageBuffers[i], 0, 0);
    }
}

void Goniometer::resized()
{
    imageBuffers.clear();
    imageBuffers.fill(Image(Image::PixelFormat::ARGB, getWidth(), getHeight(), true));
}

void Goniometer::timerCallback()
{
    repaint();
}
