//
//  Divider.h
//  MobileMix
//
//  Created by Jeran Norman on 11/3/17.
//

#ifndef Divider_h
#define Divider_h

#include "JuceHeader.h"
#include "MMLookAndFeel.h"

class Divider :
public Component
{
public:
    Divider()
    {
        setOpaque(true);
    }

private:
    
    void paint(Graphics& g) override
    {
        g.setColour(Colours::black);
        g.drawLine(0, 0, getWidth(), getHeight(), 2);
    }
};


#endif /* Divider_h */
