/*
  ==============================================================================

    MMTopBar.cpp
    Created: 21 Oct 2017 10:16:29pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMTopBar.h"

MMTopBar::MMTopBar() :
    undoButton("undoButton", DrawableButton::ButtonStyle::ImageRaw),
    redoButton("redoButton", DrawableButton::ButtonStyle::ImageRaw)
{
    undoButton.setLookAndFeel(&buttonAppearance);
    redoButton.setLookAndFeel(&buttonAppearance);
    XmlDocument goatLogo(BinaryData::goataudio_svg);
    std::unique_ptr<XmlElement> goatLogoXml(goatLogo.getDocumentElement());
    assert(goatLogoXml);
    logo = std::unique_ptr<DrawableComposite>(static_cast<DrawableComposite*>(Drawable::createFromSVG(*goatLogoXml)));
    addAndMakeVisible(*logo);
}

void MMTopBar::resized()
{
    FlexBox layout;

    FlexItem::Margin logoMargin(getHeight() * 0.2f);
    logoMargin.bottom += logoMargin.bottom * 0.4f; // Squish the bottom to make it look more balanced
    layout.items.add(FlexItem(*logo).withFlex(1.0f).withMargin(logoMargin));

    layout.performLayout(getLocalBounds());

    // Stupid hack because of the way SVG drawing works in JUCE. We have to
    // manually set the drawable bounds even though the documentation encourages
    // relying on the fact the Drawable is a component with its own bounds
    // calculations.

    // TODO: File a bug against the SVG rendering where empty space around the
    // SVG object doesn't seem to be handled correctly - they appear to get
    // ignored when setting the drawable's rendering bounds, but get added when
    // the drawable is actually rendered. My workaround was to eliminate all
    // empty space around the logo to get predictable behavior.
    logo->setTransformToFit(logo->getBoundsInParent().toFloat(),
        RectanglePlacement(RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::yMid));
}
