/*
  ==============================================================================

    GMCompressorPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMCompressorPluginEditor.h"

GMCompressorPluginEditor::GMCompressorPluginEditor(GMCompressorPlugin& processor) :
    GoatMixPluginInstanceEditor(processor),
    preview(processor.compressor.params, processor.meter)
{
    attachAttack = createSliderAttachment(processor.paramAttack, sliderAttack);
    attachRelease = createSliderAttachment(processor.paramRelease, sliderRelease);
    attachRatio = createSliderAttachment(processor.paramRatio, sliderRatio);
    attachThreshold = createSliderAttachment(processor.paramThreshold, sliderThreshold);
    attachMakeupGain = createSliderAttachment(processor.paramMakeupGain, sliderMakeupGain);
    attachDryWet = createSliderAttachment(processor.paramDryWet, sliderDryWet);

    sliderAttack.setTooltip(UIStrings::Compressor::attack);
    sliderRelease.setTooltip(UIStrings::Compressor::release);
    sliderRatio.setTooltip(UIStrings::Compressor::ratio);
    sliderThreshold.setTooltip(UIStrings::Compressor::threshold);
    sliderMakeupGain.setTooltip(UIStrings::Shared::gain);
    sliderDryWet.setTooltip(UIStrings::Shared::dryWet);
    preview.setTooltip(UIStrings::Compressor::preview);

    addAndMakeVisible(sliderAttack);
    addAndMakeVisible(sliderRelease);
    addAndMakeVisible(sliderRatio);
    addAndMakeVisible(sliderThreshold);
    addAndMakeVisible(sliderMakeupGain);
    addAndMakeVisible(sliderDryWet);

    addAndMakeVisible(preview);
    addAndMakeVisible(meterLGainReduc);
    addAndMakeVisible(meterRGainReduc);

    textLGainReduc.setText("L", dontSendNotification);
    textLGainReduc.setBorderSize(BorderSize<int>::BorderSize());
    textLGainReduc.setJustificationType(Justification::centred);

    textRGainReduc.setText("R", dontSendNotification);
    textRGainReduc.setBorderSize(BorderSize<int>::BorderSize());
    textRGainReduc.setJustificationType(Justification::centred);

    textGR.setText("GR", dontSendNotification);
    textGR.setBorderSize(BorderSize<int>::BorderSize());
    textGR.setJustificationType(Justification::centred);

    addAndMakeVisible(textGR);
    addAndMakeVisible(textLGainReduc);
    addAndMakeVisible(textRGainReduc);
}

GMCompressorPluginEditor::~GMCompressorPluginEditor()
{

}

void GMCompressorPluginEditor::resized()
{
    FlexBox layout;

    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);

    layout.items.add(FlexItem(sliderAttack).withMargin(FlexItem::Margin::Margin(vertSpace, dynamicSpace, vertSpace, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(sliderRelease).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderRatio).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderThreshold).withMargin(standardMargin).withFlex(1.0f));

    FlexItem graphItem = FlexItem(preview).withMargin(standardMargin).withWidth(this->getWidth() * 0.4f).withHeight(this->getHeight() - vertSpace * 2).withMargin(standardMargin);
    if (graphItem.width > graphItem.height) {
        graphItem.width = graphItem.height;
    } else {
        graphItem.height = graphItem.width;
        float topBottomSpace = (this->getHeight() - vertSpace * 2 - graphItem.height) / 2;
        graphItem.margin = FlexItem::Margin::Margin(vertSpace + topBottomSpace, dynamicSpace, vertSpace + topBottomSpace, dynamicSpace);
    }
    layout.items.add(graphItem);

    /*
    FlexBox meterBox;
    meterBox.flexDirection = FlexBox::Direction::column;
    meterBox.items.add(FlexItem(textGR).withFlex(1.0f));

    FlexBox meters;
    meters.flexDirection = FlexBox::Direction::row;

    FlexBox lMeter;
    lMeter.flexDirection = FlexBox::Direction::column;
    lMeter.items.add(FlexItem(textLGainReduc).withFlex(1.0f));
    lMeter.items.add(FlexItem(meterLGainReduc).withFlex(10.0f));

    FlexBox rMeter;
    rMeter.flexDirection = FlexBox::Direction::column;
    rMeter.items.add(FlexItem(textRGainReduc).withFlex(1.0f));
    rMeter.items.add(FlexItem(meterRGainReduc).withFlex(10.0f));

    meters.items.add(FlexItem(lMeter).withMargin(FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, 0.0f)).withFlex(1.0f));
    meters.items.add(FlexItem(rMeter).withFlex(1.0f));
    meterBox.items.add(FlexItem(meters).withFlex(10.0f));
    layout.items.add(FlexItem(meterBox).withMargin(standardMargin).withFlex(1.0f));
     */

    layout.items.add(FlexItem(sliderMakeupGain).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderDryWet).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace)).withFlex(1.0f));

    layout.performLayout(getLocalBounds());

    GoatMixPluginInstanceEditor::setVerticalRotated(&sliderAttack);
    GoatMixPluginInstanceEditor::setVerticalRotated(&sliderRelease);
    GoatMixPluginInstanceEditor::setVerticalRotated(&sliderRatio);
    GoatMixPluginInstanceEditor::setVerticalRotated(&sliderThreshold);
    GoatMixPluginInstanceEditor::setVerticalRotated(&meterLGainReduc);
    GoatMixPluginInstanceEditor::setVerticalRotated(&meterRGainReduc);
    GoatMixPluginInstanceEditor::setVerticalRotated(&sliderMakeupGain);
    GoatMixPluginInstanceEditor::setVerticalRotated(&sliderDryWet);
}
