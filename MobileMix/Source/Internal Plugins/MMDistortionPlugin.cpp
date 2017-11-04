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
    paramDownsample = state.createAndAddParameter(addPrefixToParameterName("Downsample"),
                                                          addPrefixToParameterName("Downsample"),
                                                          "",
                                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                          1.0f,
                                                          nullptr,
                                                          nullptr);
    
    paramBitDepth = state.createAndAddParameter(addPrefixToParameterName("Bit Depth"),
                                                addPrefixToParameterName("Bit Depth"),
                                                "",
                                                NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                1.0f,
                                                nullptr,
                                                nullptr);
    
    paramTone = state.createAndAddParameter(addPrefixToParameterName("Tone"),
                                                addPrefixToParameterName("Tone"),
                                                "",
                                                NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                1.0f,
                                                nullptr,
                                                nullptr);
    
    paramDrive = state.createAndAddParameter(addPrefixToParameterName("Drive"),
                                                addPrefixToParameterName("Drive"),
                                                "",
                                                NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                1.0f,
                                                nullptr,
                                                nullptr);
    
    paramClipThreshold1 = state.createAndAddParameter(addPrefixToParameterName("Clip Threshold 1"),
                                                addPrefixToParameterName("Clip Threshold 1"),
                                                "",
                                                NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                1.0f,
                                                nullptr,
                                                nullptr);
    
    paramLowPass = state.createAndAddParameter(addPrefixToParameterName("Low Pass"),
                                                addPrefixToParameterName("Low Pass"),
                                                "",
                                                NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                1.0f,
                                                nullptr,
                                                nullptr);
    
    paramClipThreshold2 = state.createAndAddParameter(addPrefixToParameterName("Clip Threshold 2"),
                                                addPrefixToParameterName("Clip Threshold 2"),
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

    distortion.prepare(spec);
}

void MMDistortionPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    distortion.process(context);
}
