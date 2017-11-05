/*
  ==============================================================================

    MMReverbPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMReverbPlugin.h"
#include "MMReverbPluginEditor.h"

MMReverbPlugin::MMReverbPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMReverbPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    
    paramHighPass = state.createAndAddParameter(addPrefixToParameterName("High Pass"),
                                            addPrefixToParameterName("High Pass"),
                                            "",
                                            NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                            1.0f,
                                            nullptr,
                                            nullptr);
    
    paramLowPass = state.createAndAddParameter(addPrefixToParameterName("LowPass"),
                                            addPrefixToParameterName("LowPass"),
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

AudioProcessorEditor* MMReverbPlugin::createEditor()
{
    return new MMReverbPluginEditor(*this);
}

void MMReverbPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
}

void MMReverbPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}
