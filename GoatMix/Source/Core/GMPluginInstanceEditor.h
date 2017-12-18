/*
  ==============================================================================

    GMPluginInstanceEditor.h
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "GMPluginInstance.h"
#include "../GUI/GMParameterSlider.h"

class GMPluginInstanceEditor :
    public Component
{
public:
    virtual ~GMPluginInstanceEditor() {}

protected:
    GMPluginInstanceEditor(GMPluginInstance& processor);

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

    GMPluginInstance& processor;

private:
    GMButtonAttachment bypassButtonAttachment;
    ToggleButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GMPluginInstanceEditor)
};
