/*
  ==============================================================================

    CompressorPreview.cpp
    Created: 3 Nov 2017 1:40:43am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "CompressorPreview.h"
#include "MMLookAndFeel.h"

CompressorPreview::CompressorPreview(Compressor::Parameters::Ptr _params, WindowedMeter& _meter) :
    params(_params),
    meter(_meter)
{
    startTimerHz(30);
}

void CompressorPreview::paint(Graphics& g)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    g.setColour(findColour(MMLookAndFeel::ColourIds::outline));

    if (params)
    {
        Point<float> curveStart(0.0f, getHeight());
        Point<float> knee(getWidth() * params->threshold, getHeight() * (1.0f - params->threshold));
        // Calculate the y-pos of the compression line via y = mx + b. High school
        // geometry finally came in handy!
        float fractionalRatio = 1.0f / static_cast<float>(params->ratio);
        float ratioYPos = (-fractionalRatio * (getWidth() - knee.x)) + knee.y;
        Point<float> ratio(static_cast<float>(getWidth()), ratioYPos);
        Point<float> meterPoint;

        {
            Path compressionPathLine;
            compressionPathLine.preallocateSpace(3);
            compressionPathLine.startNewSubPath(curveStart);
            compressionPathLine.lineTo(knee);
            compressionPathLine.lineTo(ratio);
            g.setColour(findColour(MMLookAndFeel::ColourIds::outline));
            g.strokePath(compressionPathLine, PathStrokeType(lf.borderThickness * 2.0f));

            float pathPos = meter.getAverageWindowedPeak() * compressionPathLine.getLength();
            meterPoint = compressionPathLine.getPointAlongPath(pathPos);
        }

        {
            Path compressionFillNormal;
            compressionFillNormal.preallocateSpace(4);
            compressionFillNormal.startNewSubPath(curveStart);
            compressionFillNormal.lineTo(knee);
            compressionFillNormal.lineTo(knee.x, getHeight());
            compressionFillNormal.closeSubPath();
            g.setColour(findColour(MMLookAndFeel::ColourIds::outlineLight));
            g.setOpacity(0.25f);
            g.fillPath(compressionFillNormal);
        }

        {
            Path compressionFillCompressed;
            compressionFillCompressed.preallocateSpace(5);
            compressionFillCompressed.startNewSubPath(knee);
            compressionFillCompressed.lineTo(ratio);
            compressionFillCompressed.lineTo(getWidth(), getHeight());
            compressionFillCompressed.lineTo(knee.getX(), getHeight());
            compressionFillCompressed.closeSubPath();
            g.setColour(findColour(MMLookAndFeel::ColourIds::meterClip));
            g.setOpacity(0.25f);
            g.fillPath(compressionFillCompressed);
        }
        g.setOpacity(1.0f);

        g.setColour(findColour(MMLookAndFeel::ColourIds::outline));
        g.drawEllipse(Rectangle<float>(getWidth() / 20.0f, getWidth() / 20.0f).withCentre(meterPoint), lf.borderThickness);
    }

    // Outer border
    {
        Path outline;
        outline.addRectangle(getLocalBounds());
        g.setColour(findColour(MMLookAndFeel::ColourIds::outline));
        g.strokePath(outline, PathStrokeType(lf.borderThickness));
    }
}

void CompressorPreview::timerCallback()
{
    repaint();
}
