/*
  ==============================================================================

    ValueStringFuncs.h
    Created: 25 Oct 2017 3:18:21pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

namespace ValueStringFuncs
{
    namespace Generic
    {
        auto valueToText = [](float value, String label, int decimalPlaces) -> String
        {
            return String(value, decimalPlaces) + " " + label;
        };

        auto textToValue = [](const String& text) -> float
        {
            return text.getFloatValue();
        };
    }

    namespace OnOff
    {
        auto valueToText = [](float value) -> String
        {
            return (value >= 0.5f) ? "On" : "Off";
        };

        auto textToValue = [](const String& text) -> float
        {
            return (text == "On" || text.getFloatValue() >= 0.5f) ? 1.0f : 0.0f;
        };
    }

    namespace Gain
    {
        const StringRef unit = "dB";
        const NormalisableRange<float> range = NormalisableRange<float>(0.0f, 2.0f, 0.1f, 0.5f);
        const float defaultValue = 1.0f;

        auto valueToText = [](float value) -> String
        {
            float dB = Decibels::gainToDecibels(range.snapToLegalValue(value));
            String prefix = (dB >= 0) ? "+" : String();
            return prefix + String(dB, 1) + " " + unit;
        };

        auto textToValue = [](const String& text) -> float
        {
            return Decibels::decibelsToGain(text.getFloatValue());
        };
    }

    namespace Pan
    {
        const StringRef unit = "°";

        auto valueToText = [](float value) -> String
        {
            String direction;
            if (value > 0.0f)
                direction = "L";
            else if (value < 0.0f)
                direction = "R";
            return String(std::fabs(value), 0) + unit + " " + direction;
        };

        auto textToValue = [](const String& text) -> float
        {
            float multiplier = text.contains("L") ? -1.0f : 1.0f;
            return text.getFloatValue() * multiplier;
        };
    }

    namespace Milliseconds
    {
        const StringRef unit = "ms";
    }

    namespace Filter
    {
        const StringRef unit = "Hz";
        const NormalisableRange<float> range = NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.25f);
        const float defaultValue = 1000.0f;
    }
}
