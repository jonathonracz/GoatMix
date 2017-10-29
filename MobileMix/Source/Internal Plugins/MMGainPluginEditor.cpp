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
}

MMGainPluginEditor::~MMGainPluginEditor()
{
}

void MMGainPluginEditor::resized()
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    FlexBox layout;

    layout.items.add(lf.getFlexItem(*this, gainSlider));

    layout.performLayout(getLocalBounds());

    //gainSlider.setSize(getWidth() / 10, getHeight() - 20);
    MobileMixPluginInstanceEditor::setVerticalRotatedWithBounds(&gainSlider, gainSlider.getBounds());
}
