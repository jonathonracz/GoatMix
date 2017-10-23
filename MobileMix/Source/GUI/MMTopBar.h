/*
  ==============================================================================

    MMTopBar.h
    Created: 21 Oct 2017 10:16:29pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../MobileMixPluginProcessor.h"

class MMTopBar :
    public Component,
    public Button::Listener,
    public ChangeListener
{
public:
    MMTopBar(MobileMixAudioProcessor& processor);
    ~MMTopBar() {}

private:
    void resized() override;
    void buttonClicked(Button* button) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    MobileMixAudioProcessor& processor;
    DrawableButton undoButton;
    DrawableButton redoButton;
    std::unique_ptr<Drawable> logoSVG;
    std::unique_ptr<Drawable> undoSVG;
    std::unique_ptr<Drawable> redoSVG;
};
