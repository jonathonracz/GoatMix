/*
  ==============================================================================

    MMCompressorPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMCompressorPlugin.h"
#include "MMCompressorPluginEditor.h"

MMCompressorPlugin::MMCompressorPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMCompressorPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramAttack = state.createAndAddParameter(addPrefixToParameterName("Attack"),
                                                          addPrefixToParameterName("Attack"),
                                                          "",
                                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                          1.0f,
                                                          nullptr,
                                                          nullptr);
    
    paramRelease = state.createAndAddParameter(addPrefixToParameterName("Release"),
                                              addPrefixToParameterName("Release"),
                                              "",
                                              NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                              1.0f,
                                              nullptr,
                                              nullptr);
    
    paramRatio = state.createAndAddParameter(addPrefixToParameterName("Ratio"),
                                              addPrefixToParameterName("Ratio"),
                                              "",
                                              NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                              1.0f,
                                              nullptr,
                                              nullptr);
    
    paramThreshold = state.createAndAddParameter(addPrefixToParameterName("Threshold"),
                                                 addPrefixToParameterName("Threshold"),
                                                 "",
                                                 NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                 1.0f,
                                                 nullptr,
                                                 nullptr);
    
    paramMakeupGain = state.createAndAddParameter(addPrefixToParameterName("Makeup Gain"),
                                              addPrefixToParameterName("Makeup Gain"),
                                              "",
                                              NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                              1.0f,
                                              nullptr,
                                              nullptr);
    
    
    paramDryWet = state.createAndAddParameter(addPrefixToParameterName("Dry/Wet"),
                                              addPrefixToParameterName("Dry/Wet"),
                                              "",
                                              NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                              1.0f,
                                              nullptr,
                                              nullptr);
}

AudioProcessorEditor* MMCompressorPlugin::createEditor()
{
    return new MMCompressorPluginEditor(*this);
}

void MMCompressorPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
}

void MMCompressorPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}
