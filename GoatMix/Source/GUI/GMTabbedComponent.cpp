/*
  ==============================================================================

    GMTabbedComponent.cpp
    Created: 13 Oct 2017 12:08:01am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMTabbedComponent.h"
#include "GMTabBarButton.h"
#include "../Core/GMPluginInstance.h"
#include "../Core/GMPluginInstanceEditor.h"

GMTabbedComponent::GMTabbedComponent(TabbedButtonBar::Orientation orientation) :
    DraggableTabbedComponent(orientation)
{
    setOutline(0);
    setIndent(0);
    setOpaque(false);
}

void GMTabbedComponent::addTabForPlugin(GMPluginInstance* plugin)
{
    lastPluginTabAddedFor = plugin;
    addTab(plugin->getDisplayName(), Colours::transparentWhite, plugin->createGoatMixEditor(), true);
}

TabBarButton* GMTabbedComponent::createTabButton(const String& tabName, int tabIndex)
{
    jassert(lastPluginTabAddedFor);
    return new GMTabBarButton(*this, *lastPluginTabAddedFor);
}
