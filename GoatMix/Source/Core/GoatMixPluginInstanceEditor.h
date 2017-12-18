/*
  ==============================================================================

    GoatMixPluginInstanceEditor.h
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GoatMixPluginInstance.h"
#include "../GUI/GMParameterSlider.h"

class GoatMixPluginInstanceEditor :
    public Component
{
public:
    virtual ~GoatMixPluginInstanceEditor() {}

protected:
    GoatMixPluginInstanceEditor(GoatMixPluginInstance& processor);

    /** Convenience methods + definitions for creating attachment points for
        editor UI elements.
    */
    typedef std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> GMButtonAttachment;
    typedef std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> GMComboBoxAttachment;
    typedef std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> GMSliderAttachment;

    GMButtonAttachment createButtonAttachment(AudioProcessorParameterWithID* parameter, Button& buttonToControl);
    GMComboBoxAttachment createComboBoxAttachment(AudioProcessorParameterWithID* parameter, ComboBox& comboBoxToControl);
    GMSliderAttachment createSliderAttachment(AudioProcessorParameterWithID* parameter, GMParameterSlider& sliderToControl);

    static void setVerticalRotated(Component* component, bool clockwise = false);
    static void setUpsideDownRotated(Component* component);

    GoatMixPluginInstance& processor;

private:
    GMButtonAttachment bypassButtonAttachment;
    ToggleButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GoatMixPluginInstanceEditor)
};
