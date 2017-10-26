/*
  ==============================================================================

    MMTabbedComponent.h
    Created: 13 Oct 2017 12:08:01am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DraggableTabbedComponent.h"

class MobileMixPluginInstance;
class MobileMixPluginInstanceEditor;

class MMTabbedComponent :
    public DraggableTabbedComponent
{
public:
    using DraggableTabbedComponent::DraggableTabbedComponent;
    void addTabForPlugin(MobileMixPluginInstance* plugin, MobileMixPluginInstanceEditor* editor);
    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;

private:
    MobileMixPluginInstance* lastPluginTabAddedFor = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMTabbedComponent)
};
