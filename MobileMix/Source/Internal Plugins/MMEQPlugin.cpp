/*
  ==============================================================================

    MMEQPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMEQPlugin.h"
#include "MMEQPluginEditor.h"

MMEQPlugin::MMEQPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMEQPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramEQ = state.createAndAddParameter(addPrefixToParameterName("EQ"),
                                                          addPrefixToParameterName("EQ"),
                                                          "",
                                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                          1.0f,
                                                          nullptr,
                                                          nullptr);
}

AudioProcessorEditor* MMEQPlugin::createEditor()
{
    return new MMEQPluginEditor(*this);
}

const String MMEQPlugin::getName() const
{
    return "EQ";
}

void MMEQPlugin::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{

}

void MMEQPlugin::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}
