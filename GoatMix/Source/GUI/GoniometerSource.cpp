/*
  ==============================================================================

    GoniometerSource.cpp
    Created: 29 Oct 2017 10:12:36pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GoniometerSource.h"

GoniometerSource::GoniometerSource() :
    pathCoordsBuffer(1024)
{
}

GoniometerSource::~GoniometerSource()
{
}

void GoniometerSource::process(const AudioBuffer<float>& buffer)
{
    // For the sake of time, hard coding this to require two channels.
    jassert(buffer.getNumChannels() >= 2);
    const float** readPointer = buffer.getArrayOfReadPointers();
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        Point<float> newPoint(readPointer[1][sample], readPointer[0][sample]);
        if (!pathCoordsBuffer.try_enqueue(newPoint))
            break;
    }
}

void GoniometerSource::clearBuffer()
{
    size_t numPopped = 0;
    while ((numPopped < pathCoordsBuffer.size_approx()) && pathCoordsBuffer.pop())
        numPopped++;
}

bool GoniometerSource::getNextPoint(Point<float>& dest)
{
    return pathCoordsBuffer.try_dequeue(dest);
}
