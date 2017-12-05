/*
  ==============================================================================

    SimpleLevelMeter.h
    Created: 27 Oct 2017 3:02:45pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MMLookAndFeel.h"
#include "../DSP/WindowedMeter.h"
#include "UIStrings.h"
#include "../DSP/RingBuffer.h"

class SimpleLevelMeter :
    public Component,
    public Timer,
    public SettableTooltipClient
{
public:
    enum Style
    {
        peakRMS,
        peakHoldRMS,
    };

    SimpleLevelMeter()
    {
        startTimerHz(24);
        setOpaque(true);
        setTooltip(UIStrings::Shared::meter);
    }

    ~SimpleLevelMeter() {}

    void setStyle(Style _style) noexcept
    {
        style = _style;
        lastPaintedMinLevel = 0.0f;
        lastPaintedMaxLevel = 0.0f;
    }

    WindowedMeter* getSource() const noexcept
    {
        return source;
    }

    void setSource(WindowedMeter* _source) noexcept
    {
        jassert(_source);
        source = _source;
    }

    float getMinGainDisplayValue() const noexcept { return gainRange.start; }
    void setMinGainDisplayValue(float value) noexcept { gainRange.start = value; needsGradientRegen = true; }
    float getMaxGainDisplayValue() const noexcept { return gainRange.end; }
    void setMaxGainDisplayValue(float value) noexcept { gainRange.end = value; needsGradientRegen = true; }

private:
    void paint(Graphics& g) noexcept override
    {
        regenerateGradientIfNeeded();
        if (source)
        {
            if (style == peakHoldRMS)
            {
                Rectangle<float> rmsBounds = getMeterRegionForLevel(rms);
                Rectangle<float> blackBounds = getMeterRegionForLevel(gainRange.end, rms);

                lastPaintedMinLevel = rms;
                lastPaintedMaxLevel = peakHold;

                g.drawImage(gradient.getClippedImage(rmsBounds.toNearestInt()), rmsBounds);
                g.setColour(Colours::black);
                g.fillRect(blackBounds);

                float proportionOfMaxMeterFilled = getProportionOfMeterFilledForLevel(peakHold);
                int maxMeterStartPos = getHeight() * (1.0 - proportionOfMaxMeterFilled);
                Rectangle<int> activeMaxMeterArea = Rectangle<int>(0,
                                                                   maxMeterStartPos,
                                                                   getWidth(),
                                                                   1);
                g.drawImage(gradient.getClippedImage(activeMaxMeterArea), activeMaxMeterArea.toFloat());
            }
            else if (style == peakRMS)
            {
                Rectangle<float> rmsBounds = getMeterRegionForLevel(rms);
                Rectangle<float> peakBounds = getMeterRegionForLevel(peak, rms);
                Rectangle<float> blackBounds = getMeterRegionForLevel(gainRange.end, peak);

                g.setOpacity(0.5f);
                g.drawImage(gradient.getClippedImage(peakBounds.toNearestInt()), peakBounds);
                g.setOpacity(1.0f);
                g.drawImage(gradient.getClippedImage(rmsBounds.toNearestInt()), rmsBounds);
                g.setColour(Colours::black);
                g.fillRect(blackBounds);

                lastPaintedMinLevel = rms;
                lastPaintedMaxLevel = peak;
            }
        }
    }

    void timerCallback() noexcept override
    {
        if (source)
        {
            rms = source->getRMS();
            peak = source->getPeakInstant();
            peakHold = source->getPeakHold();

            float topPaintLevel = gainRange.end;
            float bottomPaintLevel = gainRange.start;

            switch (style)
            {
                case peakRMS:
                {
                    if (rms == lastPaintedMinLevel && peak == lastPaintedMaxLevel)
                        break;

                    topPaintLevel = std::max(peak, lastPaintedMaxLevel);
                    bottomPaintLevel = std::min(rms, lastPaintedMinLevel);
                    break;
                }
                case peakHoldRMS:
                {
                    topPaintLevel = std::max(peakHold, lastPaintedMaxLevel);
                    bottomPaintLevel = std::min(rms, lastPaintedMinLevel);
                    break;
                }
            }

            float proportionOfMeterFilled = getProportionOfMeterFilledForLevel(topPaintLevel);
            float bottomProportionOfMeterFilled = getProportionOfMeterFilledForLevel(bottomPaintLevel);
            repaint(0, getHeight() * (1.0 - proportionOfMeterFilled), getWidth(), getHeight() * (1.0f - bottomProportionOfMeterFilled));
        }
    }

    void regenerateGradientIfNeeded() noexcept
    {
        if (needsGradientRegen)
        {
            gradient = Image(Image::PixelFormat::RGB, getWidth(), getHeight(), false);
            Graphics gradientGen(gradient);
            MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

            ColourGradient barGradient(lf.findColour(MMLookAndFeel::ColourIds::meterGradientTop),
                                       0.0f,
                                       0.0f,
                                       lf.findColour(MMLookAndFeel::ColourIds::meterGradientBottom),
                                       0.0f,
                                       1.0f,
                                       false);
            float maxGainPos = gainRange.end - 1.0f;
            float minGainPos = 1.0f - gainRange.start;
            gradientGen.setGradientFill(ColourGradient(barGradient.getColourAtPosition(0.0),
                                                       0.0f,
                                                       getHeight() * maxGainPos,
                                                       barGradient.getColourAtPosition(1.0),
                                                       0.0f,
                                                       getHeight() * minGainPos,
                                                       false));
            gradientGen.fillAll();
            gradientGen.setColour(lf.findColour(MMLookAndFeel::ColourIds::meterClip));
            gradientGen.fillRect(0, 0, getWidth(), static_cast<int>(std::ceil(getHeight() * maxGainPos)));
        }
    }

    float getProportionOfMeterFilledForLevel(float level) const noexcept
    {
        return gainRange.convertTo0to1(gainRange.snapToLegalValue(level));
    }

    Rectangle<float> getMeterRegionForLevel(float level, float bottomLevel = 0.0f) noexcept
    {
        float proportionOfMeterFilled = getProportionOfMeterFilledForLevel(level);
        float bottomProportionOfMeterFilled = getProportionOfMeterFilledForLevel(bottomLevel);
        return Rectangle<int>(0,
                              getHeight() * (1.0 - proportionOfMeterFilled),
                              getWidth(),
                              getHeight() * (1.0f - bottomProportionOfMeterFilled)).toFloat();
    }

    Style style = peakRMS;
    WeakReference<WindowedMeter> source;
    float rms = 0.0f;
    float peak = 0.0f;
    float peakHold = 0.0f;

    float lastPaintedMinLevel = 0.0f;
    float lastPaintedMaxLevel = 0.0f;

    NormalisableRange<float> gainRange = { 0.0f, 1.0f };
    bool needsGradientRegen = true;
    Image gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleLevelMeter)
};
