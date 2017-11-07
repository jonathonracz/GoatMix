/*
  ==============================================================================

    MMReverbPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMReverbPluginEditor.h"

MMReverbPluginEditor::MMReverbPluginEditor(MMReverbPlugin& processor) :
    MobileMixPluginInstanceEditor(processor),
    buttonLowPass(BinaryData::lopass_svg, BinaryData::lopass_svgSize),
    buttonHighPass(BinaryData::hipass_svg, BinaryData::hipass_svgSize)
{
    attachRoomSize = createSliderAttachment(processor.paramRoomSize, sliderRoomSize);
    addAndMakeVisible(sliderRoomSize);
    
    attachDamping = createSliderAttachment(processor.paramDamping, sliderDamping);
    addAndMakeVisible(sliderDamping);
    
    attachWidth = createSliderAttachment(processor.paramWidth, sliderWidth);
    addAndMakeVisible(sliderWidth);
    
    attachHighPass = createSliderAttachment(processor.paramHighPass, sliderHighPass);
    addAndMakeVisible(sliderHighPass);
    
    attachLowPass = createSliderAttachment(processor.paramLowPass, sliderLowPass);
    addAndMakeVisible(sliderLowPass);
    
    attachDryWet = createSliderAttachment(processor.paramDryWet, sliderDryWet);
    addAndMakeVisible(sliderDryWet);
    
    addAndMakeVisible(graphReverb);
    
    //Need MMShapeButton constructors for high and low pass buttons
    attachHighPassEnable = createButtonAttachment(processor.paramHighPassEnable, buttonHighPass);
    addAndMakeVisible(buttonHighPass);
    attachLowPassEnable = createButtonAttachment(processor.paramLowPassEnable, buttonLowPass);
    addAndMakeVisible(buttonLowPass);

    tbFreeze.setClickingTogglesState(true);
    attachFreeze = createButtonAttachment(processor.paramFreeze, tbFreeze);
    addAndMakeVisible(tbFreeze);
}

MMReverbPluginEditor::~MMReverbPluginEditor()
{

}

void MMReverbPluginEditor::resized()
{
    FlexBox layout;
    
    float vertDynamicSpace = this->getHeight() * 0.02f;
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);
    
    FlexBox graphBox;
    graphBox.flexDirection = FlexBox::Direction::column;
    graphBox.items.add(FlexItem(graphReverb).withFlex(6.0f));
    
    layout.items.add(FlexItem(graphBox).withMargin(FlexItem::Margin::Margin(vertSpace, dynamicSpace, vertSpace, vertSpace)).withFlex(8.0f));
    
    FlexBox freezeBox;
    freezeBox.flexDirection = FlexBox::Direction::column;
    
    FlexBox freezeMeters;
    freezeMeters.flexDirection = FlexBox::Direction::row;
    freezeMeters.items.add(FlexItem(sliderRoomSize).withMargin(FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, 0.0f)).withFlex(1.0f));
    freezeMeters.items.add(FlexItem(sliderDamping).withMargin(FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, dynamicSpace)).withFlex(1.0f));
    freezeMeters.items.add(FlexItem(sliderWidth).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, 0.0f, dynamicSpace)).withFlex(1.0f));
    freezeBox.items.add(FlexItem(freezeMeters).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace, 0.0f)).withFlex(6.0f));
    
    freezeBox.items.add(FlexItem(tbFreeze).withFlex(1.0f));
    layout.items.add(FlexItem(freezeBox).withMargin(standardMargin).withFlex(3.5f));
    
    FlexBox highPass;
    highPass.flexDirection = FlexBox::Direction::column;
    highPass.items.add(FlexItem(sliderHighPass).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace, 0.0f)).withFlex(6.0f));
    Rectangle<int> hpBounds = buttonHighPass.getLocalBounds().reduced(buttonHighPass.getWidth() * 0.15f, buttonHighPass.getHeight() * 0.15f);
    buttonHighPass.setInternalShapeBounds(hpBounds);
    highPass.items.add(FlexItem(buttonHighPass).withFlex(1.0f));
    
    FlexBox lowPass;
    lowPass.flexDirection = FlexBox::Direction::column;
    lowPass.items.add(FlexItem(sliderLowPass).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace, 0.0f)).withFlex(6.0f));
    Rectangle<int> lpBounds = buttonLowPass.getLocalBounds().reduced(buttonLowPass.getWidth() * 0.15f, buttonLowPass.getHeight() * 0.15f);
    buttonLowPass.setInternalShapeBounds(lpBounds);
    lowPass.items.add(FlexItem(buttonLowPass).withFlex(1.0f));
    
    layout.items.add(FlexItem(highPass).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(lowPass).withMargin(standardMargin).withFlex(1.0f));
    
    layout.items.add(FlexItem(sliderDryWet).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace)).withFlex(1.0f));
    
    layout.performLayout(getLocalBounds());
    
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderRoomSize);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDamping);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderWidth);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderHighPass);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderLowPass);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDryWet);
}
