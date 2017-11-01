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
    RingBuffer(int logicalCapacity)
    {
        setLogicalCapacity(logicalCapacity);
    }

    void clear()
    {
        head = tail = 0;
    }

    void fill(const Type& value = Type())
    {
        while (numElements() < (logicalCapacity()))
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

    void setLogicalCapacity(int num)
    {
        data.resize(num + 1);
    }

    int logicalCapacity() const
    {
        return data.size() - 1;
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

    Type* getPointerToFirstHalf()
    {
        return data.getRawDataPointer() + head;
    }

    int getSizeOfFirstHalf() const
    {
        if (head <= tail)
            return tail - head;
        else
            return static_cast<int>(data.size()) - head;
    }

    Type* getPointerToSecondHalf()
    {
        if (head <= tail || tail == 0)
            return nullptr;
        else
            return data.getRawDataPointer();
    }

    int getSizeOfSecondHalf() const
    {
        if (head <= tail || tail == 0)
            return 0;
        else
            return tail;
    }

    Type operator[](int index) const
    {
        jassert(index < numElements());
        return data[(head + index) % numElements()];
    }

    void setData(const Type* src, int num)
    {
        jassert(num < capacity());
        if (std::is_trivially_copyable<Type>::value)
        {
            head = 0;
            tail = num;
            memcpy(data.getRawDataPointer(), src, num * sizeof(Type));
        }
        else
        {
            clear();
            for (int i = 0; i < num; ++i)
            {
                push(src[i]);
            }
        }
    }

private:
    Array<Type> data;
    int head = 0;
    int tail = 0;
};
