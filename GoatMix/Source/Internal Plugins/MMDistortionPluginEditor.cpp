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
    preview(processor.distortion.params, *this),
    buttonLowPassEnable(BinaryData::lopass_svg, BinaryData::lopass_svgSize)
{
    attachDownsample = createSliderAttachment(processor.paramDownsample, sliderDownsample);
    attachBitDepth = createSliderAttachment(processor.paramBitDepth, sliderBitDepth);
    attachOverdrive = createSliderAttachment(processor.paramOverdrive, sliderOverdrive);
    attachGain = createSliderAttachment(processor.paramGain, sliderGain);
    attachLowPass = createSliderAttachment(processor.paramLowPass, sliderLowPass);
    attachLowPassEnable = createButtonAttachment(processor.paramLowPassEnable, buttonLowPassEnable);

    meter.setSource(&processor.meterSource);

    sliderDownsample.addListener(this);
    sliderBitDepth.addListener(this);
    sliderOverdrive.addListener(this);
    sliderGain.addListener(this);

    sliderDownsample.setTooltip(UIStrings::Distortion::downsample);
    sliderBitDepth.setTooltip(UIStrings::Distortion::bitDepth);
    sliderOverdrive.setTooltip(UIStrings::Distortion::overdrive);
    sliderGain.setTooltip(UIStrings::Shared::gain);
    preview.setTooltip(UIStrings::Distortion::preview);
    sliderLowPass.setTooltip(UIStrings::Shared::filterControl);
    buttonLowPassEnable.setTooltip(UIStrings::Shared::filterEnable);

    addAndMakeVisible(sliderDownsample);
    addAndMakeVisible(sliderBitDepth);
    addAndMakeVisible(sliderOverdrive);
    addAndMakeVisible(sliderGain);
    addAndMakeVisible(sliderLowPass);
    addAndMakeVisible(buttonLowPassEnable);

    addAndMakeVisible(preview);
    sendSynchronousChangeMessage();
    addAndMakeVisible(meter);
}

MMDistortionPluginEditor::~MMDistortionPluginEditor()
{
}

void MMDistortionPluginEditor::resized()
{
    FlexBox layout;

    float vertDynamicSpace = this->getHeight() * 0.02f;
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);

    layout.items.add(FlexItem(sliderDownsample).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(sliderBitDepth).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderOverdrive).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderGain).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(meter).withMargin(standardMargin).withFlex(1.0f));

    FlexItem prevItem = FlexItem(preview).withMargin(standardMargin).withWidth(this->getWidth() * 0.35f).withHeight(this->getHeight() - vertSpace * 2).withMargin(standardMargin);
    if (prevItem.width > prevItem.height) {
        prevItem.width = prevItem.height;
    } else {
        prevItem.height = prevItem.width;
        float topBottomSpace = (this->getHeight() - vertSpace * 2 - prevItem.height) / 2;
        prevItem.margin = FlexItem::Margin::Margin(vertSpace + topBottomSpace, dynamicSpace, vertSpace + topBottomSpace, dynamicSpace);
    }
    layout.items.add(prevItem);

    FlexBox lpass;
    lpass.flexDirection = FlexBox::Direction::column;
    lpass.items.add(FlexItem(sliderLowPass).withFlex(6.0f));
    lpass.items.add(FlexItem(buttonLowPassEnable).withMargin(FlexItem::Margin::Margin(vertDynamicSpace, 0.0f, 0.0f, 0.0f)).withFlex(1.0f));
    layout.items.add(FlexItem(lpass).withMargin(standardMargin).withFlex(1.0f));

    layout.performLayout(getLocalBounds());

    Rectangle<int> lpBounds = buttonLowPassEnable.getLocalBounds().reduced(buttonLowPassEnable.getWidth() * 0.15f, buttonLowPassEnable.getHeight() * 0.15f);
    buttonLowPassEnable.setInternalShapeBounds(lpBounds);

    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDownsample);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderBitDepth);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderOverdrive);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderLowPass);
}

void MMDistortionPluginEditor::sliderValueChanged(Slider* slider)
{
    sendSynchronousChangeMessage();
}
