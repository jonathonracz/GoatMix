/*
  ==============================================================================

    UIStrings.h
    Created: 17 Nov 2017 11:16:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define GM_HINT(name, value) const String name = TRANS(value);

namespace UIStrings
{

namespace Shared
{
    GM_HINT(dryWet, "The mix of \"dry\" (without this effect) and \"wet\" (processed through this effect) signal. 0% is the original signal, 100% is entirely processed through this effect.")
    GM_HINT(gain, "Changes the volume of the signal passing through.")
    GM_HINT(meter, "A visual indicator of how loud the signal passing through is. A higher green level means the volume is higher. Red means you're causing distortion by being too loud, and should turn down the gain!");
    GM_HINT(filterEnable, "Enables and disables this filter.")
    GM_HINT(filterControl, "Adjusts the center frequency of the filter. In other words, how high or low of frequencies should be allowed through.")
}

namespace Meta
{
    GM_HINT(undo, "Undos the previous action.")
    GM_HINT(redo, "Redos the last undone action.")
    GM_HINT(info, "Shows about and acknowledgements.")
    GM_HINT(mute, "Enables or disables this tab, so audio will pass through unaffected.")
    GM_HINT(tab, "This represents a stage in the processor. These can be rearranged to change the order in which sound passes through them.")
}

namespace Gain
{
    GM_HINT(displayName, "Gain")
    GM_HINT(meterValue, "This gives a numerical mesaure of what the animated meter is showing in the form of the peak value in dBFS. Anything above +0.00 dB is too loud and may cause clipping.")
    GM_HINT(pan, "\"Moves\" the sound left and right in the audio space.")
    GM_HINT(phaseDelay, "Delays the given channel, and is often used to make a sound \"wider\".")
    GM_HINT(phaseInvert, "Inverts the amplitude of the signal on the given channel. Useful for finding phase issues in the low frequency range.")
    GM_HINT(goniometer, "This is called a Gonoimeter, and is a visual representation of how \"wide\" and/or balanced sound is.")
}

namespace Compressor
{
    GM_HINT(displayName, "Compress")
    GM_HINT(attack, "The speed at which the incoming signal is compressed to the destination ratio.")
    GM_HINT(release, "The speed at which the incoming signal is released after dipping below the compression threshold.")
    GM_HINT(ratio, "The amount of compression, as a ratio of what level louder parts of the signal are compressed to the threshold level.")
    GM_HINT(threshold, "The level at which compression should become active. Generally, the lower the threshold, the more compression will be active.")
    GM_HINT(preview, "A visual display of what's going on inside the compressor. The horizontal axis is the original magnitude range, the vertical axis is the modified magnitude range.")
}

namespace Reverb
{
    GM_HINT(displayName, "Reverb")
    GM_HINT(preview, "A visual representation of how the reverb behaves on a signal.")
    GM_HINT(roomSize, "An abstract \"room size\" representation which changes the \"size\" of the reverb.")
    GM_HINT(damping, "Changes the reflection intensity of the simulated room - i.e. walls made of concrete vs. stone.")
    GM_HINT(width, "Changes the apparent wideness of the reverb, otherwise known as the stereo image.")
    GM_HINT(freeze, "Makes the current reverb cycle endlessly. Useful for \"dreamy\" sounding effects.")
}

namespace Distortion
{
    GM_HINT(displayName, "Distort")
    GM_HINT(downsample, "Repeats parts of the signal at the sample level. Useful for a \"lo-fi\" sound.")
    GM_HINT(bitDepth, "Quantizes the magnitude of the signal to match different bit depths.")
    GM_HINT(overdrive, "Adds soft clipping for a guitar-amp like sound.")
    GM_HINT(preview, "Shows a preview of how the current distortion settings are affecting the sound on a simple size wave.")
}

namespace EQ
{
    GM_HINT(displayName, "Equalize")
    GM_HINT(preview, "A preview of how the EQ is affecting the frequencies of the incoming signal.")
    GM_HINT(cutoff, "Changes the center frequency of the filter.")
    GM_HINT(q, "Changes how wide of a frequency band the filter affects.")
    GM_HINT(type, "Sets the shape of the filter, changing how it affects frequencies.")
}

}

#undef GM_HINT
