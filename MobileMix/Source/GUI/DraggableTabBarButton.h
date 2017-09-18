/*
  ==============================================================================

    DraggableTabBarButton.h
    Created: 16 Sep 2017 7:25:01pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Processors/LinearAudioProcessorGraphEditor.h"

class DraggableTabBarButton :
    public TabBarButton
{
public:
    DraggableTabBarButton(const String& name, TabbedButtonBar& ownerBar, LinearAudioProcessorGraphEditor& modelView);
    ~DraggableTabBarButton();

protected:
    int getBestTabLength(int depth) override;
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

private:
    ComponentDragger dragger;
    ComponentBoundsConstrainer ownerConstrain;
    LinearAudioProcessorGraphEditor& modelView;

    void setMoveTriggersFromTab(int index);
    int triggerTabUpX;
    int triggerTabDownX;
};
