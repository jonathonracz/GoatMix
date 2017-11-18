/*
  ==============================================================================

    SharedTooltips.h
    Created: 17 Nov 2017 11:16:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

namespace SharedTooltips
{
    StringRef dryWet = NEEDS_TRANS("The mix of \"dry\" (without this effect) and \"wet\" (processed through this effect) signal. 0% is the original signal, 100% is entirely processed through this effect.");
    StringRef gain = NEEDS_TRANS("Changes the volume of the signal passing through.");
    StringRef meter = NEEDS_TRANS("A visual indicator of how loud the signal is. A higher green level means the volume is higher. Red means you're causing distortion by being too loud, and should turn down the gain!");
    StringRef filterEnable = NEEDS_TRANS("Enables and disables this filter.");
    StringRef filterControl = NEEDS_TRANS("Adjusts the center frequency of the filter. In other words, how high or low of frequencies should be allowed through.");
}
