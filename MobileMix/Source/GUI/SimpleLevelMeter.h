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

    float getMinGainDisplayValue() const noexcept { return minGainDisplayValue; }
    void setMinGainDisplayValue(float value) noexcept { minGainDisplayValue = value; needsGradientRegen = true; }
    float getMaxGainDisplayValue() const noexcept { return maxGainDisplayValue; }
    void setMaxGainDisplayValue(float value) noexcept { maxGainDisplayValue = value; needsGradientRegen = true; }

private:
    void paint(Graphics& g) noexcept override
    {
        regenerateGradientIfNeeded();
        g.fillAll(Colours::black);
        if (source)
        {
            if (style == peakHoldRMS)
            {
                drawMeterFilledToLevel(g, source->getRMS());

                {
                    float proportionOfMaxMeterFilled = getProportionOfMeterFilledForLevel(source->getPeakHold());
                    int maxMeterStartPos = getHeight() * (1.0 - proportionOfMaxMeterFilled);
                    Rectangle<int> activeMaxMeterArea = Rectangle<int>(0,
                                                                       maxMeterStartPos,
                                                                       getWidth(),
                                                                       1);
                    g.drawImage(gradient.getClippedImage(activeMaxMeterArea), activeMaxMeterArea.toFloat());
                }
            }
            else if (style == peakRMS)
            {
                float peakLevel = source->getPeakInstant();
                float rmsLevel = source->getRMS();
                g.setOpacity(0.5f);
                drawMeterFilledToLevel(g, peakLevel, rmsLevel);
                g.setOpacity(1.0f);
                drawMeterFilledToLevel(g, rmsLevel);
            }
        }
    }

    void timerCallback() noexcept override
    {
        repaint();
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
            float maxGainPos = maxGainDisplayValue - 1.0f;
            float minGainPos = 1.0f - minGainDisplayValue;
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
        float gainBoundsDelta = ((maxGainDisplayValue - minGainDisplayValue) > 0) ? (maxGainDisplayValue - minGainDisplayValue) : 0;
        return (level - minGainDisplayValue) / gainBoundsDelta;
    }

    void drawMeterFilledToLevel(Graphics& g, float level, float bottomLevel = 0.0f) noexcept
    {
        if (bottomLevel >= level)
            return;

        float proportionOfMeterFilled = getProportionOfMeterFilledForLevel(level);
        float bottomProportionOfMeterFilled = getProportionOfMeterFilledForLevel(bottomLevel);
        Rectangle<int> activeMeterArea = Rectangle<int>(0,
                                                        getHeight() * (1.0 - proportionOfMeterFilled),
                                                        getWidth(),
                                                        getHeight() * (1.0f - bottomProportionOfMeterFilled));
        g.drawImage(gradient.getClippedImage(activeMeterArea), activeMeterArea.toFloat());
    }

    Style style = peakRMS;
    WeakReference<WindowedMeter> source;
    float lastRMSLevel = 0.0f;
    float lastPeakLevel = 0.0f;

    float minGainDisplayValue = 0.0f;
    float maxGainDisplayValue = 1.0f;
    bool needsGradientRegen = true;
    Image gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleLevelMeter)
};
