/*
  ==============================================================================

    SimpleLevelMeter.h
    Created: 27 Oct 2017 3:02:45pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

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
    void setChannel(int _channel) { channel = _channel; needsGradientRegen = true; }
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
            float proportionOfMeterFilled = (source->getMaxLevel(channel) - minGainDisplayValue) / (maxGainDisplayValue - minGainDisplayValue);
            Rectangle<int> activeMeterArea = Rectangle<int>(getHeight() * (1.0 - proportionOfMeterFilled),
                                                            0,
                                                            getWidth(),
                                                            getHeight());
            g.drawImage(gradient.getClippedImage(activeMeterArea), activeMeterArea.toFloat());
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

            ColourGradient barGradient(Colour::fromRGB(196, 248, 100),
                                       0.0f,
                                       0.0f,
                                       Colour::fromRGB(11, 248, 100),
                                       0.0f,
                                       1.0f,
                                       false);

            float gradientTopY = getHeight() * (1.0f - maxGainDisplayValue);
            float gradientBottomY = getHeight();
            gradientGen.setGradientFill(ColourGradient(barGradient.getColourAtPosition(0.0),
                                                       0.0f,
                                                       static_cast<float>(gradientTopY),
                                                       barGradient.getColourAtPosition(minGainDisplayValue),
                                                       0.0f,
                                                       gradientBottomY,
                                                       false));
            gradientGen.fillAll();
            gradientGen.setColour(Colour(255, 10, 10));
            gradientGen.fillRect(0, 0, getWidth(), static_cast<int>(gradientTopY));
        }
    }

    FFAU::LevelMeterSource* source = nullptr;
    int channel = 0;
    float minGainDisplayValue = 0.0f;
    float maxGainDisplayValue = 1.0f;
    bool needsGradientRegen = true;
    Image gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleLevelMeter)
};
