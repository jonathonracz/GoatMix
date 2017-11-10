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

    //MaxdBLabels here -- probably need to change the source channel
    leftdBLabel.setSource(&processor.meterSource, 0);
    addAndMakeVisible(leftdBLabel);
    
    maxdBLabel.setSource(&processor.meterSource, 0);
    addAndMakeVisible(maxdBLabel);
    
    rightdBLabel.setSource(&processor.meterSource, 0);
    addAndMakeVisible(rightdBLabel);
    
    //Meters here
    meterNegL.setSource(&processor.meter);
    meterPosL.setSource(&processor.meter);
    meterNegR.setSource(&processor.meter);
    meterPosR.setSource(&processor.meter);

    meterPosL.setMinGainDisplayValue(1.0f);
    meterPosL.setMaxGainDisplayValue(2.0f);
    meterPosR.setMinGainDisplayValue(1.0f);
    meterPosR.setMaxGainDisplayValue(2.0f);

    meterNegL.setChannel(0);
    meterPosL.setChannel(0);
    meterNegR.setChannel(1);
    meterPosR.setChannel(1);

    addAndMakeVisible(meterNegL);
    addAndMakeVisible(meterPosL);
    addAndMakeVisible(meterNegR);
    addAndMakeVisible(meterPosR);
    
    addAndMakeVisible(div);
    
    //meterLabels here
    meterLabels[0].setText("+6", dontSendNotification);
    meterLabels[0].setJustificationType(Justification::centredTop);
    meterLabels[1].setText("+3", dontSendNotification);
    meterLabels[1].setJustificationType(Justification::centredRight);
    meterLabels[2].setText("0", dontSendNotification);
    meterLabels[2].setJustificationType(Justification::centredBottom);
    meterLabels[3].setText("0", dontSendNotification);
    meterLabels[3].setJustificationType(Justification::centredTop);
    meterLabels[4].setText("-6", dontSendNotification);
    meterLabels[4].setJustificationType(Justification::centredRight);
    meterLabels[5].setText("-12", dontSendNotification);
    meterLabels[5].setJustificationType(Justification::centredRight);
    meterLabels[6].setText("-24", dontSendNotification);
    meterLabels[6].setJustificationType(Justification::centredRight);
    meterLabels[7].setText("-inf", dontSendNotification);
    meterLabels[7].setJustificationType(Justification::bottomRight);
    meterLabels[8].setText("0", dontSendNotification);
    meterLabels[8].setJustificationType(Justification::topLeft);
    meterLabels[9].setText("-6", dontSendNotification);
    meterLabels[9].setJustificationType(Justification::centredLeft);
    meterLabels[10].setText("-12", dontSendNotification);
    meterLabels[10].setJustificationType(Justification::centredLeft);
    meterLabels[11].setText("-24", dontSendNotification);
    meterLabels[11].setJustificationType(Justification::centredLeft);
    meterLabels[12].setText("-inf", dontSendNotification);
    meterLabels[12].setJustificationType(Justification::bottomLeft);
    meterLabels[13].setText("+6", dontSendNotification);
    meterLabels[13].setJustificationType(Justification::topLeft);
    meterLabels[14].setText("+3", dontSendNotification);
    meterLabels[14].setJustificationType(Justification::centredLeft);
    meterLabels[15].setText("0", dontSendNotification);
    meterLabels[15].setJustificationType(Justification::bottomLeft);
    
    for (int i = 0; i < 16; ++i) {
        meterLabels[i].setBorderSize(BorderSize<int>::BorderSize());
        addAndMakeVisible(meterLabels[i]);
    }
}

MMGainPluginEditor::~MMGainPluginEditor()
{
}

void MMGainPluginEditor::resized()
{
    //MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    FlexBox layout;
    
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    float vertDynamicSpace = this->getHeight() * 0.02f;
    float labelsFlex = 0.6f;
    float metersFlex = 0.75f;
    FlexItem::Margin labelsMargin = FlexItem::Margin::Margin(10.0f, 0.0f, 10.0f, 0.0f);
    FlexItem::Margin meterMargin = FlexItem::Margin::Margin(15.0f, 0.0f, 15.0f, 0.0f);
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);
    
    //Amplitude (left side)
    FlexBox ampBox;
    ampBox.flexDirection = FlexBox::Direction::column;
    
    FlexBox ampTop;
    ampTop.flexDirection = FlexBox::Direction::row;
    ampTop.items.add(FlexItem(leftdBLabel).withFlex(1.0f));
    ampTop.items.add(FlexItem(maxdBLabel).withFlex(1.0f));
    ampTop.items.add(FlexItem(rightdBLabel).withFlex(1.0f));
    ampBox.items.add(FlexItem(ampTop).withFlex(1.0f));
    
    FlexBox ampBottom;
    ampBottom.flexDirection = FlexBox::Direction::row;
    ampBottom.items.add(FlexItem(sliderGainL).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, 0.0f)).withFlex(1.0f));
    
    //L meters
    FlexBox lPosLabels;
    lPosLabels.flexDirection = FlexBox::Direction::column;
    lPosLabels.items.add(FlexItem(meterLabels[0]).withFlex(1.0f));
    lPosLabels.items.add(FlexItem(meterLabels[1]).withFlex(1.0f));
    lPosLabels.items.add(FlexItem(meterLabels[2]).withFlex(1.0f));
    ampBottom.items.add(FlexItem(lPosLabels).withMargin(labelsMargin).withFlex(labelsFlex));
    ampBottom.items.add(FlexItem(meterPosL).withMargin(meterMargin).withFlex(metersFlex));
    
    
    FlexBox lNegLabels;
    lNegLabels.flexDirection = FlexBox::Direction::column;
    lNegLabels.items.add(FlexItem(meterLabels[3]).withFlex(0.5f));
    lNegLabels.items.add(FlexItem(meterLabels[4]).withFlex(1.0f));
    lNegLabels.items.add(FlexItem(meterLabels[5]).withFlex(1.0f));
    lNegLabels.items.add(FlexItem(meterLabels[6]).withFlex(1.0f));
    lNegLabels.items.add(FlexItem(meterLabels[7]).withFlex(0.5f));
    ampBottom.items.add(FlexItem(lNegLabels).withMargin(FlexItem::Margin::Margin(10.0f, 0.0f, 10.0f, dynamicSpace)).withFlex(labelsFlex));
    ampBottom.items.add(FlexItem(meterNegL).withMargin(meterMargin).withFlex(metersFlex));
    
    ampBottom.items.add(FlexItem(sliderGain).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace * 2, 15.0f, dynamicSpace * 2)).withFlex(1.0f));
    
    //R meters
    ampBottom.items.add(FlexItem(meterNegR).withMargin(meterMargin).withFlex(metersFlex));
    FlexBox rNegLabels;
    rNegLabels.flexDirection = FlexBox::Direction::column;
    rNegLabels.items.add(FlexItem(meterLabels[8]).withFlex(0.5f));
    rNegLabels.items.add(FlexItem(meterLabels[9]).withFlex(1.0f));
    rNegLabels.items.add(FlexItem(meterLabels[10]).withFlex(1.0f));
    rNegLabels.items.add(FlexItem(meterLabels[11]).withFlex(1.0f));
    rNegLabels.items.add(FlexItem(meterLabels[12]).withFlex(0.5f));
    ampBottom.items.add(FlexItem(rNegLabels).withMargin(FlexItem::Margin::Margin(10.0f, dynamicSpace, 10.0f, 0.0f)).withFlex(labelsFlex));
    
    ampBottom.items.add(FlexItem(meterPosR).withMargin(meterMargin).withFlex(metersFlex));
    FlexBox rPosLabels;
    rPosLabels.flexDirection = FlexBox::Direction::column;
    rPosLabels.items.add(FlexItem(meterLabels[13]).withFlex(1.0f));
    rPosLabels.items.add(FlexItem(meterLabels[14]).withFlex(1.0f));
    rPosLabels.items.add(FlexItem(meterLabels[15]).withFlex(1.0f));
    ampBottom.items.add(FlexItem(rPosLabels).withMargin(labelsMargin).withFlex(labelsFlex));
    
    ampBottom.items.add(FlexItem(sliderGainR).withMargin(standardMargin).withFlex(1.0f));
    ampBox.items.add(FlexItem(ampBottom).withFlex(8.0f));
    
    layout.items.add(FlexItem(ampBox).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 0.0f, vertSpace)).withFlex(1.0f));
    
    layout.items.add(FlexItem(div).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));
    
    //Phase (right side)
    float phaseWidth = (this->getWidth() * 0.405f);
    float phaseHeight = this->getHeight() - vertSpace * 2;
    float phaseSliderWidth = phaseWidth / 6;
    
    FlexBox phaseBox;
    phaseBox.flexDirection = FlexBox::Direction::column;
    float panHeight = phaseHeight * (1.0f/6.0f);
    phaseBox.items.add(FlexItem(sliderPan).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace * 2, 0.0f)).withHeight(panHeight));

    FlexBox phaseBottom;
    phaseBottom.flexDirection = FlexBox::Direction::row;
    
    FlexBox lPhase;
    lPhase.flexDirection = FlexBox::Direction::column;
    lPhase.items.add(FlexItem(sliderPhaseDelayL).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace * 2, 0.0f)).withWidth(phaseSliderWidth).withFlex(5.0f));
    lPhase.items.add(FlexItem(buttonPhaseInvertL).withWidth(phaseSliderWidth).withFlex(1.0f));
    phaseBottom.items.add(FlexItem(lPhase).withFlex(1.0f));
    
    //Goniometer
    float gonVertSpace = phaseHeight - panHeight;
    float gonHorSpace = phaseWidth - phaseSliderWidth * 2;
    float calcWidth = gonHorSpace;
    float calcHeight = gonVertSpace;
    if (calcWidth > calcHeight) {
        calcWidth = calcHeight;
    } else {
        calcHeight = calcWidth;
    }
    float horMargin = (gonHorSpace - calcWidth) / 2;
    float vertMargin = (gonVertSpace - calcHeight) / 2;
    if (horMargin < dynamicSpace * 2) {
        horMargin = dynamicSpace * 2;
        calcWidth = gonHorSpace - horMargin * 2;
        calcHeight = calcWidth;
    }
    else if (vertMargin < vertDynamicSpace * 2) {
        vertMargin = vertDynamicSpace * 2;
        calcHeight = gonVertSpace - vertMargin * 2;
        calcWidth = calcHeight;
    }
    FlexItem gonItem = FlexItem(goniometer).withWidth(calcWidth).withHeight(calcHeight);
    gonItem.margin = FlexItem::Margin::Margin(vertMargin, horMargin, vertMargin, horMargin);
    phaseBottom.items.add(gonItem);
    
    FlexBox rPhase;
    rPhase.flexDirection = FlexBox::Direction::column;
    rPhase.items.add(FlexItem(sliderPhaseDelayR).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace * 2, 0.0f)).withWidth(phaseSliderWidth).withFlex(5.0f));
    rPhase.items.add(FlexItem(buttonPhaseInvertR).withWidth(phaseSliderWidth).withFlex(1.0f));
    phaseBottom.items.add(FlexItem(rPhase).withFlex(1.0f));
    phaseBox.items.add(FlexItem(phaseBottom).withFlex(6.0f));
    
    layout.items.add(FlexItem(phaseBox).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace * 2)).withWidth(phaseWidth));

    layout.performLayout(getLocalBounds());

    Rectangle<int> shapeBounds = buttonPhaseInvertL.getLocalBounds().reduced(buttonPhaseInvertL.getWidth() * 0.15f, buttonPhaseInvertL.getHeight() * 0.15f);
    buttonPhaseInvertL.setInternalShapeBounds(shapeBounds);
    buttonPhaseInvertR.setInternalShapeBounds(shapeBounds);

    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGainL);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGainR);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderPhaseDelayL);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderPhaseDelayR);
}
