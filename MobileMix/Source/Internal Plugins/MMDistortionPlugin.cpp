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

void MMDistortionPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(maximumExpectedSamplesPerBlock),
        static_cast<uint32>(getMainBusNumInputChannels())
    };

    quantizer.prepare(spec);
    sampleRepeater.prepare(spec);
}

void MMDistortionPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dsp::AudioBlock<float> block(buffer);

    quantizer.params->bitDepth = 8;
    quantizer.process(dsp::ProcessContextReplacing<float>(block));

    sampleRepeater.params->samplesToRepeat = 4;
    sampleRepeater.process(dsp::ProcessContextReplacing<float>(block));
}
