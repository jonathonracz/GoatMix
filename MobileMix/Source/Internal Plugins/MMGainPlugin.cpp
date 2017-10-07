/*
  ==============================================================================

    MMGainPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMGainPlugin.h"
#include "MMGainPluginEditor.h"

MMGainPlugin::MMGainPlugin(AudioProcessor& rootProcessor,
                           ValueTree& parentState) :
    MobileMixPluginInstance(rootProcessor, parentState)
{
}

void MMGainPlugin::registerParameters()
{
    // Add parameters here via createParameter...
}

AudioProcessorEditor* MMGainPlugin::createEditor()
{
    return new MMGainPluginEditor(*this);
}

const String MMGainPlugin::getName() const
{
    return NEEDS_TRANS("Gain");
}

void MMGainPlugin::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{

}

void MMGainPlugin::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}
