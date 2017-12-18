/*
  ==============================================================================

  Divider.h
  Created: 3 Nov 2017 1:40:43am
  Author:  Jeran Norman

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GMLookAndFeel.h"

class Divider :
    public Component
{
public:
    Divider() = default;
    ~Divider() = default;

private:
    void paint(Graphics& g) override
    {
        g.setColour(findColour(GMLookAndFeel::ColourIds::outline));
        g.fillRect(0, 0, getWidth(), getHeight());
    }
};
