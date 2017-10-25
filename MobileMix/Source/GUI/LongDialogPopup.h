/*
  ==============================================================================

    LongDialogPopup.h
    Created: 24 Oct 2017 3:20:25pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class LongDialogPopup :
    public Component,
    public Button::Listener
{
public:
    LongDialogPopup(const String& textToDisplay) :
        closeButton(NEEDS_TRANS("Close"))
    {
        display.setReadOnly(true);
        display.setMultiLine(true);
        display.setCaretVisible(false);
        display.setText(textToDisplay);
        closeButton.addListener(this);
        addAndMakeVisible(display);
        addAndMakeVisible(closeButton);
    }

    ~LongDialogPopup() {}

    struct Listener
    {
        virtual ~Listener() {}
        virtual void closeButtonClicked(LongDialogPopup* dialog) = 0;
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

private:
    void visibilityChanged() override
    {
        if (isVisible())
        {
        }
    }

    void resized() override
    {
        display.setBoundsRelative(0.0f, 0.0f, 0.5f, 0.9f);
        display.setCentreRelative(0.5f, 0.5f);
        closeButton.setBoundsRelative(0.05f, 0.05f, 0.1f, 0.1f);
    }

    void paint(Graphics& g) override
    {
        g.fillAll(Colour(0x7f000000));
    }

    void buttonClicked(Button* button) override
    {
        BailOutChecker checker(this);
        listeners.callChecked(checker, &Listener::closeButtonClicked, this);
    }

    ListenerList<Listener> listeners;
    TextButton closeButton;
    TextEditor display;
};
