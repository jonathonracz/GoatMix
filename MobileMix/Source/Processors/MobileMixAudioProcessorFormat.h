/*
  ==============================================================================

    MobileMixAudioProcessorFormat.h
    Created: 25 Sep 2017 12:34:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "InternalAudioProcessorFormat.h"

class MobileMixAudioProcessorFormat :
    public InternalAudioProcessorFormat
{
public:
    PluginDescription gainDesc;

private:
    void createPluginInstance(const PluginDescription&,
                              double initialSampleRate,
                              int initialBufferSize,
                              void* userData,
                              void (*callback)(void*, AudioPluginInstance*, const String&)) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixAudioProcessorFormat)
};
