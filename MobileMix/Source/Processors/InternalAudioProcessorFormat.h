/*
  ==============================================================================

    InternalAudioProcessorFormat.h
    Created: 24 Sep 2017 11:50:40pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class InternalAudioProcessorFormat :
    public AudioPluginFormat
{
public:
    String getName() const override                                                     { return "Internal"; }
    bool fileMightContainThisPluginType(const String&) override                         { return true; }
    FileSearchPath getDefaultLocationsToSearch() override                               { return {}; }
    bool canScanForPlugins() const override                                             { return false; }
    void findAllTypesForFile(OwnedArray <PluginDescription>&, const String&) override   {}
    bool doesPluginStillExist(const PluginDescription&) override                        { return true; }
    String getNameOfPluginFromIdentifier(const String& fileOrIdentifier) override       { return fileOrIdentifier; }
    bool pluginNeedsRescanning(const PluginDescription&) override                       { return false; }
    StringArray searchPathsForPlugins(const FileSearchPath&, bool, bool) override       { return {}; }

private:
    bool requiresUnblockedMessageThreadDuringCreation(const PluginDescription&) const noexcept override { return false; }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InternalAudioProcessorFormat)
};
