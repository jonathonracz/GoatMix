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
    paths(Image::PixelFormat::ARGB, 1, 1, false),
    pathCoordsForDrawing(256)
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

    if (wasResized)
    {
        // Resize paths
        paths = paths.rescaled(getWidth(), getHeight(), Graphics::ResamplingQuality::lowResamplingQuality);

        // Draw background
        background = Image(Image::PixelFormat::ARGB, getWidth(), getHeight(), true);
        Graphics bgPainter(background);

        {
            Path guidelines;
            guidelines.addEllipse(getLocalBounds().toFloat());
            Rectangle<float> innerGuide = getLocalBounds().toFloat().withSizeKeepingCentre(getWidth() / 2.0f, getHeight() / 2.0f);
            guidelines.addEllipse(innerGuide);
            guidelines.addLineSegment(Line<float>(0.0f, 0.0f, static_cast<float>(getWidth()), static_cast<float>(getHeight())), lf.borderThickness);
            guidelines.addLineSegment(Line<float>(static_cast<float>(getWidth()), 0.0f, 0.0f, static_cast<float>(getHeight())), lf.borderThickness);
            bgPainter.setColour(findColour(MMLookAndFeel::ColourIds::outlineLight));
            bgPainter.strokePath(guidelines, PathStrokeType(lf.borderThickness));
        }

        {
            Path border;
            border.addRectangle(getLocalBounds());
            bgPainter.setColour(findColour(MMLookAndFeel::ColourIds::outline));
            bgPainter.strokePath(border, PathStrokeType(lf.borderThickness * 2.0f));
        }

        wasResized = false;
    }

    // Pull as many samples as we can from the intermediate buffer and turn them
    // into normalized x/y coordinates rotated 45 degrees.
    Point<float> newPoint;
    while (source && source->getNextPoint(newPoint))
        pathCoordsForDrawing.push(newPoint);

    Path drawPath;
    drawPath.preallocateSpace(pathCoordsForDrawing.getNumElements());
    Point<float> componentSpacePoint;
    for (int i = 0; i < pathCoordsForDrawing.getNumElements(); ++i)
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

    // Render paths.
    {
        paths.multiplyAllAlphas(0.94f);
        Graphics pathRender(paths);
        pathRender.setColour(findColour(MMLookAndFeel::ColourIds::outline));
        pathRender.strokePath(drawPath, PathStrokeType(lf.borderThickness / 2.0f));
    }

    g.drawImageAt(background, 0, 0);
    g.drawImageAt(paths, 0, 0);
}

void Goniometer::resized()
{
    wasResized = true;
}

void Goniometer::timerCallback()
{
    repaint();
}
