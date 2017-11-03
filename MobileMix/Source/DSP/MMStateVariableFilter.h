/*
  ==============================================================================

    MMStateVariableFilter.h
    Created: 3 Nov 2017 2:29:28am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

// Do a simple alias to get all the template syntax out of the way...
using MMStateVariableFilter = dsp::ProcessorDuplicator<
    dsp::StateVariableFilter::Filter<float>,
    dsp::StateVariableFilter::Parameters<float>>;
