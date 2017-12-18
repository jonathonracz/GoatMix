/*
  ==============================================================================

    GoniometerSource.h
    Created: 29 Oct 2017 10:12:36pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../External/readerwriterqueue/readerwriterqueue.h"

class GoniometerSource
{
public:
    GoniometerSource();
    ~GoniometerSource();

    // Call from the audio thread
    void process(const AudioBuffer<float>& buffer);

    // Call from the message thread
    void clearBuffer();
    bool getNextPoint(Point<float>& dest);

private:
    moodycamel::ReaderWriterQueue<Point<float>> pathCoordsBuffer;

    JUCE_DECLARE_WEAK_REFERENCEABLE(GoniometerSource);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GoniometerSource)
};
