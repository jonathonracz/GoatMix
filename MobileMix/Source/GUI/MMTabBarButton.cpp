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
    bypassButton(_representedPlugin.getName() + "BypassButton", Colours::green, Colours::blue, Colours::red),
    representedPlugin(_representedPlugin)
{
    representedPlugin.addListener(this);
    addAndMakeVisible(bypassButton);
}

MMTabBarButton::~MMTabBarButton()
{
    representedPlugin.removeListener(this);
}

int MMTabBarButton::getBestTabLength(int depth)
{
    return owner.getWidth() / owner.getNumTabs();
}

void MMTabBarButton::audioProcessorParameterChanged(AudioProcessor *processor, int parameterIndex, float newValue)
{
    if (parameterIndex == representedPlugin.paramBypass->getParameterIndex())
    {
        bypassButton.setToggleState(representedPlugin.isBypassed(), NotificationType::dontSendNotification);
    }
}
