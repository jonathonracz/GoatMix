/*
  ==============================================================================

    DraggableTabBar.cpp
    Created: 16 Sep 2017 7:15:53pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "DraggableTabBar.h"
#include "DraggableTab.h"

DraggableTabBar::DraggableTabBar(Orientation orientation) :
    TabbedButtonBar(orientation)
{
}

DraggableTabBar::~DraggableTabBar()
{
}

TabBarButton* DraggableTabBar::createTabButton(const String& tabName, int tabIndex)
{
    return new DraggableTab(tabName, *this);
}
