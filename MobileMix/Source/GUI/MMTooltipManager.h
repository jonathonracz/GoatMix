/*
  ==============================================================================

    MMTooltipManager.h
    Created: 17 Nov 2017 11:39:31pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MMTooltipManager :
    public MouseListener,
    public Timer
{
public:
    MMTooltipManager(Component& _parent) :
        parent(_parent)
    {
        parent.addMouseListener(this, true);
    }

    ~MMTooltipManager() {}

    struct Listener
    {
        virtual ~Listener() {}
        virtual void displayTooltipForComponent(MMTooltipManager* manager, Component* component, String tooltip) {}
        virtual void hideTooltip(MMTooltipManager* manager) {}
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

    void setActivationTime(int ms) { activationTime = ms; }
    int getActivationTime() const { return activationTime; }

    bool isTooltipShowing() const { return tooltipShown; }

private:
    void mouseDown(const MouseEvent& e) override
    {
        if (!tooltipShown)
            startTimer(activationTime);
    }

    void mouseDrag(const MouseEvent& e) override
    {
        if (e.getDistanceFromDragStart() > 4)
        {
            stopTimer();
            hideTooltip();
        }
    }

    void mouseUp(const MouseEvent& e) override
    {
        stopTimer();
        hideTooltip();
    }

    void timerCallback() override
    {
        stopTimer();
        showTooltip();
    }

    void showTooltip()
    {
        if (!tooltipShown)
        {
            Component* componentUnderCursor = parent.getComponentAt(parent.getMouseXYRelative());
            if (TooltipClient* component = dynamic_cast<TooltipClient*>(componentUnderCursor))
            {
                if (component->getTooltip().isEmpty())
                    return;

                listeners.call(&Listener::displayTooltipForComponent, this, componentUnderCursor, component->getTooltip());
                tooltipShown = true;
            }
        }
    }

    void hideTooltip()
    {
        if (tooltipShown)
        {
            listeners.call(&Listener::hideTooltip, this);
            tooltipShown = false;
        }
    }

    int activationTime = 500;
    bool tooltipShown = false;
    ListenerList<Listener> listeners;
    Component& parent;
};
