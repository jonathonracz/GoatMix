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

class SimpleLevelMeter :
    public Component,
    public Timer
{
public:
    SimpleLevelMeter()
    {
        startTimerHz(30);
        setOpaque(true);
    }

    ~SimpleLevelMeter() {}

    void setSource(FFAU::LevelMeterSource* _source)
    {
        jassert(_source);
        source = _source;
        jassert(channel < source->getNumChannels());
    }

    float getChannel() const { return channel; }
    void setChannel(int _channel) { channel = _channel; }
    float getMinGainDisplayValue() const { return minGainDisplayValue; }
    void setMinGainDisplayValue(float value) { minGainDisplayValue = value; needsGradientRegen = true; }
    float getMaxGainDisplayValue() const { return maxGainDisplayValue; }
    void setMaxGainDisplayValue(float value) { maxGainDisplayValue = value; needsGradientRegen = true; }

private:
    void paint(Graphics& g) override
    {
        regenerateGradientIfNeeded();
        g.fillAll(Colours::black);
        if (source)
        {
            float gainBoundsDelta = ((maxGainDisplayValue - minGainDisplayValue) > 0) ? (maxGainDisplayValue - minGainDisplayValue) : 0;

            {
                float proportionOfRMSMeterFilled = (source->getRMSLevel(channel) - minGainDisplayValue) / gainBoundsDelta;
                Rectangle<int> activeRMSMeterArea = Rectangle<int>(0,
                                                                   getHeight() * (1.0 - proportionOfRMSMeterFilled),
                                                                   getWidth(),
                                                                   getHeight());
                g.drawImage(gradient.getClippedImage(activeRMSMeterArea), activeRMSMeterArea.toFloat());
            }

            {
                float proportionOfMaxMeterFilled = (source->getMaxLevel(channel) - minGainDisplayValue) / gainBoundsDelta;
                int maxMeterStartPos = getHeight() * (1.0 - proportionOfMaxMeterFilled);
                Rectangle<int> activeMaxMeterArea = Rectangle<int>(0,
                                                                   maxMeterStartPos,
                                                                   getWidth(),
                                                                   1);
                g.drawImage(gradient.getClippedImage(activeMaxMeterArea), activeMaxMeterArea.toFloat());
            }
        }
    }

    void timerCallback() override
    {
        if (source)
            source->decayIfNeeded();

        repaint();
    }

    void regenerateGradientIfNeeded()
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

    WeakReference<FFAU::LevelMeterSource> source;
    int channel = 0;
    float minGainDisplayValue = 0.0f;
    float maxGainDisplayValue = 1.0f;
    bool needsGradientRegen = true;
    Image gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleLevelMeter)
};
