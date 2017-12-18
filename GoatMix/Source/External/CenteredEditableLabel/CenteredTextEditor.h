/*
  ==============================================================================

    CenteredTextEditor.h
    Created: 4 May 2017 11:02:08am
    Author:  Adam Wilson

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/*
*/
class CenteredTextEditor    : public TextEditor,
                              public ComponentListener,
                              public TextEditor::Listener,
                              public KeyListener
{
public:
    CenteredTextEditor (const String& componentName = String()) : TextEditor (componentName)
    {
        addComponentListener (this);
        addListener (this);
    }

    ~CenteredTextEditor()
    {
    }

    void setSizeAndPosition()
    {
        int textWidth = TextEditor::getTextWidth();
        int textHeight = TextEditor::getTextHeight();

        auto parentBounds = getParentComponent()->getBounds();

        Rectangle<int> newBounds (parentBounds.getWidth() / 2 - (textWidth / 2),
                                  parentBounds.getHeight() / 2 - (textHeight / 2),
                                  textWidth,
                                  textHeight);
        setBounds (newBounds);
    }

    void textEditorTextChanged (TextEditor &editor) override
    {
        setSizeAndPosition();
    }

    void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized) override
    {
        setSizeAndPosition();
    }

    bool keyPressed (const KeyPress &key, Component *originatingComponent) override
    {
        setSizeAndPosition();
        return true;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CenteredTextEditor)
};
