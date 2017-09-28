/*
  ==============================================================================

    GainProcessor.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GainProcessor.h"
#include "GainProcessorEditor.h"

GainProcessor::GainProcessor(AudioProcessor& rootProcessor,
                             AudioProcessorValueTreeState& parentState) :
    MobileMixAudioProcessor(rootProcessor, parentState)
{
}

AudioProcessorEditor* GainProcessor::createEditor()
{
    return new GainProcessorEditor(*this);
}

const String GainProcessor::getName() const
{
    return TRANS("Gain");
}

void GainProcessor::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{

}

void GainProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}
