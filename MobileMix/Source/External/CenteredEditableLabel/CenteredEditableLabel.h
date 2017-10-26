/*
  ==============================================================================

    CenteredEditableLabel.h
    Created: 4 May 2017 10:37:43am
    Author:  Adam Wilson

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "CenteredTextEditor.h"

//==============================================================================
/*
*/
class CenteredEditableLabel    : public Label
{
public:
    CenteredEditableLabel (const String& componentName = String(),
           const String& labelText = String()) : Label (componentName, labelText)
    {
    }

    ~CenteredEditableLabel()
    {
    }

protected:

    static void copyColourIfSpecified (Label& l, TextEditor& ed, int colourID, int targetColourID)
    {
        if (l.isColourSpecified (colourID) || l.getLookAndFeel().isColourSpecified (colourID))
            ed.setColour (targetColourID, l.findColour (colourID));
    }

    TextEditor *createEditorComponent () override
    {
        CenteredTextEditor* const ed = new CenteredTextEditor (getName());
        ed->applyFontToAllText (getLookAndFeel().getLabelFont (*this));
        copyAllExplicitColoursTo (*ed);

        copyColourIfSpecified (*this, *ed, textWhenEditingColourId, TextEditor::textColourId);
        copyColourIfSpecified (*this, *ed, backgroundWhenEditingColourId, TextEditor::backgroundColourId);
        copyColourIfSpecified (*this, *ed, outlineWhenEditingColourId, TextEditor::focusedOutlineColourId);

        return ed;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CenteredEditableLabel)
};
