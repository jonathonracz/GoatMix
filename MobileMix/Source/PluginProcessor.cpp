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

#include "Processors/GainProcessor.h"

const char* orderedIndexValueKey = "orderedIndex";

MobileMixAudioProcessor::MobileMixAudioProcessor() :
    linearGraph(AudioChannelSet::stereo())
{
}

MobileMixAudioProcessor::~MobileMixAudioProcessor()
{
}

void MobileMixAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    linearGraph.prepareToPlay(sampleRate, samplesPerBlock);
}

void MobileMixAudioProcessor::releaseResources()
{
    linearGraph.releaseResources();
}

bool MobileMixAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // We're assuming EVERYTHING in this plugin will ALWAYS be stereo.
    return (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::stereo());
}

void MobileMixAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    linearGraph.processBlock(buffer, midiMessages);
}

AudioProcessorEditor* MobileMixAudioProcessor::createEditor()
{
    return new MobileMixAudioProcessorEditor(*this);
}

bool MobileMixAudioProcessor::hasEditor() const
{
    return true;
}

const String MobileMixAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MobileMixAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool MobileMixAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double MobileMixAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MobileMixAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int MobileMixAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MobileMixAudioProcessor::setCurrentProgram(int index)
{
}

const String MobileMixAudioProcessor::getProgramName(int index)
{
    return {};
}

void MobileMixAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void MobileMixAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    linearGraph.getStateInformation(destData);
}

void MobileMixAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    linearGraph.setStateInformation(data, sizeInBytes);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MobileMixAudioProcessor();
}
