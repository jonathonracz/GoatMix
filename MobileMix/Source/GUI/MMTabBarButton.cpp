/*
  ==============================================================================

    MMTabBarButton.cpp
    Created: 13 Oct 2017 12:06:57am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMTabBarButton.h"

MMTabBarButton::MMTabBarButton(DraggableTabbedComponent& _owner, MobileMixPluginInstance& _representedPlugin) :
    DraggableTabBarButton(_representedPlugin.getName(), _owner),
    shadow(Drawable::createFromImageData(BinaryData::tabshadow_svg, BinaryData::tabshadow_svgSize)),
    muteButtonBg(Drawable::createFromImageData(BinaryData::mutebuttonbg_svg, BinaryData::mutebuttonbg_svgSize)),
    bypassButton(_representedPlugin.getName() + "BypassButton"),
    bypassButtonAttachment(_representedPlugin.state, _representedPlugin.paramBypass->paramID, bypassButton),
    representedPlugin(_representedPlugin)
{
    assert(shadow);
    bypassButton.addMouseListener(this, false);
    meter.setMaxGainDisplayValue(1.1f);
    meter.setSource(&representedPlugin.meterSource);
    addAndMakeVisible(shadow.get());
    addAndMakeVisible(muteButtonBg.get());
    addAndMakeVisible(bypassButton);
    addAndMakeVisible(meter);
}

MMTabBarButton::~MMTabBarButton()
{
}

void MMTabBarButton::resized()
{
    muteButtonBg->setTransformToFit(getLocalBounds().toFloat(), RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::yTop);
    shadow->setBounds(getLocalBounds());
    shadow->setTransformToFit(getLocalBounds().toFloat(), RectanglePlacement::Flags::yTop | RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::stretchToFit);
    bypassButton.setBounds(muteButtonBg->getBoundsInParent());
    meter.setBoundsRelative(0.9f, 0.5f, 0.1f, 0.7f);
    meter.setCentrePosition(meter.getX(), meter.getY());
}

void MMTabBarButton::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    shadow->setVisible(!isFrontTab());

    g.fillAll(getTabBackgroundColour());
    g.drawText(getName(), getTextArea(), Justification::centred);

    float borderThickness = 4.0f;

    g.setColour(Colours::black);
    Path muteButtonBgBorder = muteButtonBg->getOutlineAsPath();
    muteButtonBgBorder.applyTransform(muteButtonBgBorder.getTransformToScaleToFit(getLocalBounds().toFloat(), true, Justification::topLeft));

    Path border;
    border.addRectangle(getLocalBounds());

    g.strokePath(muteButtonBgBorder, PathStrokeType(borderThickness / 2.0f));
    g.strokePath(border, PathStrokeType(borderThickness));
}

int MMTabBarButton::getBestTabLength(int depth)
{
    return owner.getWidth() / owner.getNumTabs();
}
