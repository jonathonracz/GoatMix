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
    namespace Gain
    {
        StringRef unit = "dB";

        auto valueToText = [](float value) -> String
        {
            return Decibels::toString(Decibels::gainToDecibels(value), 1);
        };

        auto textToValue = [](const String& text) -> float
        {
            return Decibels::decibelsToGain(text.getFloatValue());
        };
    }
}
