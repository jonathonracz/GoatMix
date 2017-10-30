/*
  ==============================================================================

    MMGainPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMGainPluginEditor.h"

MMGainPluginEditor::MMGainPluginEditor(MMGainPlugin& processor) :
    MobileMixPluginInstanceEditor(processor),
    buttonPhaseInvertL(BinaryData::phaseinvert_svg, BinaryData::phaseinvert_svgSize),
    buttonPhaseInvertR(BinaryData::phaseinvert_svg, BinaryData::phaseinvert_svgSize)
{
    attachGain = createSliderAttachment(processor.paramGain, sliderGain);
    attachGainL = createSliderAttachment(processor.paramGainL, sliderGainL);
    attachGainR = createSliderAttachment(processor.paramGainR, sliderGainR);
    attachPan = createSliderAttachment(processor.paramPan, sliderPan);
    attachPhaseDelayL = createSliderAttachment(processor.paramPhaseDelayL, sliderPhaseDelayL);
    attachPhaseDelayR = createSliderAttachment(processor.paramPhaseDelayR, sliderPhaseDelayR);
    attachPhaseInvertL = createButtonAttachment(processor.paramPhaseInvertL, buttonPhaseInvertL);
    attachPhaseInvertR = createButtonAttachment(processor.paramPhaseInvertR, buttonPhaseInvertR);

    addAndMakeVisible(sliderGain);
    addAndMakeVisible(sliderGainL);
    addAndMakeVisible(sliderGainR);
    addAndMakeVisible(sliderPan);
    addAndMakeVisible(sliderPhaseDelayL);
    addAndMakeVisible(sliderPhaseDelayR);
    addAndMakeVisible(buttonPhaseInvertL);
    addAndMakeVisible(buttonPhaseInvertR);

    goniometer.setSource(&processor.goniometerSource);
    addAndMakeVisible(goniometer);
}

MMGainPluginEditor::~MMGainPluginEditor()
{
}

void MMGainPluginEditor::resized()
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    goniometer.setBounds(0, 0, 200, 200);
    FlexBox layout;

    layout.items.add(lf.getFlexItem(*this, sliderGainL));
    layout.items.add(lf.getFlexItem(*this, sliderGain));
    layout.items.add(lf.getFlexItem(*this, sliderGainR));

    FlexBox phaseL;
    phaseL.flexDirection = FlexBox::Direction::column;

    FlexBox phaseR;
    phaseR.flexDirection = FlexBox::Direction::column;

    FlexBox phaseRow;


    layout.performLayout(getLocalBounds());

    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGainL);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGainR);
}
