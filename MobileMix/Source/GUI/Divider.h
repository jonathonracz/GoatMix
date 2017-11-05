//
//  Divider.h
//  MobileMix
//
//  Created by Jeran Norman on 11/3/17.
//

#pragma once

#include "JuceHeader.h"
#include "MMLookAndFeel.h"

class Divider :
    public Component
{
public:
    Divider() = default;
    ~Divider() = default;

private:
    void paint(Graphics& g) override
    {
        g.setColour(findColour(MMLookAndFeel::ColourIds::outline));
        g.fillRect(0, 0, getWidth(), getHeight());
    }
};
