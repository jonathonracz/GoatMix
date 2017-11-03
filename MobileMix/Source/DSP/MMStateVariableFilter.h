/*
  ==============================================================================

    MMStateVariableFilter.h
    Created: 3 Nov 2017 2:29:28am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using MMStateVariableFilter = dsp::ProcessorDuplicator<
    dsp::StateVariableFilter::Filter<float>,
    dsp::StateVariableFilter::Parameters<float>>;
