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
        MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());
        g.setColour(Colours::black);
        g.drawLine(0, 0, getWidth(), getHeight(), lf.borderThickness);
    }
};
