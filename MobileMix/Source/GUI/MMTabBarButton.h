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
    public DraggableTabBarButton,
    public AudioProcessorListener
{
public:
    MMTabBarButton(DraggableTabbedComponent& owner, MobileMixPluginInstance& representedPlugin);
    ~MMTabBarButton();
    
private:
    int getBestTabLength(int depth) override;
    
    void audioProcessorParameterChanged(AudioProcessor *processor, int parameterIndex, float newValue) override;
    void audioProcessorChanged(AudioProcessor *processor) override {}
    
    ShapeButton bypassButton;
    MobileMixPluginInstance& representedPlugin;
};
