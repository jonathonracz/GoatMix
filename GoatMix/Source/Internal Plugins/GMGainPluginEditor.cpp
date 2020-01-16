/*
  ==============================================================================

    GMGainPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GMGainPluginEditor.h"

GMGainPluginEditor::GMGainPluginEditor(GMGainPlugin& processor) :
    GMPluginInstanceEditor(processor),
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

    sliderGain.setTooltip(UIStrings::Shared::gain);
    sliderGainL.setTooltip(UIStrings::Shared::gain);
    sliderGainR.setTooltip(UIStrings::Shared::gain);
    sliderPan.setTooltip(UIStrings::Gain::pan);
    sliderPhaseDelayL.setTooltip(UIStrings::Gain::phaseDelay);
    sliderPhaseDelayR.setTooltip(UIStrings::Gain::phaseDelay);
    buttonPhaseInvertL.setTooltip(UIStrings::Gain::phaseInvert);
    buttonPhaseInvertR.setTooltip(UIStrings::Gain::phaseInvert);
    goniometer.setTooltip(UIStrings::Gain::goniometer);
    leftdBLabel.setTooltip(UIStrings::Gain::meterValue);
    maxdBLabel.setTooltip(UIStrings::Gain::meterValue);
    rightdBLabel.setTooltip(UIStrings::Gain::meterValue);

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
    leftdBLabel.setSource(processor.meterSource.meters[0]);
    addAndMakeVisible(leftdBLabel);

    //maxdBLabel.setSource(processor.meterSource.meters[0]);
    //addAndMakeVisible(maxdBLabel);

    rightdBLabel.setSource(processor.meterSource.meters[1]);
    addAndMakeVisible(rightdBLabel);

    // Meters here
    std::array<SimpleLevelMeter*, 4> meters = { &meterPosL, &meterPosR, &meterNegL, &meterNegR };
    for (size_t i = 0; i < meters.size(); ++i)
    {
        meters[i]->setSource(processor.meterSource.meters[i % 2]);

        if (i < 2)
        {
            meters[i]->setMinGainDisplayValue(1.0f);
            meters[i]->setMaxGainDisplayValue(2.0f);
        }

        addAndMakeVisible(meters[i]);
    }

    addAndMakeVisible(div);

    // Labels here
    std::array<SpanningLabel*, 4> labels = { &labelPosL, &labelPosR, &labelNegL, &labelNegR };
    for (size_t i = 0; i < labels.size(); ++i)
    {
        labels[i]->setLayoutDirection(SpanningLabel::LayoutDirection::verticalCenter);
        labels[i]->setValueToTextFunction([](float value) -> String {
            // Round all dB values to the nearest 0.5, snap anything < 0.1 to 0
            // (for rounding errors when doing proportion conversions)
            if (value < 0.1f)
                return "-INF";

            float dBValue = std::llround(Decibels::gainToDecibels(value) * 2.0f) / 2.0f;
            return (std::floor(dBValue) == dBValue) ? String(static_cast<int>(dBValue)) : String(dBValue, 1);
        });
        labels[i]->setRange(NormalisableRange<float>(meters[i]->getMinGainDisplayValue(), meters[i]->getMaxGainDisplayValue()));
        labels[i]->setReversedOrder(true);

        if (i < 2)
            labels[i]->setNumIntermediatePoints(1);
        else
            labels[i]->setNumIntermediatePoints(3);

        addAndMakeVisible(labels[i]);
    }
}

GMGainPluginEditor::~GMGainPluginEditor()
{
}

void GMGainPluginEditor::resized()
{
    //GMLookAndFeel& lf = static_cast<GMLookAndFeel&>(getLookAndFeel());

    FlexBox layout;

    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    float vertDynamicSpace = this->getHeight() * 0.02f;
    float labelsFlex = 0.8f;
    float metersFlex = 0.75f;
    FlexItem::Margin labelsMargin = FlexItem::Margin(10.0f, 2.0f, 10.0f, 2.0f);
    FlexItem::Margin meterMargin = FlexItem::Margin(15.0f, 0.0f, 15.0f, 0.0f);
    FlexItem::Margin standardMargin = FlexItem::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);

    // Amplitude (left side)
    FlexBox ampBox;
    ampBox.flexDirection = FlexBox::Direction::column;

    FlexBox ampTop;
    ampTop.flexDirection = FlexBox::Direction::row;
    ampTop.items.add(FlexItem(leftdBLabel).withFlex(2.0f));
    ampTop.items.add(FlexItem(maxdBLabel).withFlex(1.0f));
    ampTop.items.add(FlexItem(rightdBLabel).withFlex(2.0f));
    ampBox.items.add(FlexItem(ampTop).withMargin(FlexItem::Margin(0, dynamicSpace * 2, 0, 15.0f)).withFlex(1.0f));

    FlexBox ampBottom;
    ampBottom.flexDirection = FlexBox::Direction::row;
    ampBottom.items.add(FlexItem(sliderGainL).withMargin(FlexItem::Margin(15.0f, dynamicSpace, 15.0f, 0.0f)).withFlex(1.0f));

    // L meters
    ampBottom.items.add(FlexItem(labelPosL).withMargin(labelsMargin).withFlex(labelsFlex));
    ampBottom.items.add(FlexItem(meterPosL).withMargin(meterMargin).withFlex(metersFlex));

    ampBottom.items.add(FlexItem(labelNegL).withMargin(labelsMargin).withFlex(labelsFlex));
    ampBottom.items.add(FlexItem(meterNegL).withMargin(meterMargin).withFlex(metersFlex));

    ampBottom.items.add(FlexItem(sliderGain).withMargin(FlexItem::Margin(15.0f, dynamicSpace * 2, 15.0f, dynamicSpace * 2)).withFlex(1.0f));

    // R meters
    ampBottom.items.add(FlexItem(meterNegR).withMargin(meterMargin).withFlex(metersFlex));
    ampBottom.items.add(FlexItem(labelNegR).withMargin(labelsMargin).withFlex(labelsFlex));

    ampBottom.items.add(FlexItem(meterPosR).withMargin(meterMargin).withFlex(metersFlex));
    ampBottom.items.add(FlexItem(labelPosR).withMargin(labelsMargin).withFlex(labelsFlex));

    ampBottom.items.add(FlexItem(sliderGainR).withMargin(standardMargin).withFlex(1.0f));
    ampBox.items.add(FlexItem(ampBottom).withFlex(8.0f));

    layout.items.add(FlexItem(ampBox).withMargin(FlexItem::Margin(15.0f, dynamicSpace, 0.0f, vertSpace)).withFlex(1.0f));

    layout.items.add(FlexItem(div).withWidth(2.0f).withMargin(FlexItem::Margin(vertSpace, 0.0f, vertSpace, 0.0f)));

    // Phase (right side)
    float phaseWidth = (this->getWidth() * 0.405f);
    float phaseHeight = this->getHeight() - vertSpace * 2;
    float phaseSliderWidth = phaseWidth / 6;

    FlexBox phaseBox;
    phaseBox.flexDirection = FlexBox::Direction::column;
    float panHeight = phaseHeight * (1.0f/6.0f);
    phaseBox.items.add(FlexItem(sliderPan).withMargin(FlexItem::Margin(0.0f, 0.0f, vertDynamicSpace * 2, 0.0f)).withHeight(panHeight));

    FlexBox phaseBottom;
    phaseBottom.flexDirection = FlexBox::Direction::row;

    FlexBox lPhase;
    lPhase.flexDirection = FlexBox::Direction::column;
    lPhase.items.add(FlexItem(sliderPhaseDelayL).withMargin(FlexItem::Margin(0.0f, 0.0f, vertDynamicSpace * 2, 0.0f)).withWidth(phaseSliderWidth).withFlex(5.0f));
    lPhase.items.add(FlexItem(buttonPhaseInvertL).withWidth(phaseSliderWidth).withFlex(1.0f));
    phaseBottom.items.add(FlexItem(lPhase).withFlex(1.0f));

    // Goniometer
    float gonVertSpace = phaseHeight - panHeight;
    float gonHorSpace = phaseWidth - phaseSliderWidth * 2;
    float calcWidth = gonHorSpace;
    float calcHeight = gonVertSpace;
    if (calcWidth > calcHeight)
    {
        calcWidth = calcHeight;
    }
    else
    {
        calcHeight = calcWidth;
    }
    float horMargin = (gonHorSpace - calcWidth) / 2;
    float vertMargin = (gonVertSpace - calcHeight) / 2;
    if (horMargin < dynamicSpace * 2)
    {
        horMargin = dynamicSpace * 2;
        calcWidth = gonHorSpace - horMargin * 2;
        calcHeight = calcWidth;
    }
    else if (vertMargin < vertDynamicSpace * 2)
    {
        vertMargin = vertDynamicSpace * 2;
        calcHeight = gonVertSpace - vertMargin * 2;
        calcWidth = calcHeight;
    }
    FlexItem gonItem = FlexItem(goniometer).withWidth(calcWidth).withHeight(calcHeight);
    gonItem.margin = FlexItem::Margin(vertMargin, horMargin, vertMargin, horMargin);
    phaseBottom.items.add(gonItem);

    FlexBox rPhase;
    rPhase.flexDirection = FlexBox::Direction::column;
    rPhase.items.add(FlexItem(sliderPhaseDelayR).withMargin(FlexItem::Margin(0.0f, 0.0f, vertDynamicSpace * 2, 0.0f)).withWidth(phaseSliderWidth).withFlex(5.0f));
    rPhase.items.add(FlexItem(buttonPhaseInvertR).withWidth(phaseSliderWidth).withFlex(1.0f));
    phaseBottom.items.add(FlexItem(rPhase).withFlex(1.0f));
    phaseBox.items.add(FlexItem(phaseBottom).withFlex(6.0f));

    layout.items.add(FlexItem(phaseBox).withMargin(FlexItem::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace * 2)).withWidth(phaseWidth));

    layout.performLayout(getLocalBounds());

    Rectangle<int> shapeBounds = buttonPhaseInvertL.getLocalBounds().reduced(buttonPhaseInvertL.getWidth() * 0.15f, buttonPhaseInvertL.getHeight() * 0.15f);
    buttonPhaseInvertL.setInternalShapeBounds(shapeBounds);
    buttonPhaseInvertR.setInternalShapeBounds(shapeBounds);

    GMPluginInstanceEditor::setVerticalRotated(&sliderGainL);
    GMPluginInstanceEditor::setVerticalRotated(&sliderGain);
    GMPluginInstanceEditor::setVerticalRotated(&sliderGainR);
    GMPluginInstanceEditor::setVerticalRotated(&sliderPhaseDelayL);
    GMPluginInstanceEditor::setVerticalRotated(&sliderPhaseDelayR);
}
