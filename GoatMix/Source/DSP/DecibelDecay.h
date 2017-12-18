/*
  ==============================================================================

    DecibelDecay.h
    Created: 28 Nov 2017 4:37:39pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class DecibelDecay
{
public:
    struct DecaydBFactors
    {
        static constexpr float ppmType1 = 20.0f / 1.7f;
        static constexpr float ppmType2 = 24.0f / 2.8f;
    };

    DecibelDecay() = default;

    DecibelDecay(float _dBPerSecondDecay, float _linearSnapToZero) :
        dBPerSecondDecay(_dBPerSecondDecay), linearSnapToZero(_linearSnapToZero)
    {
    }

    ~DecibelDecay() {}

    float getdBPerSecondDecay() const noexcept { return dBPerSecondDecay; }
    void setdBPerSecondDecay(float _dBPerSecondDecay) noexcept { dBPerSecondDecay = _dBPerSecondDecay; }

    float getLinearSnapToZero() const noexcept { return linearSnapToZero; }
    void setLinearSnapToZero(float _linearSnapToZero) noexcept { linearSnapToZero = _linearSnapToZero; dBSnapToZero = Decibels::gainToDecibels(_linearSnapToZero); }

    float getdBSnapToZero() const noexcept { return dBSnapToZero; }
    void setdBSnapToZero(float _dBSnapToZero) noexcept { dBSnapToZero = _dBSnapToZero; linearSnapToZero = Decibels::decibelsToGain(_dBSnapToZero); }

    inline float decayLinear(float linearValue, float deltaSeconds)
    {
        return decayLinear(linearValue, deltaSeconds, dBPerSecondDecay, linearSnapToZero);
    }

    inline float decaydB(float dBValue, float deltaSeconds)
    {
        return decaydB(dBValue, deltaSeconds, dBPerSecondDecay, dBSnapToZero);
    }

    static float decayLinear(float linearValue, float deltaSeconds, float dBPerSecondDecay, float linearSnapToZero = 0.1f) noexcept
    {
        float linearDecay = Decibels::decibelsToGain(deltaSeconds * dBPerSecondDecay);
        linearValue -= linearDecay;
        return (linearValue > linearSnapToZero) ? linearValue : 0.0f;
    }

    static float decaydB(float dBValue, float deltaSeconds, float dBPerSecondDecay, float dBSnapToZero = -100.0f) noexcept
    {
        dBValue -= dBPerSecondDecay * deltaSeconds;
        return (dBValue > dBSnapToZero) ? dBValue : 0.0f;
    }

private:
    float dBPerSecondDecay = DecaydBFactors::ppmType1;
    float linearSnapToZero = 0.1f;
    float dBSnapToZero = Decibels::gainToDecibels(linearSnapToZero);

};
