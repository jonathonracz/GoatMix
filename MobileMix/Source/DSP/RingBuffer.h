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
        while (numElements() < (getLogicalCapacity()))
            push(value);
    }

    int getCapacity() const
    {
        return data.size();
    }

    void setCapacity(int num)
    {
        data.resize(num);
    }

    int getLogicalCapacity() const
    {
        return data.size() - 1;
    }

    void setLogicalCapacity(int num)
    {
        data.resize(num + 1);
    }

    int numElements() const
    {
        if (head < tail)
            return tail - head;
        else if (head > tail)
            return (getCapacity() - head) + tail;
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
        tail = (tail + 1) % getCapacity();
        if (head == tail)
            head = (head + 1) % getCapacity();
    }

    Type pop()
    {
        jassert(head != tail);
        Type ret = data[head];
        head = (head + 1) % getCapacity();
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
        jassert(num < getCapacity());
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
    int capacity = 0;
    int head = 0;
    int tail = 0;
};
