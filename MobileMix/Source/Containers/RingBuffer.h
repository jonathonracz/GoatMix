/*
  ==============================================================================

    RingBuffer.h
    Created: 29 Oct 2017 11:09:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template<class Type>
class RingBuffer
{
public:
    RingBuffer() {}
    RingBuffer(int capacity)
    {
        data.resize(capacity);
    }

    void clear()
    {
        head = tail = 0;
    }

    void fill(const Type& value = Type())
    {
        while (numElements() < (capacity() - 1))
            push(value);
    }

    void setCapacity(int num)
    {
        data.resize(num);
    }

    int capacity() const
    {
        return data.size();
    }

    int numElements() const
    {
        if (head < tail)
            return tail - head;
        else if (head > tail)
            return (capacity() - head) + tail;
        else
            return 0;
    }

    bool isEmpty() const
    {
        return numElements() == 0;
    }

    void push(const Type& src)
    {
        data.setUnchecked(tail, src);
        tail = (tail + 1) % capacity();
        if (head == tail)
            head = (head + 1) % capacity();
    }

    Type pop()
    {
        jassert(head != tail);
        Type ret = data[head];
        head = (head + 1) % capacity();
        return ret;
    }

    Type& getReference(int index) const
    {
        jassert(index < numElements());
        return data.getReference((head + index) % numElements());
    }

    Type operator[](int index) const
    {
        jassert(index < numElements());
        return data[(head + index) % numElements()];
    }

private:
    Array<Type> data;
    int head = 0;
    int tail = 0;
};
