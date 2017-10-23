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
    bypassButton.setClickingTogglesState(true); // Make it a toggle
    addAndMakeVisible(shadow.get());
    addAndMakeVisible(bypassButton);
}

MMTabBarButton::~MMTabBarButton()
{
}

void MMTabBarButton::resized()
{
    shadow->setBounds(getLocalBounds());
    muteButtonBg->setBounds(getLocalBounds());

    shadow->setTransformToFit(getLocalBounds().toFloat(), RectanglePlacement::Flags::yTop | RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::stretchToFit);

    bypassButton.setBounds(getLocalBounds().removeFromRight(getWidth() / 2));
}

void MMTabBarButton::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    shadow->setVisible(!isFrontTab());

    g.fillAll(getTabBackgroundColour());
    g.drawText(getName(), getTextArea(), Justification::centred);
    muteButtonBg->drawWithin(g, getLocalBounds().toFloat(), RectanglePlacement::Flags::yTop | RectanglePlacement::Flags::xLeft, 1.0f);

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
