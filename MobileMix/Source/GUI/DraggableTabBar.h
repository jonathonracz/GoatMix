/*
  ==============================================================================

    DraggableTabBar.h
    Created: 16 Sep 2017 7:15:53pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DraggableTabBar :
    public TabbedButtonBar
{
public:
    DraggableTabBar(Orientation orientation);
    ~DraggableTabBar();
    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;
};
