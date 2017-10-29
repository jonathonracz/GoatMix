/*
  ==============================================================================

    MobileMixPluginInstanceEditor.h
    Created: 7 Oct 2017 5:17:49pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MobileMixPluginInstance.h"
#include "../GUI/MMParameterSlider.h"

class MobileMixPluginInstanceEditor :
    public AudioProcessorEditor
{
public:
    virtual ~MobileMixPluginInstanceEditor() {}

protected:
    MobileMixPluginInstanceEditor(MobileMixPluginInstance& processor);

    /** Convenience methods + definitions for creating attachment points for
        editor UI elements.
    */
    typedef std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> MMButtonAttachment;
    typedef std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> MMComboBoxAttachment;
    typedef std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> MMSliderAttachment;

    MMButtonAttachment createButtonAttachment(AudioProcessorParameterWithID* parameter, Button& buttonToControl);
    MMComboBoxAttachment createComboBoxAttachment(AudioProcessorParameterWithID* parameter, ComboBox& comboBoxToControl);
    MMSliderAttachment createSliderAttachment(AudioProcessorParameterWithID* parameter, MMParameterSlider& sliderToControl);

    static void setVerticalRotatedWithBounds(Component* component, Rectangle<int> verticalBounds, bool clockwise = false);

    MobileMixPluginInstance& processor;

private:
    MMButtonAttachment bypassButtonAttachment;
    ToggleButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MobileMixPluginInstanceEditor)
};
