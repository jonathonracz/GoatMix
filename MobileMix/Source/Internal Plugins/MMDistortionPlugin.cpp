/*
  ==============================================================================

    MMDistortionPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMDistortionPlugin.h"
#include "MMDistortionPluginEditor.h"

MMDistortionPlugin::MMDistortionPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMDistortionPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramDistortion = state.createAndAddParameter(addPrefixToParameterName("Distortion"),
                                                          addPrefixToParameterName("Distortion"),
                                                          "",
                                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                          1.0f,
                                                          nullptr,
                                                          nullptr);
}

AudioProcessorEditor* MMDistortionPlugin::createEditor()
{
    return new MMDistortionPluginEditor(*this);
}

const String MMDistortionPlugin::getName() const
{
    return "Distortion";
}

void MMDistortionPlugin::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{

}

void MMDistortionPlugin::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}
