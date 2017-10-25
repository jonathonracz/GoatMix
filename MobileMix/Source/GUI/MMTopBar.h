/*
  ==============================================================================

    MMTopBar.h
    Created: 21 Oct 2017 10:16:29pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../MobileMixPluginProcessor.h"
#include "SVGButton.h"

class MMTopBar :
    public Component,
    public Button::Listener,
    public ChangeListener
{
public:
    MMTopBar(MobileMixAudioProcessor& processor);
    ~MMTopBar() {}

    struct Listener
    {
        virtual ~Listener() {}
        virtual void undoClicked(MMTopBar* bar) = 0;
        virtual void redoClicked(MMTopBar* bar) = 0;
        virtual void infoClicked(MMTopBar* bar) = 0;
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

private:
    void resized() override;
    void buttonClicked(Button* button) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    ListenerList<Listener> listeners;

    MobileMixAudioProcessor& processor;
    SVGButton undoButton;
    SVGButton redoButton;
    SVGButton infoButton;
    std::unique_ptr<Drawable> logoSVG;
};
