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

    maxdBLabel.setSource(&processor.meterSource, 0);
    addAndMakeVisible(maxdBLabel);
    
    smlMeterL.setSource(&processor.meterSource);
    smlMeterR.setSource(&processor.meterSource);
    addAndMakeVisible(smlMeterL);
    addAndMakeVisible(smlMeterR);
    
    addAndMakeVisible(div);
}

MMGainPluginEditor::~MMGainPluginEditor()
{
}

void MMGainPluginEditor::resized()
{
    //MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    //goniometer.setBounds(0, 0, 200, 200);
    //maxdBLabel.setBounds(0, 0, 100, 100);
    FlexBox layout;
    
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);
    
    //Amplitude (left side)
    FlexBox ampBox;
    ampBox.flexDirection = FlexBox::Direction::column;
    
    FlexBox ampTop;
    ampTop.flexDirection = FlexBox::Direction::row;
    ampTop.items.add(FlexItem(maxdBLabel).withFlex(1.0f));
    ampBox.items.add(FlexItem(ampTop).withFlex(1.0f));
    
    FlexBox ampBottom;
    ampBottom.flexDirection = FlexBox::Direction::row;
    ampBottom.items.add(FlexItem(sliderGainL).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, 0.0f)).withFlex(1.0f));
    ampBottom.items.add(FlexItem(smlMeterL).withMargin(standardMargin).withFlex(0.75f));
    ampBottom.items.add(FlexItem(sliderGain).withMargin(standardMargin).withFlex(1.0f));
    ampBottom.items.add(FlexItem(smlMeterR).withMargin(standardMargin).withFlex(0.75f));
    ampBottom.items.add(FlexItem(sliderGainR).withMargin(standardMargin).withFlex(1.0f));
    ampBox.items.add(FlexItem(ampBottom).withFlex(8.0f));
    
    layout.items.add(FlexItem(ampBox).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace * 1.5f, 0.0f, vertSpace)).withFlex(1.0f));
    
    layout.items.add(FlexItem(div).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));
    
    //Phase (right side)
    FlexBox phaseBox;
    phaseBox.flexDirection = FlexBox::Direction::column;
    phaseBox.items.add(FlexItem(sliderPan).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, 15.0f, 0.0f)).withFlex(1.0f));

    FlexBox phaseBottom;
    phaseBottom.flexDirection = FlexBox::Direction::row;
    
    FlexBox lPhase;
    lPhase.flexDirection = FlexBox::Direction::column;
    lPhase.items.add(FlexItem(sliderPhaseDelayL).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, 15.0f, 0.0f)).withFlex(5.0f));
    lPhase.items.add(FlexItem(buttonPhaseInvertL).withFlex(1.0f));
    phaseBottom.items.add(FlexItem(lPhase).withFlex(1.0f));
    
    phaseBottom.items.add(FlexItem(goniometer).withMargin(FlexItem::Margin::Margin(0.0f, dynamicSpace * 2, 0.0f, dynamicSpace * 2)).withFlex(6.0f));
    
    FlexBox rPhase;
    rPhase.flexDirection = FlexBox::Direction::column;
    rPhase.items.add(FlexItem(sliderPhaseDelayR).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, 15.0f, 0.0f)).withFlex(5.0f));
    rPhase.items.add(FlexItem(buttonPhaseInvertR).withFlex(1.0f));
    phaseBottom.items.add(FlexItem(rPhase).withFlex(1.0f));
    phaseBox.items.add(FlexItem(phaseBottom).withFlex(6.0f));
    
    layout.items.add(FlexItem(phaseBox).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace * 2.5f)).withFlex((1.3f)));

    layout.performLayout(getLocalBounds());

    Rectangle<int> shapeBounds = buttonPhaseInvertL.getLocalBounds().reduced(buttonPhaseInvertL.getWidth() * 0.15f, buttonPhaseInvertL.getHeight() * 0.15f);
    buttonPhaseInvertL.setInternalShapeBounds(shapeBounds);
    buttonPhaseInvertR.setInternalShapeBounds(shapeBounds);

    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGainL);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGainR);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderPhaseDelayL);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderPhaseDelayR);
    //MobileMixPluginInstanceEditor::setVerticalRotated(&smlMeterL);
    //MobileMixPluginInstanceEditor::setVerticalRotated(&smlMeterR);
}
