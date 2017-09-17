/*
  ==============================================================================

    DraggableTab.h
    Created: 16 Sep 2017 7:25:01pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DraggableTab :
    public TabBarButton
{
public:
    DraggableTab(const String& name, TabbedButtonBar& ownerBar);
    ~DraggableTab();

protected:
    int getBestTabLength (int depth) override;
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

private:
    ComponentDragger dragger;
    ComponentBoundsConstrainer ownerConstrain;

    void setMoveTriggersFromTab(int index);
    int triggerTabUpX;
    int triggerTabDownX;
};
