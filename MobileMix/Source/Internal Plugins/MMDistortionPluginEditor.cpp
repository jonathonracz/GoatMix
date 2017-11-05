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
    preview(processor.distortion.params),
    buttonLowPassEnable(BinaryData::lopass_svg, BinaryData::lopass_svgSize)
{
    attachDownsample = createSliderAttachment(processor.paramDownsample, sliderDownsample);
    attachBitDepth = createSliderAttachment(processor.paramBitDepth, sliderBitDepth);
    attachOverdrive = createSliderAttachment(processor.paramOverdrive, sliderOverdrive);
    attachGain = createSliderAttachment(processor.paramGain, sliderGain);
    attachLowPass = createSliderAttachment(processor.paramLowPass, sliderLowPass);
    attachLowPassEnable = createButtonAttachment(processor.paramLowPassEnable, buttonLowPassEnable);

    meterL.setSource(&processor.meterSource);
    meterL.setChannel(0);
    meterR.setSource(&processor.meterSource);
    meterR.setChannel(1);

    addAndMakeVisible(sliderDownsample);
    addAndMakeVisible(sliderBitDepth);
    addAndMakeVisible(sliderOverdrive);
    addAndMakeVisible(sliderGain);
    addAndMakeVisible(sliderLowPass);
    addAndMakeVisible(buttonLowPassEnable);
    
    addAndMakeVisible(preview);
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

    sliderGain.addListener(&preview);
    sliderBitDepth.addListener(&preview);
    sliderOverdrive.addListener(&preview);
    sliderDownsample.addListener(&preview);
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
    layout.items.add(FlexItem(sliderOverdrive).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderGain).withMargin(standardMargin).withFlex(1.0f));
    
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
    
    layout.items.add(FlexItem(preview).withMargin(standardMargin).withFlex(6.0f));
    
    FlexBox lpass;
    lpass.flexDirection = FlexBox::Direction::column;
    //lpass.items.add(FlexItem(sliderLowPass).withFlex(6.0f));
    lpass.items.add(FlexItem(buttonLowPassEnable).withMargin(FlexItem::Margin::Margin(15.0f, 0.0f, 0.0f, 0.0f)));
    layout.items.add(FlexItem(lpass).withMargin(standardMargin).withFlex(1.0f));
    
    layout.performLayout(getLocalBounds());
    
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDownsample);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderBitDepth);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderOverdrive);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderLowPass);
}
