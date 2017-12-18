/*
  ==============================================================================

    LongDialogPopup.h
    Created: 24 Oct 2017 3:20:25pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GMLookAndFeel.h"

class LongDialogPopup :
    public Component
{
public:
    LongDialogPopup(const String& _textToDisplay) :
        textToDisplay(_textToDisplay)
    {
        setVisible(false);
    }

    ~LongDialogPopup() {}

    struct Listener
    {
        virtual ~Listener() {}
        virtual void dismissed(LongDialogPopup* dialog) = 0;
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

    void show()
    {
        setVisible(true);
    }

    void hide()
    {
        setVisible(false);
    }

private:
    void paint(Graphics& g) override
    {
        g.fillAll(Colour(0xcf000000));
        g.setColour(Colours::white);
        g.drawFittedText(
            textToDisplay,
            getBounds().withSizeKeepingCentre(static_cast<int>(getWidth() * 0.8f), getHeight()),
            Justification::Flags::centred,
            INT_MAX,
            1.0f);
    }

    void mouseUp(const MouseEvent& e) override
    {
        hide();
        BailOutChecker checker(this);
        listeners.callChecked(checker, &Listener::dismissed, this);
    }

    const float fadeTime = 1.0f;
    ListenerList<Listener> listeners;
    String textToDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LongDialogPopup)
};
