/*
  ==============================================================================

    MMTopBar.h
    Created: 21 Oct 2017 10:16:29pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MMButtonAppearances.h"

class MMTopBar :
    public Component
{
public:
    MMTopBar();
    ~MMTopBar() {}

private:
    void resized();

    DrawableButton undoButton;
    DrawableButton redoButton;
    std::unique_ptr<DrawableComposite> logo;
    MMStaticButton buttonAppearance;
};
