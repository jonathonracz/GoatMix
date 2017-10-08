/*
  ==============================================================================

    MobileMixPluginFormat.cpp
    Created: 25 Sep 2017 12:34:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginFormat.h"

#include "../Internal Plugins/MMPlugins.h"

MobileMixPluginFormat::MobileMixPluginFormat(AudioProcessor& rootProcessor,
                                             ValueTree& parentState) :
    root(rootProcessor),
    parent(parentState)
{
    gainDesc = MMGainPlugin(root, parent).getPluginDescription();
    compressorDesc = MMCompressorPlugin(root, parent).getPluginDescription();
    reverbDesc = MMReverbPlugin(root, parent).getPluginDescription();
}

void MobileMixPluginFormat::getAllPluginsInExpectedParameterOrder(OwnedArray<PluginDescription>& array)
{
    array.add(new PluginDescription(gainDesc));
    array.add(new PluginDescription(compressorDesc));
    array.add(new PluginDescription(reverbDesc));
}

void MobileMixPluginFormat::createPluginInstance(const PluginDescription& desc,
                                                 double initialSampleRate,
                                                 int initialBufferSize,
                                                 void* userData,
                                                 void (*callback)(void*, AudioPluginInstance*, const String&))
{
    if (desc.isDuplicateOf(gainDesc))
        callback(userData, new MMGainPlugin(root, parent), String());
    else if (desc.isDuplicateOf(compressorDesc))
        callback(userData, new MMCompressorPlugin(root, parent), String());
    else if (desc.isDuplicateOf(reverbDesc))
        callback(userData, new MMReverbPlugin(root, parent), String());
}
