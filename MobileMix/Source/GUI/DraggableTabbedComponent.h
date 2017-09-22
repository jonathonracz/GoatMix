/*
  ==============================================================================

    DraggableTabbedComponent.h
    Created: 21 Sep 2017 8:34:18pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DraggableTabbedComponent :
    public TabbedComponent
{
public:
    using TabbedComponent::TabbedComponent;

    struct Listener
    {
        virtual ~Listener() {}
        virtual void tabAdded(int index) {}
        virtual void tabRemoved(int index) {}
        virtual void tabMoved(int fromIndex, int toIndex) {}
    };

    void addTabWithNotification(const String& tabName,
                                Colour tabBackgroundColour,
                                Component* contentComponent,
                                bool deleteComponentWhenNotNeeded,
                                int insertIndex = -1);
    void removeTabWithNotification(int tabIndex);
    void moveTabWithNotification(int currentIndex, int newIndex, bool animate = false);

    void addListener(Listener* listener);
    void removeListener(Listener* listener);

    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;

private:
    ListenerList<Listener> listeners;
};
