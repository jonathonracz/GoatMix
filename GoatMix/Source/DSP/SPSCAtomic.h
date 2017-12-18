/*
  ==============================================================================

    SPSCAtomic.h
    Created: 1 Dec 2017 9:18:20pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <atomic>

template<typename Type>
struct SPSCAtomic
{
    SPSCAtomic() noexcept = default;

    SPSCAtomic(Type initialValue) noexcept : value(initialValue) {}

    ~SPSCAtomic() noexcept {}

    inline Type get() const noexcept
    {
        return value.load(std::memory_order_acquire);
    }

    inline operator Type() const noexcept
    {
        return get();
    }

    inline SPSCAtomic<Type>& operator=(const Type& newValue) noexcept
    {
        value.store(newValue, std::memory_order_release);
        return *this;
    }

    std::atomic<Type> value;
};
