/*
  ==============================================================================

    RefCountedAudioBuffer.h
    Created: 26 Nov 2017 12:12:10pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/* Note that operations on this object are NOT thread safe! */
template<typename FloatType>
struct RefCountedAudioBuffer :
    public AudioBuffer<FloatType>,
    public ReferenceCountedObject
{
    using Ptr = ReferenceCountedObjectPtr<RefCountedAudioBuffer>;
};
