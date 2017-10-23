/*
  ==============================================================================

    MMTopBar.cpp
    Created: 21 Oct 2017 10:16:29pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMTopBar.h"
#include "../MobileMixPluginEditor.h"

MMTopBar::MMTopBar(MobileMixAudioProcessor& _processor) :
    processor(_processor),
    undoButton("undoButton", DrawableButton::ButtonStyle::ImageFitted),
    redoButton("redoButton", DrawableButton::ButtonStyle::ImageFitted),
    logoSVG(Drawable::createFromImageData(BinaryData::goataudio_svg, BinaryData::goataudio_svgSize)),
    undoSVG(Drawable::createFromImageData(BinaryData::undo_svg, BinaryData::undo_svgSize)),
    redoSVG(Drawable::createFromImageData(BinaryData::redo_svg, BinaryData::redo_svgSize))
{
    assert(logoSVG);
    assert(undoSVG);
    assert(redoSVG);

    undoButton.setImages(undoSVG.get());
    redoButton.setImages(redoSVG.get());

    undoButton.addListener(this);
    redoButton.addListener(this);
    processor.undoManager.addChangeListener(this);

    addAndMakeVisible(undoButton);
    addAndMakeVisible(redoButton);
    addAndMakeVisible(*logoSVG);
}

void MMTopBar::resized()
{
    FlexBox layout;

    FlexItem::Margin logoMargin(getHeight() * 0.2f);
    logoMargin.bottom += logoMargin.bottom * 0.4f; // Squish the bottom to make it look more balanced
    layout.items.add(FlexItem(*logoSVG).withFlex(1.0f).withMargin(logoMargin));

    layout.items.add(FlexItem(undoButton).withFlex(1.0f));
    layout.items.add(FlexItem(redoButton).withFlex(1.0f));

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
    logoSVG->setTransformToFit(logoSVG->getBoundsInParent().toFloat(),
        RectanglePlacement(RectanglePlacement::Flags::xLeft | RectanglePlacement::Flags::yMid));
}

void MMTopBar::buttonClicked(Button* button)
{
    if (button == &undoButton)
    {
        processor.undoManager.undo();
    }
    else if (button == &redoButton)
    {
        processor.undoManager.redo();
    }
}

void MMTopBar::changeListenerCallback(ChangeBroadcaster* source)
{
    // See declaration comment for the bad reasoning behind this.
    if (!processor.paramUndoRedoCleanedUp)
    {
        processor.undoManager.clearUndoHistory();
        processor.paramUndoRedoCleanedUp = true;
    }

    if (processor.undoManager.canUndo())
    {
        undoButton.setAlpha(1.0f);
    }
    else
    {
        undoButton.setAlpha(0.25f);
    }

    if (processor.undoManager.canRedo())
    {
        redoButton.setAlpha(1.0f);
    }
    else
    {
        redoButton.setAlpha(0.25f);
    }
}
