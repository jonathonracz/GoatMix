/*
  ==============================================================================

    GMTabBarButton.h
    Created: 13 Oct 2017 12:06:57am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "DraggableTabBarButton.h"
#include "../Core/GoatMixPluginInstance.h"
#include "GMShapeButton.h"
#include "SimpleMultiLevelMeter.h"

class GMTabBarButton :
    public DraggableTabBarButton,
    public DraggableTabbedComponent::Listener
{
public:
    GMTabBarButton(DraggableTabbedComponent& owner, GoatMixPluginInstance& representedPlugin);
    ~GMTabBarButton();

protected:
    void resized() override;
    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

private:
    int getBestTabLength(int depth) override;
    void tabDragStarted(int atIndex) override;
    void tabDragEnded(int atIndex) override;

    std::unique_ptr<Drawable> shadow;
    std::unique_ptr<Drawable> muteButtonBg;
    GMShapeButton bypassButton;
    AudioProcessorValueTreeState::ButtonAttachment bypassButtonAttachment;
    GoatMixPluginInstance& representedPlugin;
    SimpleMultiLevelMeter meter;
    Image freezeSnapshot;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMTabBarButton)
};
