/*
  ==============================================================================

    MMTabBarButton.h
    Created: 13 Oct 2017 12:06:57am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DraggableTabBarButton.h"
#include "../Core/MobileMixPluginInstance.h"

class MMTabBarButton :
    public DraggableTabBarButton
{
public:
    MMTabBarButton(DraggableTabbedComponent& owner, MobileMixPluginInstance& representedPlugin);
    ~MMTabBarButton();

protected:
    void resized() override;

private:
    int getBestTabLength(int depth) override;

    TextButton bypassButton;
    AudioProcessorValueTreeState::ButtonAttachment bypassButtonAttachment;
    MobileMixPluginInstance& representedPlugin;
};
