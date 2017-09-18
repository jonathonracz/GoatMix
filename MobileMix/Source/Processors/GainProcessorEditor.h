/*
  ==============================================================================

    GainProcessorEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SubProcessorEditor.h"
#include "GainProcessor.h"

class GainProcessorEditor :
    public SubProcessorEditor
{
public:
    GainProcessorEditor(SubProcessor& processor);
    ~GainProcessorEditor();

protected:
    void paint(Graphics& g) override;

private:
    void parameterChanged(const String &parameterID, float newValue) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainProcessorEditor)
};
