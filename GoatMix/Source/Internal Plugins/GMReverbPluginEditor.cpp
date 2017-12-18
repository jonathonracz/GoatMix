/*
  ==============================================================================

    GMReverbPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMReverbPluginEditor.h"

GMReverbPluginEditor::GMReverbPluginEditor(GMReverbPlugin& processor) :
    GMPluginInstanceEditor(processor),
    preview(processor.state, processor.paramRoomSize->paramID, processor.paramDamping->paramID, processor.paramWidth->paramID, processor.paramFreeze->paramID),
    buttonHighPass(BinaryData::hipass_svg, BinaryData::hipass_svgSize),
    buttonLowPass(BinaryData::lopass_svg, BinaryData::lopass_svgSize),
    tbFreeze("Freeze")
{
    attachRoomSize = createSliderAttachment(processor.paramRoomSize, sliderRoomSize);
    attachDamping = createSliderAttachment(processor.paramDamping, sliderDamping);
    attachWidth = createSliderAttachment(processor.paramWidth, sliderWidth);
    attachHighPass = createSliderAttachment(processor.paramHighPass, sliderHighPass);
    attachLowPass = createSliderAttachment(processor.paramLowPass, sliderLowPass);
    attachDryWet = createSliderAttachment(processor.paramDryWet, sliderDryWet);

    attachHighPassEnable = createButtonAttachment(processor.paramHighPassEnable, buttonHighPass);
    attachLowPassEnable = createButtonAttachment(processor.paramLowPassEnable, buttonLowPass);
    attachFreeze = createButtonAttachment(processor.paramFreeze, tbFreeze);

    tbFreeze.setClickingTogglesState(true);

    sliderRoomSize.addListener(this);
    sliderDamping.addListener(this);
    sliderWidth.addListener(this);
    tbFreeze.addListener(this);

    sliderRoomSize.setTooltip(UIStrings::Reverb::roomSize);
    sliderDamping.setTooltip(UIStrings::Reverb::damping);
    sliderWidth.setTooltip(UIStrings::Reverb::width);
    sliderHighPass.setTooltip(UIStrings::Shared::filterControl);
    sliderLowPass.setTooltip(UIStrings::Shared::filterControl);
    sliderDryWet.setTooltip(UIStrings::Shared::dryWet);
    preview.setTooltip(UIStrings::Reverb::preview);
    buttonHighPass.setTooltip(UIStrings::Shared::filterEnable);
    buttonLowPass.setTooltip(UIStrings::Shared::filterEnable);
    tbFreeze.setTooltip(UIStrings::Reverb::freeze);

    addAndMakeVisible(sliderRoomSize);
    addAndMakeVisible(sliderDamping);
    addAndMakeVisible(sliderWidth);
    addAndMakeVisible(sliderHighPass);
    addAndMakeVisible(sliderLowPass);
    addAndMakeVisible(sliderDryWet);
    addAndMakeVisible(preview);
    addAndMakeVisible(buttonHighPass);
    addAndMakeVisible(buttonLowPass);
    addAndMakeVisible(tbFreeze);

    sendSynchronousChangeMessage();
}

GMReverbPluginEditor::~GMReverbPluginEditor()
{
}

void GMReverbPluginEditor::resized()
{
    FlexBox layout;

    float vertDynamicSpace = this->getHeight() * 0.02f;
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);

    FlexBox graphBox;
    graphBox.flexDirection = FlexBox::Direction::column;
    graphBox.items.add(FlexItem(preview).withFlex(6.0f));

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
    highPass.items.add(FlexItem(buttonHighPass).withFlex(1.0f));

    FlexBox lowPass;
    lowPass.flexDirection = FlexBox::Direction::column;
    lowPass.items.add(FlexItem(sliderLowPass).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertDynamicSpace, 0.0f)).withFlex(6.0f));
    lowPass.items.add(FlexItem(buttonLowPass).withFlex(1.0f));

    layout.items.add(FlexItem(highPass).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(lowPass).withMargin(standardMargin).withFlex(1.0f));

    layout.items.add(FlexItem(sliderDryWet).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace)).withFlex(1.0f));

    layout.performLayout(getLocalBounds());

    Rectangle<int> hpBounds = buttonHighPass.getLocalBounds().reduced(buttonHighPass.getWidth() * 0.15f, buttonHighPass.getHeight() * 0.15f);
    buttonHighPass.setInternalShapeBounds(hpBounds);
    Rectangle<int> lpBounds = buttonLowPass.getLocalBounds().reduced(buttonLowPass.getWidth() * 0.15f, buttonLowPass.getHeight() * 0.15f);
    buttonLowPass.setInternalShapeBounds(lpBounds);

    GMPluginInstanceEditor::setVerticalRotated(&sliderRoomSize);
    GMPluginInstanceEditor::setVerticalRotated(&sliderDamping);
    GMPluginInstanceEditor::setVerticalRotated(&sliderWidth);
    GMPluginInstanceEditor::setVerticalRotated(&sliderHighPass);
    GMPluginInstanceEditor::setVerticalRotated(&sliderLowPass);
    GMPluginInstanceEditor::setVerticalRotated(&sliderDryWet);
}

void GMReverbPluginEditor::sliderValueChanged(Slider* slider)
{
    sendSynchronousChangeMessage();
}

void GMReverbPluginEditor::buttonStateChanged(Button* button)
{
    sendSynchronousChangeMessage();
}
