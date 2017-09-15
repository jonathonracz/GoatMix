/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP/Gain.h"
#include "DSP/PitchShift.h"
#include "DSP/BufferSizeAdaptor.h"


//==============================================================================
MobileMixAudioProcessor::MobileMixAudioProcessor() :
    parameters(*this, nullptr),
    input(AudioGraphIOProcessor::IODeviceType::audioInputNode),
    output(AudioGraphIOProcessor::IODeviceType::audioOutputNode)
{
}

MobileMixAudioProcessor::~MobileMixAudioProcessor()
{
}

bool MobileMixAudioProcessor::hasEditor() const
{
    return false;
}

AudioProcessorEditor* MobileMixAudioProcessor::createEditor()
{
    return new MobileMixAudioProcessorEditor(*this);
}

bool MobileMixAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::stereo());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
