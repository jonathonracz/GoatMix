/*
  ==============================================================================

    BufferSizeAdaptor.h
    Created: 13 Sep 2017 12:05:17am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "../Containers/SingleThreadRingBuffer.h"
#include <unordered_set>
#include <vector>

class BufferSizeAdaptor
{
public:
    BufferSizeAdaptor() {}
    ~BufferSizeAdaptor() {}

    struct Listener
    {
        virtual ~Listener();
        virtual void processAtAdaptedBufferSize(float* samples, int numSamples) = 0;
    };

    void addListener(Listener* listener)
    {
        listeners.insert(listener);
    }

    void removeListener(Listener* listener)
    {
        listeners.erase(listener);
    }

    void setMaxBufferSize(int size)
    {
        buffer.resize(static_cast<size_t>(size), 0.0f);
        bufferWriteIdx = 0;
    }

    void setDesiredBufferSize(int size)
    {
        assert(size <= buffer.size());
        logicalBufferSize = static_cast<size_t>(size);
    }

    void process(float* samples, int numSamples)
    {
        size_t currentSampleIdx = 0;
        size_t totalSamples = numSamples;
        while (currentSampleIdx != totalSamples)
        {

        }
    }

private:
    void flushBuffer()
    {
        assert(bufferWriteIdx == buffer.size());
        for (Listener* listener : listeners)
            listener->processAtAdaptedBufferSize(&buffer.front(), static_cast<int>(bufferWriteIdx));
        bufferWriteIdx = 0;
    }

    std::unordered_set<Listener*> listeners;
    std::vector<float> buffer;
    size_t logicalBufferSize = 0;
    size_t bufferWriteIdx = 0;
};
