/*
  ==============================================================================

    MMGainPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMGainPlugin.h"
#include "MMGainPluginEditor.h"
#include "../GUI/ValueStringFuncs.h"

MMGainPlugin::MMGainPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMGainPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramGain = state.createAndAddParameter(addPrefixToParameterName("Gain"),
                                            addPrefixToParameterName("Gain"),
                                            ValueStringFuncs::Gain::unit,
                                            NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                            1.0f,
                                            ValueStringFuncs::Gain::valueToText,
                                            ValueStringFuncs::Gain::textToValue);
}

AudioProcessorEditor* MMGainPlugin::createEditor()
{
    return new MMGainPluginEditor(*this);
}

const String MMGainPlugin::getName() const
{
    return "Gain";
}

void MMGainPlugin::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    MobileMixPluginInstance::prepareToPlay(sampleRate, maximumExpectedSamplesPerBlock);
}

void MMGainPlugin::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    MobileMixPluginInstance::processBlock(buffer, midiMessages);
}
