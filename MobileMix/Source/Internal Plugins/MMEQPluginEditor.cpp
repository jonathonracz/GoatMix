/*
  ==============================================================================

    MMEQPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMEQPluginEditor.h"
#include "MMEQPlugin.h"

MMEQPluginEditor::MMEQPluginEditor(MMEQPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    for (size_t i = 0; i < eqs.size(); ++i)
    {
        EQControls* eqControl = &eqs[i];
        MMEQPlugin::EQParams* eqParam = &processor.eqParams[i];

        eqControl->boxType.addItem("Bypass", 1);
        eqControl->boxType.addItem("Low Pass", 2);
        eqControl->boxType.addItem("Low Shelf", 3);
        eqControl->boxType.addItem("Peak", 4);
        eqControl->boxType.addItem("High Shelf", 5);
        eqControl->boxType.addItem("High Pass", 6);
        eqControl->boxType.setSelectedId(-1);
        eqControl->boxType.setJustificationType(Justification::Flags::centred);

        eqControl->attachFrequency = createSliderAttachment(eqParam->paramFrequency, eqControl->sliderFrequency);
        eqControl->attachGain = createSliderAttachment(eqParam->paramGain, eqControl->sliderGain);
        eqControl->attachQ = createSliderAttachment(eqParam->paramQ, eqControl->sliderQ);
        eqControl->attachType = createComboBoxAttachment(eqParam->paramType, eqControl->boxType);

        eqControl->text.setText(String(i), dontSendNotification);
        eqControl->text.setBorderSize(BorderSize<int>::BorderSize());
        eqControl->text.setJustificationType(Justification::centred);

        addAndMakeVisible(eqControl->sliderFrequency);
        addAndMakeVisible(eqControl->sliderGain);
        addAndMakeVisible(eqControl->sliderQ);
        addAndMakeVisible(eqControl->boxType);
        addAndMakeVisible(eqControl->text);
    }

    for (size_t i = 0; i < dividers.size(); ++i)
        addAndMakeVisible(dividers[i]);
}

MMEQPluginEditor::~MMEQPluginEditor()
{
}

void MMEQPluginEditor::resized()
{
    FlexBox layout;

    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin rightMargin = FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, 0.0f);
    FlexItem::Margin leftMargin = FlexItem::Margin::Margin(0.0f, vertSpace, 0.0f, dynamicSpace);
    FlexItem::Margin rightLeftMargin = FlexItem::Margin::Margin(0.0f, dynamicSpace, 0.0f, dynamicSpace);
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 10.0f, dynamicSpace);

    // 0
    FlexBox fb0;
    fb0.flexDirection = FlexBox::Direction::row;
    fb0.items.add(FlexItem(eqs[0].sliderFrequency).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 10.0f, vertSpace)).withFlex(1.0f));
    fb0.items.add(FlexItem(eqs[0].sliderGain).withMargin(standardMargin).withFlex(1.0f));
    fb0.items.add(FlexItem(eqs[0].sliderQ).withMargin(standardMargin).withFlex(1.0f));
    FlexBox cb0;
    cb0.flexDirection = FlexBox::Direction::column;
    cb0.items.add(FlexItem(fb0).withFlex(6.0f));
    FlexBox rb0;
    rb0.flexDirection = FlexBox::Direction::row;
    rb0.items.add(FlexItem(eqs[0].boxType).withFlex(2.0f));
    rb0.items.add(FlexItem(eqs[0].text).withFlex(1.0f));
    cb0.items.add(FlexItem(rb0).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(cb0).withMargin(rightMargin).withFlex(1.0f));
    layout.items.add(FlexItem(dividers[0]).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));

    // 1
    FlexBox fb1;
    fb1.flexDirection = FlexBox::Direction::row;
    fb1.items.add(FlexItem(eqs[1].sliderFrequency).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 10.0f, vertSpace)).withFlex(1.0f));
    fb1.items.add(FlexItem(eqs[1].sliderGain).withMargin(standardMargin).withFlex(1.0f));
    fb1.items.add(FlexItem(eqs[1].sliderQ).withMargin(standardMargin).withFlex(1.0f));
    FlexBox cb1;
    cb1.flexDirection = FlexBox::Direction::column;
    cb1.items.add(FlexItem(fb1).withFlex(6.0f));
    FlexBox rb1;
    rb1.flexDirection = FlexBox::Direction::row;
    rb1.items.add(FlexItem(eqs[1].boxType).withFlex(2.0f));
    rb1.items.add(FlexItem(eqs[1].text).withFlex(1.0f));
    cb1.items.add(FlexItem(rb1).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(cb1).withMargin(rightMargin).withFlex(1.0f));
    layout.items.add(FlexItem(dividers[1]).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));

    // 2
    FlexBox fb2;
    fb2.flexDirection = FlexBox::Direction::row;
    fb2.items.add(FlexItem(eqs[2].sliderFrequency).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 10.0f, vertSpace)).withFlex(1.0f));
    fb2.items.add(FlexItem(eqs[2].sliderGain).withMargin(standardMargin).withFlex(1.0f));
    fb2.items.add(FlexItem(eqs[2].sliderQ).withMargin(standardMargin).withFlex(1.0f));
    FlexBox cb2;
    cb2.flexDirection = FlexBox::Direction::column;
    cb2.items.add(FlexItem(fb2).withFlex(6.0f));
    FlexBox rb2;
    rb2.flexDirection = FlexBox::Direction::row;
    rb2.items.add(FlexItem(eqs[2].boxType).withFlex(2.0f));
    rb2.items.add(FlexItem(eqs[2].text).withFlex(1.0f));
    cb2.items.add(FlexItem(rb2).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(cb2).withMargin(rightMargin).withFlex(1.0f));
    layout.items.add(FlexItem(dividers[2]).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));

    // 3
    FlexBox fb3;
    fb3.flexDirection = FlexBox::Direction::row;
    fb3.items.add(FlexItem(eqs[3].sliderFrequency).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 10.0f, vertSpace)).withFlex(1.0f));
    fb3.items.add(FlexItem(eqs[3].sliderGain).withMargin(standardMargin).withFlex(1.0f));
    fb3.items.add(FlexItem(eqs[3].sliderQ).withMargin(standardMargin).withFlex(1.0f));
    FlexBox cb3;
    cb3.flexDirection = FlexBox::Direction::column;
    cb3.items.add(FlexItem(fb3).withFlex(6.0f));
    FlexBox rb3;
    rb3.flexDirection = FlexBox::Direction::row;
    rb3.items.add(FlexItem(eqs[3].boxType).withFlex(2.0f));
    rb3.items.add(FlexItem(eqs[3].text).withFlex(1.0f));
    cb3.items.add(FlexItem(rb3).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, vertSpace)).withFlex(1.0f));
    layout.items.add(FlexItem(cb3).withMargin(rightMargin).withFlex(1.0f));

    // Final
    layout.performLayout(getLocalBounds());

    // Rotate everything
    for (size_t i = 0; i < eqs.size(); ++i)
    {
        EQControls* eq = &eqs[i];
        MobileMixPluginInstanceEditor::setVerticalRotated(&eq->sliderFrequency);
        MobileMixPluginInstanceEditor::setVerticalRotated(&eq->sliderGain);
        MobileMixPluginInstanceEditor::setVerticalRotated(&eq->sliderQ);
    }
}
