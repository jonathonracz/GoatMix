/*
  ==============================================================================

    DraggableTabBarButton.h
    Created: 16 Sep 2017 7:25:01pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DraggableTabbedComponent.h"

class DraggableTabBarButton :
    public TabBarButton
{
public:
    DraggableTabBarButton(const String& name, DraggableTabbedComponent& owner);
    ~DraggableTabBarButton();

protected:
    int getBestTabLength(int depth) override;
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

private:
    ComponentDragger dragger;
    ComponentBoundsConstrainer ownerConstrain;
    DraggableTabbedComponent& owner;

    void setMoveTriggersFromTab(int index);
    int triggerTabUpX;
    int triggerTabDownX;
};
