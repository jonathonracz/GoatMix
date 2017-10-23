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
#include "SVGButton.h"

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
    SVGButton undoButton;
    SVGButton redoButton;
    std::unique_ptr<Drawable> logoSVG;
    std::unique_ptr<Drawable> undoSVG;
    std::unique_ptr<Drawable> redoSVG;
};
