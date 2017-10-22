/*
  ==============================================================================

    MMTabBarButton.cpp
    Created: 13 Oct 2017 12:06:57am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMTabBarButton.h"

MMTabBarButton::MMTabBarButton(DraggableTabbedComponent& _owner, MobileMixPluginInstance& _representedPlugin) :
    DraggableTabBarButton(_representedPlugin.getName(), _owner),
    bypassButton(_representedPlugin.getName() + "BypassButton"),
    bypassButtonAttachment(_representedPlugin.state, _representedPlugin.paramBypass->paramID, bypassButton),
    representedPlugin(_representedPlugin)
{
    bypassButton.setClickingTogglesState(true); // Make it a toggle
    addAndMakeVisible(bypassButton);
}

MMTabBarButton::~MMTabBarButton()
{
}

void MMTabBarButton::resized()
{
    bypassButton.setBounds(getLocalBounds().removeFromRight(getWidth() / 2));
}

int MMTabBarButton::getBestTabLength(int depth)
{
    return owner.getWidth() / owner.getNumTabs();
}
