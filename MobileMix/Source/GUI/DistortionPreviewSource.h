/*
  ==============================================================================

    DistortionPreviewSource.h
    Created: 30 Oct 2017 5:22:58pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class DistortionPreviewSource :
    dsp::ProcessorBase
{
public:
    DistortionPreviewSource() {}
    ~DistortionPreviewSource() {}

    void prepare(const dsp::ProcessSpec& spec) override;
    void process(const dsp::ProcessContextReplacing<float>& context) override;
    void reset() override;

private:
    std::vector<float> samples;
};
