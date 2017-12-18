/*
  ==============================================================================

    GoatMixPluginFormat.cpp
    Created: 25 Sep 2017 12:34:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GoatMixPluginFormat.h"

#include "../Internal Plugins/GMPlugins.h"

GoatMixPluginFormat::GoatMixPluginFormat(AudioProcessorValueTreeState& _state) :
    state(_state)
{
    gainDesc = GMGainPlugin(state).getPluginDescription();
    compressorDesc = GMCompressorPlugin(state).getPluginDescription();
    reverbDesc = GMReverbPlugin(state).getPluginDescription();
    distortionDesc = GMDistortionPlugin(state).getPluginDescription();
    eqDesc = GMEQPlugin(state).getPluginDescription();
}

void GoatMixPluginFormat::getAllPluginsInExpectedParameterOrder(OwnedArray<PluginDescription>& array)
{
    array.add(new PluginDescription(gainDesc));
    array.add(new PluginDescription(compressorDesc));
    array.add(new PluginDescription(reverbDesc));
    array.add(new PluginDescription(distortionDesc));
    array.add(new PluginDescription(eqDesc));
}

void GoatMixPluginFormat::createPluginInstance(const PluginDescription& desc,
                                                 double initialSampleRate,
                                                 int initialBufferSize,
                                                 void* userData,
                                                 void (*callback)(void*, AudioPluginInstance*, const String&))
{
    if (desc.isDuplicateOf(gainDesc))
        callback(userData, new GMGainPlugin(state), String());
    else if (desc.isDuplicateOf(compressorDesc))
        callback(userData, new GMCompressorPlugin(state), String());
    else if (desc.isDuplicateOf(reverbDesc))
        callback(userData, new GMReverbPlugin(state), String());
    else if (desc.isDuplicateOf(distortionDesc))
        callback(userData, new GMDistortionPlugin(state), String());
    else if (desc.isDuplicateOf(eqDesc))
        callback(userData, new GMEQPlugin(state), String());
}
