/*
  ==============================================================================

    MMDistortionPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMDistortionPluginEditor.h"

MMDistortionPluginEditor::MMDistortionPluginEditor(MMDistortionPlugin& processor) :
    MobileMixPluginInstanceEditor(processor),
    preview(processor.distortion.params)
{
    attachDownsample = createSliderAttachment(processor.paramDownsample, sliderDownsample);
    addAndMakeVisible(sliderDownsample);
    
    attachBitDepth = createSliderAttachment(processor.paramBitDepth, sliderBitDepth);
    addAndMakeVisible(sliderBitDepth);
    
    attachTone = createSliderAttachment(processor.paramTone, sliderTone);
    addAndMakeVisible(sliderTone);
    
    attachDrive = createSliderAttachment(processor.paramDrive, sliderDrive);
    addAndMakeVisible(sliderDrive);
    
    attachClipThreshold1 = createSliderAttachment(processor.paramClipThreshold1, sliderClipThreshold1);
    addAndMakeVisible(sliderClipThreshold1);
    
    attachLowPass = createSliderAttachment(processor.paramLowPass, sliderLowPass);
    addAndMakeVisible(sliderLowPass);
    
    attachClipThreshold2 = createSliderAttachment(processor.paramClipThreshold2, sliderClipThreshold2);
    addAndMakeVisible(sliderClipThreshold2);
    
    addAndMakeVisible(graphDistortion);
    addAndMakeVisible(meterL);
    addAndMakeVisible(meterR);
    
    labelL.setText("L", dontSendNotification);
    labelL.setBorderSize(BorderSize<int>::BorderSize());
    labelL.setJustificationType(Justification::centred);
    
    labelR.setText("R", dontSendNotification);
    labelR.setBorderSize(BorderSize<int>::BorderSize());
    labelR.setJustificationType(Justification::centred);
    
    addAndMakeVisible(labelL);
    addAndMakeVisible(labelR);
}

MMDistortionPluginEditor::~MMDistortionPluginEditor()
{

}

void MMDistortionPluginEditor::resized()
{
    FlexBox layout;
    
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);
    
    layout.items.add(FlexItem(sliderDownsample).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(sliderBitDepth).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderTone).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderDrive).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderClipThreshold1).withMargin(standardMargin).withFlex(1.0f));
    
    FlexBox lmeter;
    lmeter.flexDirection = FlexBox::Direction::column;
    lmeter.items.add(FlexItem(labelL).withFlex(1.0f));
    lmeter.items.add(FlexItem(meterL).withFlex(6.0f));
    layout.items.add(FlexItem(lmeter).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace)).withFlex(0.5f));
    
    FlexBox rmeter;
    rmeter.flexDirection = FlexBox::Direction::column;
    rmeter.items.add(FlexItem(labelR).withFlex(1.0f));
    rmeter.items.add(FlexItem(meterR).withFlex(6.0f));
    layout.items.add(FlexItem(rmeter).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, 0.0f)).withFlex(0.5f));
    
    layout.items.add(FlexItem(graphDistortion).withMargin(standardMargin).withFlex(6.0f));
    
    FlexBox lpass;
    lpass.flexDirection = FlexBox::Direction::column;
    lpass.items.add(FlexItem(sliderLowPass).withFlex(6.0f));
    //lpass.items.add(FlexItem(buttonLowPass)withMargin(FlexItem::Margin::Margin(15.0f, 0.0f, 0.0f, 0.0f)));
    layout.items.add(FlexItem(lpass).withMargin(standardMargin).withFlex(1.0f));
    
    layout.items.add(FlexItem(sliderClipThreshold2).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace)));
    
    layout.performLayout(getLocalBounds());
    
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDownsample);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderBitDepth);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderTone);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDrive);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderClipThreshold1);
    MobileMixPluginInstanceEditor::setVerticalRotated(&meterL);
    MobileMixPluginInstanceEditor::setVerticalRotated(&meterR);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderLowPass);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderClipThreshold2);
}
