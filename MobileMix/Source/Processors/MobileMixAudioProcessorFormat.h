/*
  ==============================================================================

    MobileMixAudioProcessorFormat.h
    Created: 25 Sep 2017 12:34:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "NestedAudioProcessorFormat.h"
#include "NestedAudioProcessorInstance.h"

class MobileMixAudioProcessorFormat :
    public NestedAudioProcessorFormat
{
public:
    PluginDescription gainDesc;

private:
    void createPluginInstance(const PluginDescription&,
                              double initialSampleRate,
                              int initialBufferSize,
                              void* userData,
                              void (*callback)(void*, AudioPluginInstance*, const String&)) override;
};
