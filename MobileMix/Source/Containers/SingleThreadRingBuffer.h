/*
    Copyright (C) 2016 Jonathon Racz
*/

#pragma once

/** A lightweight ring buffer implementation indended to be written to and
    accessed from a single thread. The behavior is based on that of the Boost
    circular_buffer class.
*/
template <class Type, class Alloc = std::allocator<Type> >
class SingleThreadRingBuffer
{
public:
    /** Creates an empty ring buffer. */
    SingleThreadRingBuffer()
    {
        clear();
    }

    /** Creates an empty ring buffer with the given capacity. */
    SingleThreadRingBuffer(int capacity) :
        data(static_cast<size_t>(capacity))
    {
        clear();
    }

    /** Creates a ring buffer from another ring buffer. */
    SingleThreadRingBuffer(const SingleThreadRingBuffer& other) :
        data(other.data),
        startIndex(other.startIndex),
        endIndex(other.endIndex) {}

    /** Creates a ring buffer from another ring buffer. */
    SingleThreadRingBuffer& operator=(const SingleThreadRingBuffer& other)
    {
        data = other.data;
        startIndex = other.startIndex;
        endIndex = other.endIndex;
        return *this;
    }

    /** Creates a ring buffer from another ring buffer. */
    SingleThreadRingBuffer(SingleThreadRingBuffer&& other) :
        data(std::move(other.data)),
        startIndex(std::move(other.startIndex)),
        endIndex(std::move(other.endIndex)) {}

    /** Creates a ring buffer from another ring buffer. */
    SingleThreadRingBuffer& operator=(SingleThreadRingBuffer&& other)
    {
        data = std::move(other.data);
        startIndex = std::move(other.startIndex);
        endIndex = std::move(other.endIndex);
        return *this;
    }

    ~SingleThreadRingBuffer() {}

    /** Push a set of values into the front of the buffer in-order. Takes linear
        time based on the number of values being pushed.
     
        @param numToPush Convenience argument to allow pushing in multiple
        values at once.
    */
    void pushFront(const Type* value, int numToPush = 1)
    {
        if (numToPush > 0)
        {
            for (int i = 0; i < numToPush; ++i)
            {
                if (filledSize == data.size())
                {
                    endIndex = circularIndexToRealIndex(static_cast<int>(endIndex - 1));
                }
                else
                {
                    filledSize++;
                }

                startIndex = circularIndexToRealIndex(static_cast<int>(startIndex - 1));
                data[startIndex] = *value;
            }
        }
    }

    /** Push a set of values into the back of the buffer in-order. Takes linear
        time based on the number of values being pushed.

        @param numToPush Convenience argument to allow pushing in multiple
        values at once.
    */
    void pushBack(const Type* value, int numToPush = 1)
    {
        if (numToPush > 0)
        {
            for (int i = 0; i < numToPush; ++i)
            {
                if (filledSize == data.size())
                {
                    startIndex = circularIndexToRealIndex(static_cast<int>(startIndex + 1));
                }
                else
                {
                    filledSize++;
                }

                endIndex = circularIndexToRealIndex(static_cast<int>(endIndex + 1));
                data[endIndex] = *value;
            }
        }
    }

    /** Pop a certain number of values from the front of the buffer. If more
        pops are requested then there are available, it will pop as many as it
        can. Occurs in constant time.
    */
    void popFront(int numToPop = 1)
    {
        if (filledSize > 0 && numToPop > 0)
        {
            numToPop = std::min(numToPop, static_cast<int>(filledSize));
            filledSize -= static_cast<size_t>(numToPop);
            startIndex = circularIndexToRealIndex(static_cast<int>(startIndex) + numToPop);
        }
    }

    /** Pop a certain number of values from the back of the buffer. If more
        pops are requested then there are available, it will pop as many as it
        can. Occurs in constant time.
    */
    void popBack(int numToPop = 1)
    {
        if (filledSize > 0 && numToPop > 0)
        {
            numToPop = std::min(numToPop, static_cast<int>(filledSize));
            filledSize -= numToPop;
            endIndex = circularIndexToRealIndex(static_cast<int>(endIndex) - numToPop);
        }
    }

    /** Returns the filled size of the buffer, i.e. how many actual objects are
        inside of it.
    */
    int getSize() const { return static_cast<int>(filledSize); }

    /** Returns the entire capacity of the buffer. */
    int getCapacity() const { return static_cast<int>(data.size()); }

    /** Sets the capacity of the buffer; occurs in linear time depending on the
        number of items currently in the buffer.
    */
    void setCapacity(int capacity, bool ifShrinkingRemoveFromBack = true)
    {
        jassert(capacity >= 0);
        if (capacity == static_cast<int>(data.size())) return;
        linearize();

        if (capacity < static_cast<int>(data.size()))
        {
            if (!ifShrinkingRemoveFromBack)
            {
                size_t elementsToShrink = data.size() - static_cast<size_t>(capacity);
                std::rotate(data.begin(), std::next(data.begin(), static_cast<int>(elementsToShrink)), data.end());
            }

            filledSize = static_cast<size_t>(capacity);
            endIndex = filledSize;
        }

        data.resize(static_cast<size_t>(capacity));
    }

    /** Resets the buffer state. Occurs in constant time without any allocations
        or deallocations.
    */
    void clear() noexcept
    {
        startIndex = 0;
        endIndex = 0;
        filledSize = 0;
    }

    /** Returns whether the buffer is empty. */
    bool isEmpty() const { return filledSize == 0; }

    /** Returns whether the buffer is full. */
    bool isFull() const { return static_cast<int>(filledSize) == data.size(); };

    /** Rearranges the internal contents such that index 0 of the underlying
        data points to the beginning of the logical buffer and continues
        sequentially. Takes linear time.
    */
    void linearize()
    {
        if (startIndex != 0)
        {
            std::rotate(std::next(data.begin(), static_cast<int>(startIndex)), data.begin(), std::next(data.begin(), static_cast<int>(endIndex)));
            startIndex = 0;
            endIndex = filledSize;
        }
    }

    /** Returns whether the data is linearized, i.e. if the start of the
        circular data is at index zero of the underlying data.
    */
    bool isLinearized() const noexcept { return startIndex = 0; }

    /* Returns a copy of the first element of the ring buffer. */
    Type getFirst() const { return (*this)[0]; }

    /* Returns a copy of the last element of the ring buffer. */
    Type getLast() const { return (*this)[this->getSize() - 1]; }

    /* Returns a copy of the element at the given index of the ring buffer. */
    Type operator[](int index) const
    {
        size_t realIndex = circularIndexToRealIndex(index);
        jassert(isPositiveAndBelow(realIndex, data.size()));
        return data[realIndex];
    }
    
private:
    std::vector<Type, Alloc> data;
    size_t startIndex;
    size_t endIndex;
    size_t filledSize;

    forcedinline size_t circularIndexToRealIndex(int index) const
    {
        return static_cast<size_t>((static_cast<int>(startIndex) + index) % static_cast<int>(data.size()));
    }
    
};

#if UNIT_TESTS

class SingleThreadRingBufferTests :
    public UnitTest
{
public:
    SingleThreadRingBufferTests() :
        UnitTest("Single thread ring buffer"),
    dataSet(1024) {}

    void runTest() override
    {
        // Generate an arbitrarily large set of random floats.
        for (size_t i = 0; i < dataSet.size(); i++)
        {
            dataSet[i] = getRandom().nextFloat() * static_cast<float>(getRandom().nextInt());
        }

        SingleThreadRingBuffer<float> ringBuffer(512);
        ringBuffer.pushBack(dataSet.data(), 513);

        bool allSame = true;
        for (int i = 0; i < ringBuffer.getCapacity(); i++)
        {
            if (!(ringBuffer[i] == dataSet[static_cast<size_t>(i) + 1]))
            {
                allSame = false;
                break;
            }
        }

        expect(allSame == true);

        ringBuffer.popFront(2);
        for (int i = 0; i < ringBuffer.getCapacity(); i++)
        {
            if (!(ringBuffer[i] == dataSet[static_cast<size_t>(i) + 3]))
            {
                allSame = false;
                break;
            }
        }

        expect(allSame == true);
    }

private:
    std::vector<float> dataSet;
    
};

static SingleThreadRingBufferTests singleThreadRingBufferUnitTests;

#endif
