/*
  ==============================================================================

    Math.h
    Created: 11 Sep 2017 11:10:19pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <cassert>

namespace math
{

template<typename NumericType>
constexpr int numSIMDOps(int size)
{
    return size / juce::dsp::SIMDRegister<NumericType>::size();
}

template<typename NumericType>
constexpr int numPostSIMDOps(int size)
{
    return size % juce::dsp::SIMDRegister<NumericType>::size();
}

template<typename NumericType>
constexpr int postSIMDStartIndex(int size)
{
    return size - numPostSIMDOps<NumericType>(size);
}

/** Shift the base frequency of an FFT to the center. */
void fftshift(float* samples, int numSamples)
{
    assert(!(numSamples % 2));
    int halfwayPoint = numSamples / 2;
    float swap;

    // TODO: SIMD-accelerate this.
    for (int i = 0; i < halfwayPoint; ++i)
    {
        swap = samples[i];
        samples[i] = samples[halfwayPoint + i];
        samples[halfwayPoint + i] = swap;
    }
}

/** Hanning window, zero-terminated on both ends. */
void hanningz(float* samples, int numSamples)
{
    juce::FloatVectorOperations::fill(samples, 2.0f * juce::MathConstants<float>::pi / numSamples, numSamples);
    // TODO: SIMD-accelerate this with some sort of cosine approximation.
    for (int i = 0; i < numSamples; ++i)
        samples[i] = 1.0f - std::cosf(samples[i] * i);
    juce::FloatVectorOperations::multiply(samples, 0.5f, numSamples);
}

}
