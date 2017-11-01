/*
  ==============================================================================

    RingBuffer.h
    Created: 29 Oct 2017 11:09:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

template<class Type>
class RingBuffer
{
public:
    RingBuffer() {}
    RingBuffer(int logicalAllocatedCapacity) noexcept
    {
        setAllocatedLogicalCapacity(logicalAllocatedCapacity);
        setLogicalCapacity(logicalAllocatedCapacity);
    }

    RingBuffer(const RingBuffer& other)
    {
        setCapacity(other.capacity);
        for (int i = 0; i < other.getNumElements(); ++i)
            push(other.getReference(i));
    }

    RingBuffer(RingBuffer&& other) = default;

    ~RingBuffer() noexcept {}

    void clear() noexcept
    {
        head = tail = 0;
    }

    void fill(const Type& value = Type()) noexcept
    {
        while (getNumElements() < (getLogicalCapacity()))
            push(value);
    }

    int getCapacity() const noexcept
    {
        return capacity;
    }

    void setCapacity(int num, bool doNotReallocate = false) noexcept
    {
        if (allocSize < num)
        {
            jassert(!doNotReallocate); // You would have had to reallocate here!
            setAllocatedCapacity(num);
        }
        linearize();
        capacity = num;
    }

    int getLogicalCapacity() const noexcept
    {
        return getCapacity() - 1;
    }

    void setLogicalCapacity(int num, bool doNotReallocate = false) noexcept
    {
        setCapacity(num + 1, doNotReallocate);
    }

    int getAllocatedCapacity() const noexcept
    {
        return allocSize;
    }

    void setAllocatedCapacity(int num) noexcept
    {
        if (num)
        {
            data.realloc(num);
            for (int i = allocSize; i < num; ++i)
                new (data + i) Type();
        }
        else
        {
            data.free();
        }

        allocSize = num;
    }

    int getAllocatedLogicalCapacity() const noexcept
    {
        return getAllocatedCapacity() - 1;
    }

    void setAllocatedLogicalCapacity(int num) noexcept
    {
        setAllocatedCapacity(num + 1);
    }

    void deallocateToCurrentCapacity() noexcept
    {
        if (allocSize > capacity)
            setAllocatedCapacity(capacity);
    }

    int getNumElements() const noexcept
    {
        if (head < tail)
            return tail - head;
        else if (head > tail)
            return (getCapacity() - head) + tail;
        else
            return 0;
    }

    bool isEmpty() const noexcept
    {
        return getNumElements() == 0;
    }

    void push(const Type& src) noexcept
    {
        data[tail] = src;
        tail = (tail + 1) % getCapacity();
        if (head == tail)
            head = (head + 1) % getCapacity();
    }

    Type pop() noexcept
    {
        jassert(head != tail);
        Type ret = data[head];
        head = (head + 1) % getCapacity();
        return ret;
    }

    Type& getReference(int index) const noexcept
    {
        jassert(index < getNumElements());
        return data[(head + index) % getNumElements()];
    }

    Type* getPointerToFirstHalf() noexcept
    {
        return data.getData() + head;
    }

    int getSizeOfFirstHalf() const noexcept
    {
        if (head <= tail)
            return tail - head;
        else
            return capacity - head;
    }

    Type* getPointerToSecondHalf() noexcept
    {
        if (head <= tail || tail == 0)
            return nullptr;
        else
            return data.getData();
    }

    int getSizeOfSecondHalf() const noexcept
    {
        if (head <= tail || tail == 0)
            return 0;
        else
            return tail;
    }

    Type operator[](int index) const noexcept
    {
        jassert(index < getNumElements());
        return data[(head + index) % getNumElements()];
    }

    void setData(const Type* src, int num) noexcept
    {
        jassert(num < getCapacity());
        if (std::is_trivially_copyable<Type>::value)
        {
            head = 0;
            tail = num;
            memcpy(data.getData(), src, num * sizeof(Type));
        }
        else
        {
            clear();
            for (int i = 0; i < num; ++i)
                push(src[i]);
        }
    }

    void linearize() noexcept
    {
        head = 0;
        tail = getNumElements();
        std::rotate(data.getData(), data.getData() + head, data.getData() + capacity);
    }

private:
    HeapBlock<Type> data;
    int allocSize = 0;
    int capacity = 0;
    int head = 0;
    int tail = 0;
};
