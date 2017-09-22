/*
  ==============================================================================

    DraggableTabbedComponent.cpp
    Created: 21 Sep 2017 8:34:18pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "DraggableTabbedComponent.h"
#include "DraggableTabBarButton.h"

void DraggableTabbedComponent::addTabWithNotification(const String& tabName,
                                                      Colour tabBackgroundColour,
                                                      Component* contentComponent,
                                                      bool deleteComponentWhenNotNeeded,
                                                      int insertIndex)
{
    addTab(tabName, tabBackgroundColour, contentComponent, deleteComponentWhenNotNeeded, insertIndex);
    int newTabIndex = (insertIndex >= 0) ? insertIndex : getNumTabs() - 1;
    listeners.call(&Listener::tabAdded, newTabIndex);
}

void DraggableTabbedComponent::removeTabWithNotification(int tabIndex)
{
    removeTab(tabIndex);
    listeners.call(&Listener::tabRemoved, tabIndex);
}

void DraggableTabbedComponent::moveTabWithNotification(int currentIndex, int newIndex, bool animate)
{
    moveTab(currentIndex, newIndex, animate);
    // Note that here newIndex and currentIndex are switched, because otherwise
    // this listener callback would be following the tab moved as a result of
    // tab dragging rather than the dragged tab itself.
    listeners.call(&Listener::tabMovedViaDrag, newIndex, currentIndex);
}

void DraggableTabbedComponent::addListener(Listener* listener)
{
    listeners.add(listener);
}

void DraggableTabbedComponent::removeListener(Listener* listener)
{
    listeners.remove(listener);
}

TabBarButton* DraggableTabbedComponent::createTabButton(const String& tabName, int tabIndex)
{
    return new DraggableTabBarButton(tabName, *this);
}
