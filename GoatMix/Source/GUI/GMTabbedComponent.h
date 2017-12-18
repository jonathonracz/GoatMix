/*
  ==============================================================================

    GMTabbedComponent.h
    Created: 13 Oct 2017 12:08:01am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DraggableTabbedComponent.h"

class GoatMixPluginInstance;
class GoatMixPluginInstanceEditor;

class GMTabbedComponent :
    public DraggableTabbedComponent
{
public:
    GMTabbedComponent(TabbedButtonBar::Orientation orientation);
    ~GMTabbedComponent() {}
    void addTabForPlugin(GoatMixPluginInstance* plugin);
    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;

private:
    GoatMixPluginInstance* lastPluginTabAddedFor = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMTabbedComponent)
};
