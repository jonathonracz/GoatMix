/*
  ==============================================================================

    MMEQPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMEQPluginEditor.h"

MMEQPluginEditor::MMEQPluginEditor(MMEQPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    attachFrequency1 = createSliderAttachment(processor.paramFrequency1, sliderFrequency1);
    addAndMakeVisible(sliderFrequency1);
    attachGain1 = createSliderAttachment(processor.paramGain1, sliderGain1);
    addAndMakeVisible(sliderGain1);
    attachQ1 = createSliderAttachment(processor.paramQ1, sliderQ1);
    addAndMakeVisible(sliderQ1);
    
    attachFrequency2 = createSliderAttachment(processor.paramFrequency2, sliderFrequency2);
    addAndMakeVisible(sliderFrequency2);
    attachGain2 = createSliderAttachment(processor.paramGain2, sliderGain2);
    addAndMakeVisible(sliderGain2);
    attachQ2 = createSliderAttachment(processor.paramQ2, sliderQ2);
    addAndMakeVisible(sliderQ2);
    
    attachFrequency3 = createSliderAttachment(processor.paramFrequency3, sliderFrequency3);
    addAndMakeVisible(sliderFrequency3);
    attachGain3 = createSliderAttachment(processor.paramGain3, sliderGain3);
    addAndMakeVisible(sliderGain3);
    attachQ3 = createSliderAttachment(processor.paramQ3, sliderQ3);
    addAndMakeVisible(sliderQ3);
    
    attachFrequency4 = createSliderAttachment(processor.paramFrequency4, sliderFrequency4);
    addAndMakeVisible(sliderFrequency4);
    attachGain4 = createSliderAttachment(processor.paramGain4, sliderGain4);
    addAndMakeVisible(sliderGain4);
    attachQ4 = createSliderAttachment(processor.paramQ4, sliderQ4);
    addAndMakeVisible(sliderQ4);
    
    boxType1.addItem("Low Pass", 1);
    boxType1.addItem("Low Shelf", 2);
    boxType1.addItem("High Shelf", 3);
    boxType1.addItem("High Pass", 4);
    
    boxType2.addItem("Low Pass", 1);
    boxType2.addItem("Low Shelf", 2);
    boxType2.addItem("High Shelf", 3);
    boxType2.addItem("High Pass", 4);
    
    boxType3.addItem("Low Pass", 1);
    boxType3.addItem("Low Shelf", 2);
    boxType3.addItem("High Shelf", 3);
    boxType3.addItem("High Pass", 4);
    
    boxType4.addItem("Low Pass", 1);
    boxType4.addItem("Low Shelf", 2);
    boxType4.addItem("High Shelf", 3);
    boxType4.addItem("High Pass", 4);
    
    boxType1.setText("Type", dontSendNotification);
    boxType2.setText("Type", dontSendNotification);
    boxType3.setText("Type", dontSendNotification);
    boxType4.setText("Type", dontSendNotification);
    
    addAndMakeVisible(boxType1);
    addAndMakeVisible(boxType2);
    addAndMakeVisible(boxType3);
    addAndMakeVisible(boxType4);
    
    text1.setText("1", dontSendNotification);
    text1.setBorderSize(BorderSize<int>::BorderSize());
    text1.setJustificationType(Justification::centred);
    
    text2.setText("2", dontSendNotification);
    text2.setBorderSize(BorderSize<int>::BorderSize());
    text2.setJustificationType(Justification::centred);
    
    text3.setText("3", dontSendNotification);
    text3.setBorderSize(BorderSize<int>::BorderSize());
    text3.setJustificationType(Justification::centred);
    
    text4.setText("4", dontSendNotification);
    text4.setBorderSize(BorderSize<int>::BorderSize());
    text4.setJustificationType(Justification::centred);
    
    addAndMakeVisible(text1);
    addAndMakeVisible(text2);
    addAndMakeVisible(text3);
    addAndMakeVisible(text4);
    
    addAndMakeVisible(div1);
    addAndMakeVisible(div2);
    addAndMakeVisible(div3);
    
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
    
    //Box 1
    FlexBox fb1;
    fb1.flexDirection = FlexBox::Direction::row;
    
    fb1.items.add(FlexItem(sliderFrequency1).withMargin(FlexItem::Margin::Margin(15.0f, dynamicSpace, 10.0f, vertSpace)).withFlex(1.0f));
    fb1.items.add(FlexItem(sliderGain1).withMargin(standardMargin).withFlex(1.0f));
    fb1.items.add(FlexItem(sliderQ1).withMargin(standardMargin).withFlex(1.0f));
    
    FlexBox cb1;
    cb1.flexDirection = FlexBox::Direction::column;
    cb1.items.add(FlexItem(fb1).withFlex(6.0f));
    
    FlexBox rb1;
    rb1.flexDirection = FlexBox::Direction::row;
    rb1.items.add(FlexItem(boxType1).withFlex(2.0f));
    rb1.items.add(FlexItem(text1).withFlex(1.0f));
    
    cb1.items.add(FlexItem(rb1).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, vertSpace)).withFlex(1.0f));
    
    layout.items.add(FlexItem(cb1).withMargin(rightMargin).withFlex(1.0f));
    layout.items.add(FlexItem(div1).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));
    
    //Box 2
    FlexBox fb2;
    fb2.flexDirection = FlexBox::Direction::row;
    
    fb2.items.add(FlexItem(sliderFrequency2).withMargin(standardMargin).withFlex(1.0f));
    fb2.items.add(FlexItem(sliderGain2).withMargin(standardMargin).withFlex(1.0f));
    fb2.items.add(FlexItem(sliderQ2).withMargin(standardMargin).withFlex(1.0f));
    
    FlexBox cb2;
    cb2.flexDirection = FlexBox::Direction::column;
    cb2.items.add(FlexItem(fb2).withFlex(6.0f));
    
    FlexBox rb2;
    rb2.flexDirection = FlexBox::Direction::row;
    rb2.items.add(FlexItem(boxType2).withFlex(2.0f));
    rb2.items.add(FlexItem(text2).withFlex(1.0f));
    
    cb2.items.add(FlexItem(rb2).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, dynamicSpace)).withFlex(1.0f));
    
    layout.items.add(FlexItem(cb2).withMargin(rightLeftMargin).withFlex(1.0f));
    layout.items.add(FlexItem(div2).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));
    
    //Box 3
    FlexBox fb3;
    fb3.flexDirection = FlexBox::Direction::row;
    
    fb3.items.add(FlexItem(sliderFrequency3).withMargin(standardMargin).withFlex(1.0f));
    fb3.items.add(FlexItem(sliderGain3).withMargin(standardMargin).withFlex(1.0f));
    fb3.items.add(FlexItem(sliderQ3).withMargin(standardMargin).withFlex(1.0f));
    
    FlexBox cb3;
    cb3.flexDirection = FlexBox::Direction::column;
    cb3.items.add(FlexItem(fb3).withFlex(6.0f));
    
    FlexBox rb3;
    rb3.flexDirection = FlexBox::Direction::row;
    rb3.items.add(FlexItem(boxType3).withFlex(2.0f));
    rb3.items.add(FlexItem(text3).withFlex(1.0f));
    
    cb3.items.add(FlexItem(rb3).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, dynamicSpace)).withFlex(1.0f));
    
    layout.items.add(FlexItem(cb3).withMargin(rightLeftMargin).withFlex(1.0f));
    layout.items.add(FlexItem(div3).withWidth(2.0f).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));
    
    //Box 4
    FlexBox fb4;
    fb4.flexDirection = FlexBox::Direction::row;
    
    fb4.items.add(FlexItem(sliderFrequency4).withMargin(standardMargin).withFlex(1.0f));
    fb4.items.add(FlexItem(sliderGain4).withMargin(standardMargin).withFlex(1.0f));
    fb4.items.add(FlexItem(sliderQ4).withMargin(FlexItem::Margin::Margin(15.0f, 0.0f, 10.0f, dynamicSpace)).withFlex(1.0f));
    
    FlexBox cb4;
    cb4.flexDirection = FlexBox::Direction::column;
    cb4.items.add(FlexItem(fb4).withFlex(6.0f));
    
    FlexBox rb4;
    rb4.flexDirection = FlexBox::Direction::row;
    rb4.items.add(FlexItem(boxType4).withFlex(2.0f));
    rb4.items.add(FlexItem(text4).withMargin(FlexItem::Margin::Margin(0.0f, -dynamicSpace, 0.0f, 0.0f)).withFlex(1.0f));
    
    cb4.items.add(FlexItem(rb4).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, dynamicSpace)).withFlex(1.0f));
    
    layout.items.add(FlexItem(cb4).withMargin(leftMargin).withFlex(1.0f));
    
    //Final
    layout.performLayout(getLocalBounds());
    
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderFrequency1);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain1);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderQ1);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderFrequency2);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain2);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderQ2);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderFrequency3);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain3);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderQ3);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderFrequency4);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderGain4);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderQ4);
}
