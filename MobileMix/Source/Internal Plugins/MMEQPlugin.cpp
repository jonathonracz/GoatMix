/*
  ==============================================================================

    MMEQPlugin.cpp
    Created: 15 Sep 2017 11:01:31am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMEQPlugin.h"
#include "MMEQPluginEditor.h"

MMEQPlugin::MMEQPlugin(AudioProcessorValueTreeState& state) :
    MobileMixPluginInstance(state)
{
}

void MMEQPlugin::registerParameters()
{
    // Add parameters here via createParameter...
    paramFrequency1 = state.createAndAddParameter(addPrefixToParameterName("Frequency1"),
                                                          addPrefixToParameterName("Frequency"),
                                                          "",
                                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                          1.0f,
                                                          nullptr,
                                                          nullptr);
    
    paramGain1 = state.createAndAddParameter(addPrefixToParameterName("Gain1"),
                                                  addPrefixToParameterName("Gain"),
                                                  "",
                                                  NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                  1.0f,
                                                  nullptr,
                                                  nullptr);
    
    paramQ1 = state.createAndAddParameter(addPrefixToParameterName("Q1"),
                                             addPrefixToParameterName("Q"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramType1 = state.createAndAddParameter(addPrefixToParameterName("Type1"),
                                             addPrefixToParameterName("Type"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramFrequency2 = state.createAndAddParameter(addPrefixToParameterName("Frequency2"),
                                                  addPrefixToParameterName("Frequency"),
                                                  "",
                                                  NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                  1.0f,
                                                  nullptr,
                                                  nullptr);
    
    paramGain2 = state.createAndAddParameter(addPrefixToParameterName("Gain2"),
                                             addPrefixToParameterName("Gain"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramQ2 = state.createAndAddParameter(addPrefixToParameterName("Q2"),
                                          addPrefixToParameterName("Q"),
                                          "",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                          1.0f,
                                          nullptr,
                                          nullptr);
    
    paramType2 = state.createAndAddParameter(addPrefixToParameterName("Type2"),
                                             addPrefixToParameterName("Type"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramFrequency3 = state.createAndAddParameter(addPrefixToParameterName("Frequency3"),
                                                  addPrefixToParameterName("Frequency"),
                                                  "",
                                                  NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                  1.0f,
                                                  nullptr,
                                                  nullptr);
    
    paramGain3 = state.createAndAddParameter(addPrefixToParameterName("Gain3"),
                                             addPrefixToParameterName("Gain"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramQ3 = state.createAndAddParameter(addPrefixToParameterName("Q3"),
                                          addPrefixToParameterName("Q"),
                                          "",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                          1.0f,
                                          nullptr,
                                          nullptr);
    
    paramType3 = state.createAndAddParameter(addPrefixToParameterName("Type3"),
                                             addPrefixToParameterName("Type"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramFrequency4 = state.createAndAddParameter(addPrefixToParameterName("Frequency4"),
                                                  addPrefixToParameterName("Frequency"),
                                                  "",
                                                  NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                                  1.0f,
                                                  nullptr,
                                                  nullptr);
    
    paramGain4 = state.createAndAddParameter(addPrefixToParameterName("Gain4"),
                                             addPrefixToParameterName("Gain"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
    
    paramQ4 = state.createAndAddParameter(addPrefixToParameterName("Q4"),
                                          addPrefixToParameterName("Q"),
                                          "",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                          1.0f,
                                          nullptr,
                                          nullptr);
    
    paramType4 = state.createAndAddParameter(addPrefixToParameterName("Type4"),
                                             addPrefixToParameterName("Type"),
                                             "",
                                             NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                                             1.0f,
                                             nullptr,
                                             nullptr);
}

AudioProcessorEditor* MMEQPlugin::createEditor()
{
    return new MMEQPluginEditor(*this);
}

void MMEQPlugin::prepareToPlayDerived(double sampleRate, int maximumExpectedSamplesPerBlock)
{
}

void MMEQPlugin::processBlockDerived(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}
