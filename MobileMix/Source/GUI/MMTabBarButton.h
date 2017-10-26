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
#include "MMMuteButton.h"

class MMTabBarButton :
    public DraggableTabBarButton
{
public:
    MMTabBarButton(DraggableTabbedComponent& owner, MobileMixPluginInstance& representedPlugin);
    ~MMTabBarButton();

protected:
    void resized() override;
    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

private:
    int getBestTabLength(int depth) override;

    std::unique_ptr<Drawable> shadow;
    std::unique_ptr<Drawable> muteButtonBg;
    MMMuteButton bypassButton;
    AudioProcessorValueTreeState::ButtonAttachment bypassButtonAttachment;
    MobileMixPluginInstance& representedPlugin;
    FFAU::LevelMeter meter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMTabBarButton)
};
