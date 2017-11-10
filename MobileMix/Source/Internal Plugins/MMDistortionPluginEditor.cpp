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

    sliderDownsample.addListener(this);
    sliderBitDepth.addListener(this);
    sliderOverdrive.addListener(this);
    sliderGain.addListener(this);

    addAndMakeVisible(sliderDownsample);
    addAndMakeVisible(sliderBitDepth);
    addAndMakeVisible(sliderOverdrive);
    addAndMakeVisible(sliderGain);
    addAndMakeVisible(sliderLowPass);
    addAndMakeVisible(buttonLowPassEnable);

    addAndMakeVisible(preview);
    regeneratePreview();
    addAndMakeVisible(meterL);
    addAndMakeVisible(meterR);

    labelL.setText("L", dontSendNotification);
    labelL.setBorderSize(BorderSize<int>::BorderSize());
    labelL.setJustificationType(Justification::centred);

    labelR.setText("R", dontSendNotification);
    labelR.setBorderSize(BorderSize<int>::BorderSize());
    labelR.setJustificationType(Justification::centred);

    labelDB.setText("dB", dontSendNotification);
    labelDB.setBorderSize(BorderSize<int>::BorderSize());
    labelDB.setJustificationType(Justification::centred);

    addAndMakeVisible(labelDB);
    addAndMakeVisible(labelL);
    addAndMakeVisible(labelR);
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

    FlexBox meters;
    meters.flexDirection = FlexBox::Direction::column;
    meters.items.add(FlexItem(labelDB).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, 0.0f, 0.0f)).withFlex(0.75f));

    FlexBox meterRow;
    meterRow.flexDirection = FlexBox::Direction::row;

    FlexBox lmeter;
    lmeter.flexDirection = FlexBox::Direction::column;
    lmeter.items.add(FlexItem(labelL).withFlex(0.75f));
    lmeter.items.add(FlexItem(meterL).withFlex(6.0f));
    meterRow.items.add(FlexItem(lmeter).withMargin(FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, dynamicSpace)).withFlex(1.0f));

    FlexBox rmeter;
    rmeter.flexDirection = FlexBox::Direction::column;
    rmeter.items.add(FlexItem(labelR).withFlex(0.75f));
    rmeter.items.add(FlexItem(meterR).withFlex(6.0f));
    meterRow.items.add(FlexItem(rmeter).withMargin(FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, dynamicSpace)).withFlex(1.0f));
    meters.items.add(FlexItem(meterRow).withFlex(6.0f));
    layout.items.add(FlexItem(meters).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, 0.0f)).withFlex(1.5f));

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
    regeneratePreview();
}

void MMDistortionPluginEditor::regeneratePreview()
{
    preview.getParams()->samplesToRepeat = static_cast<size_t>(sliderDownsample.getValue());
    preview.getParams()->bitDepth = static_cast<size_t>(sliderBitDepth.getValue());
    preview.getParams()->overdriveGainUp = static_cast<float>(sliderOverdrive.getValue());
    preview.getParams()->overdriveGainDown = static_cast<float>(sliderGain.getValue());
    preview.repaint();
}
