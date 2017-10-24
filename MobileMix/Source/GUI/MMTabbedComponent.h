/*
  ==============================================================================

    MMTabbedComponent.h
    Created: 13 Oct 2017 12:08:01am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DraggableTabbedComponent.h"
#include "../Core/MobileMixPluginInstance.h"

class MMTabbedComponent :
    public DraggableTabbedComponent
{
public:
    using DraggableTabbedComponent::DraggableTabbedComponent;
    void addTabForPlugin(MobileMixPluginInstance* plugin);
    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;
    
private:
    MobileMixPluginInstance* lastPluginTabAddedFor = nullptr;

};
