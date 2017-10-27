/*
  ==============================================================================

    MMTabbedComponent.cpp
    Created: 13 Oct 2017 12:08:01am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMTabbedComponent.h"
#include "MMTabBarButton.h"
#include "../Core/MobileMixPluginInstance.h"
#include "../Core/MobileMixPluginInstanceEditor.h"

void MMTabbedComponent::addTabForPlugin(MobileMixPluginInstance* plugin)
{
    lastPluginTabAddedFor = plugin;
    addTab(plugin->getName(), Colours::white, plugin->createEditor(), true);
}

TabBarButton* MMTabbedComponent::createTabButton(const String& tabName, int tabIndex)
{
    jassert(lastPluginTabAddedFor);
    return new MMTabBarButton(*this, *lastPluginTabAddedFor);
}
