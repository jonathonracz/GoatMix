/*
  ==============================================================================

    MaxdBLabel.h
    Created: 30 Oct 2017 1:30:38am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MMLookAndFeel.h"

class MaxdBLabel :
    public Label,
    public Timer
{
public:
    MaxdBLabel()
    {
        setJustificationType(Justification::centred);
        startTimerHz(5);
    }

    void setSource(FFAU::LevelMeterSource* _source, int _channel)
    {
        jassert(_source);
        source = _source;
        channel = _channel;
    }

private:
    void mouseUp(const MouseEvent& e) override
    {
        setText(Decibels::toString(0.0f), NotificationType::dontSendNotification);
        source->clearAllMaxNums();
        Label::mouseUp(e);
    }

    void paint(Graphics& g) override
    {
        if (source && source->getMaxOverallLevel(channel) > 1.0f)
            g.fillAll(findColour(MMLookAndFeel::ColourIds::meterClip));
        Label::paint(g);
    }

    void timerCallback() override
    {
        if (source)
            setText(Decibels::toString(source->getMaxOverallLevel(channel)), NotificationType::dontSendNotification);
        else
            setText("NO SOURCE", NotificationType::dontSendNotification);
        repaint();
    }

    WeakReference<FFAU::LevelMeterSource> source;
    int channel = 0;
};
