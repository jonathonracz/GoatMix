/*
  ==============================================================================

    GMTopBar.h
    Created: 21 Oct 2017 10:16:29pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../GoatMixPluginProcessor.h"
#include "GMShapeButton.h"

class GMTopBar :
    public Component,
    public Button::Listener,
    public ChangeListener
{
public:
    GMTopBar(GoatMixAudioProcessor& processor);
    ~GMTopBar();

    struct Listener
    {
        virtual ~Listener() {}
        virtual void undoClicked(GMTopBar* bar) = 0;
        virtual void redoClicked(GMTopBar* bar) = 0;
        virtual void infoClicked(GMTopBar* bar) = 0;
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

private:
    void refreshUndoRedoButtonState();

    void resized() override;
    void buttonClicked(Button* button) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    ListenerList<Listener> listeners;

    GoatMixAudioProcessor& processor;
    GMShapeButton undoButton;
    GMShapeButton redoButton;
    GMShapeButton infoButton;
    std::unique_ptr<Drawable> logoSVG;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMTopBar)
};
