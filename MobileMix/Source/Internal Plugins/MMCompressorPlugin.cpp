/*
  ==============================================================================

    MMCompressorPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMCompressorPlugin.h"
#include "MMCompressorPluginEditor.h"

MMCompressorPlugin::MMCompressorPlugin(AudioProcessor& rootProcessor,
                           ValueTree& parentState) :
    MobileMixPluginInstance(rootProcessor, parentState)
{
}

void MMCompressorPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramCompressor = getParameterState().createAndAddParameter(addPrefixToParameterName("Compressor"),
                                                          addPrefixToParameterName("Compressor"),
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

const String MMCompressorPlugin::getName() const
{
    return "Compressor";
}

void MMCompressorPlugin::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{

}

void MMCompressorPlugin::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}
