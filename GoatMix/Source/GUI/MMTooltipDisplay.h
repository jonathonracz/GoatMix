/*
  ==============================================================================

    MMTooltipDisplay.h
    Created: 18 Nov 2017 1:14:54am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MMTooltipManager.h"

class MMTooltipDisplay :
    public Component,
    public MMTooltipManager::Listener
{
public:
    MMTooltipDisplay(Component& _parent) :
        manager(_parent),
        parent(_parent)
    {
        setAlwaysOnTop(true);
        setInterceptsMouseClicks(false, true);
        setAlpha(static_cast<float>(manager.isTooltipShowing()));
        manager.addListener(this);
        parent.addAndMakeVisible(this);
    }

    ~MMTooltipDisplay() {}

private:
    void parentSizeChanged() override
    {
        setBounds(parent.getLocalBounds());
    }

    void paint(Graphics& g) override
    {
        if (buffer.getBounds() != getLocalBounds() || isDirty)
        {
            buffer = Image(Image::PixelFormat::ARGB, getWidth(), getHeight(), true);
            Graphics bufferPainter(buffer);
            bufferPainter.fillAll(Colours::black.withAlpha(0.85f));
            buffer.clear(tooltipTargetBounds);
            bufferPainter.setColour(Colours::white);
            bufferPainter.drawFittedText(
                tooltipText,
                getLocalBounds().withSizeKeepingCentre(static_cast<int>(getWidth() * 0.95f), static_cast<int>(getHeight() * 0.95f)),
                Justification::Flags::centredTop,
                32,
                1.0f);
            isDirty = false;
        }

        g.drawImageAt(buffer, 0, 0);
    }

    void displayTooltipForComponent(MMTooltipManager* manager, Component* component, String tooltip) override
    {
        isDirty = true;
        tooltipText = tooltip;
        tooltipTargetBounds = getLocalArea(component, component->getLocalBounds());
        Desktop::getInstance().getAnimator().fadeIn(this, 100);
    }

    void hideTooltip(MMTooltipManager* manager) override
    {
        Desktop::getInstance().getAnimator().fadeOut(this, 100);
    }

    Image buffer;
    String tooltipText;
    Rectangle<int> tooltipTargetBounds;
    bool isDirty = true;
    MMTooltipManager manager;
    Component& parent;
};
