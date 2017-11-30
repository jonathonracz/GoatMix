/*
  ==============================================================================

    MMTabBarButton.cpp
    Created: 13 Oct 2017 12:06:57am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMTabBarButton.h"
#include "MMLookAndFeel.h"
#include "UIStrings.h"

MMTabBarButton::MMTabBarButton(DraggableTabbedComponent& _owner, MobileMixPluginInstance& _representedPlugin) :
    DraggableTabBarButton(_representedPlugin.getName(), _owner),
    shadow(Drawable::createFromImageData(BinaryData::tabshadow_svg, BinaryData::tabshadow_svgSize)),
    muteButtonBg(Drawable::createFromImageData(BinaryData::mutebuttonbg_svg, BinaryData::mutebuttonbg_svgSize)),
    bypassButton(BinaryData::power_svg,
                 BinaryData::power_svgSize,
                 true,
                 false,
                 _representedPlugin.getName() + "BypassButton"),
    bypassButtonAttachment(_representedPlugin.state, _representedPlugin.paramBypass->paramID, bypassButton),
    representedPlugin(_representedPlugin)
{
    assert(shadow);
    owner.addListener(this);
    bypassButton.addMouseListener(this, false);
    bypassButton.setOverrideColors(MMLookAndFeel::ColourIds::muteButtonOn, MMLookAndFeel::ColourIds::muteButtonOff);
    meter.setMaxGainDisplayValue(1.1f);
    meter.setSource(&representedPlugin.meterSource);
    meter.addMouseListener(this, true);

    setTooltip(UIStrings::Meta::tab);
    bypassButton.setTooltip(UIStrings::Meta::mute);

    addAndMakeVisible(shadow.get());
    addAndMakeVisible(bypassButton);
    addAndMakeVisible(meter);

    // Notice we don't make this visible, so that we can get the transform
    // ease-of-use benefits of being a child component, while being able to
    // paint manually with a border in the paint callback.
    addChildComponent(muteButtonBg.get());
}

MMTabBarButton::~MMTabBarButton()
{
}

void MMTabBarButton::resized()
{
    muteButtonBg->setTransformToFit(getLocalBounds().toFloat(), RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::yTop);
    shadow->setBounds(getLocalBounds());
    shadow->setTransformToFit(getLocalBounds().toFloat(), RectanglePlacement::Flags::yTop | RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::stretchToFit);
    Rectangle<int> bypassButtonBounds = muteButtonBg->getBoundsInParent();
    bypassButtonBounds.reduce(muteButtonBg->getWidth() * 0.1f, muteButtonBg->getHeight() * 0.1f);
    bypassButtonBounds.setCentre(bypassButtonBounds.getCentreX() * 0.95f, bypassButtonBounds.getCentreY());
    bypassButton.setBounds(bypassButtonBounds);
    meter.setBoundsRelative(0.9f, 0.5f, 0.1f, 0.7f);
    meter.setCentrePosition(meter.getX(), meter.getY());
}

void MMTabBarButton::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    if (freezeSnapshot.isValid())
    {
        g.drawImageAt(freezeSnapshot, 0, 0);
        return;
    }

    shadow->setVisible(!isFrontTab());
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    float borderThickness = lf.borderThickness;

    Path muteButtonBgBorder = muteButtonBg->getOutlineAsPath();
    muteButtonBgBorder.applyTransform(muteButtonBgBorder.getTransformToScaleToFit(getLocalBounds().toFloat(), true, Justification::topLeft));

    Path border;
    border.addRectangle(getLocalBounds());

    g.setColour(lf.findColour(MMLookAndFeel::ColourIds::muteButtonBg));
    g.fillPath(muteButtonBgBorder);
    g.setColour(lf.findColour(MMLookAndFeel::ColourIds::outline));
    g.strokePath(muteButtonBgBorder, PathStrokeType(borderThickness));
    g.strokePath(border, PathStrokeType(borderThickness * 2.0f));
    Rectangle<int> textArea = getTextArea();
    textArea.setLeft(muteButtonBgBorder.getBounds().getRight());
    textArea.setRight(meter.getBounds().getX());
    g.drawText(getTabbedButtonBar().getTabNames()[getIndex()], textArea, Justification::centred);
}

int MMTabBarButton::getBestTabLength(int depth)
{
    return owner.getWidth() / owner.getNumTabs();
}

void MMTabBarButton::tabDragStarted(int atIndex)
{
    if (atIndex == getIndex())
    {
        Component* topComponent = getTopLevelComponent();
        freezeSnapshot = topComponent->createComponentSnapshot(topComponent->getLocalArea(this, getLocalBounds()));
        meter.stopAnimating();
        setOpaque(true);
    }
}

void MMTabBarButton::tabDragEnded(int atIndex)
{
    if (atIndex == getIndex())
    {
        meter.startAnimating(30);
        setOpaque(false);
        freezeSnapshot = Image();
    }
}
