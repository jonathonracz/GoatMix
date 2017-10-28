/*
  ==============================================================================

    MMGainPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMGainPluginEditor.h"

MMGainPluginEditor::MMGainPluginEditor(MMGainPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    gainSliderAttachment = createSliderAttachment(processor.paramGain->paramID, gainSlider);
    addAndMakeVisible(gainSlider);

    testMeter.setMeterSource(&processor.meterSource);
    addAndMakeVisible(testMeter);
    testMeter2.setMaxGainDisplayValue(1.1f);
    testMeter2.setSource(&processor.meterSource);
    addAndMakeVisible(testMeter2);
}

MMGainPluginEditor::~MMGainPluginEditor()
{

}

void MMGainPluginEditor::paint(Graphics& g)
{
    g.setColour(Colours::green);
    g.fillAll();
    g.setColour(Colours::red);
    g.drawRect(10, 10, getWidth() - 20, getHeight() - 20);
}

void MMGainPluginEditor::resized()
{
    gainSlider.setSize(getWidth() / 10, getHeight() - 20);
    MobileMixPluginInstanceEditor::setVerticalRotatedWithBounds(&gainSlider, gainSlider.getBounds());

    testMeter.setBounds(getLocalBounds().getWidth() / 2.0f, getLocalBounds().getHeight() / 2.0f, getLocalBounds().getWidth() / 2.0f, getLocalBounds().getHeight() / 2.0f);
    testMeter2.setBounds(testMeter.getBounds());
}
