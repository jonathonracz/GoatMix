/*
  ==============================================================================

    MMReverbPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMReverbPlugin.h"
#include "MMReverbPluginEditor.h"

MMReverbPlugin::MMReverbPlugin(AudioProcessor& rootProcessor,
                           ValueTree& parentState) :
    MobileMixPluginInstance(rootProcessor, parentState)
{
}

void MMReverbPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramReverb = getParameterState().createAndAddParameter(addPrefixToParameterName("Reverb"),
                                                          addPrefixToParameterName("Reverb"),
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

const String MMReverbPlugin::getName() const
{
    return "Reverb";
}

void MMReverbPlugin::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{

}

void MMReverbPlugin::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}
