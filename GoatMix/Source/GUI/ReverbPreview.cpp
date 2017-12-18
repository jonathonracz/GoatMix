/*
  ==============================================================================

    ReverbPreview.cpp
    Created: 3 Nov 2017 1:40:27am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "ReverbPreview.h"
#include "GMLookAndFeel.h"

ReverbPreview::ReverbPreview(AudioProcessorValueTreeState& _state, String _roomSizeID,
    String _dampingID, String _widthID, String _freezeID) :
    state(_state),
    roomSizeID(_roomSizeID),
    dampingID(_dampingID),
    widthID(_widthID),
    freezeID(_freezeID),
    cache(1),
    thumbnail(1, formatManager, cache)
{
    state.addParameterListener(roomSizeID, this);
    state.addParameterListener(dampingID, this);
    state.addParameterListener(widthID, this);
    state.addParameterListener(freezeID, this);

    spec.numChannels = 1;
    spec.sampleRate = 4410;
    spec.maximumBlockSize = 1024;
    buffer.setSize(spec.numChannels, spec.maximumBlockSize);
    reverb.prepare(spec);
    thumbnail.addChangeListener(this);
    processPreviewSignal();
}

void ReverbPreview::paint(Graphics& g)
{
    GMLookAndFeel& lf = static_cast<GMLookAndFeel&>(getLookAndFeel());

    g.setColour(findColour(GMLookAndFeel::ColourIds::outline));

    // Outer border
    {
        Path outline;
        outline.addRectangle(getLocalBounds());
        g.strokePath(outline, PathStrokeType(lf.borderThickness));
    }

    if (reverb.params->freeze)
        g.drawFittedText(NEEDS_TRANS("Freeze enabled\n(Feedback loop is infinite)"), getLocalBounds(), Justification::Flags::centred, 1, 1.0f);
    else
        thumbnail.drawChannel(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 0, 1.0f);
}

void ReverbPreview::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == roomSizeID)
        reverb.params->roomSize = newValue;
    else if (parameterID == dampingID)
        reverb.params->damping = newValue;
    else if (parameterID == widthID)
        reverb.params->width = newValue;
    else if (parameterID == freezeID)
        reverb.params->freeze = static_cast<bool>(newValue);

    processPreviewSignal();
}

void ReverbPreview::processPreviewSignal()
{
    if (reverb.params->freeze)
    {
        repaint();
        return;
    }

    thumbnail.reset(spec.numChannels, spec.sampleRate);
    cache.clear();
    reverb.reset();
    buffer.clear();

    // Create an impulse.
    buffer.setSample(0, 0, 1.0f);

    // Run the reverb on the aforementioned impulse until reaching a reasonable
    // decay level.
    int blockNumber = 0;
    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    float magnitude = 0.0f;
    do {
        if (blockNumber > 0)
            block.clear();

        reverb.process(context);
        block.multiply(10.0f); // Arbitrary multiplier to give us more amplitude resolution when the thumbnail is generated.
        thumbnail.addBlock(buffer.getNumSamples() * blockNumber++, buffer, 0, buffer.getNumSamples());
        magnitude = buffer.getMagnitude(0, 0, buffer.getNumSamples());
        JUCE_UNDENORMALISE(magnitude);
    } while (magnitude > 0.01f);
}

void ReverbPreview::changeListenerCallback(ChangeBroadcaster* source)
{
    jassert(source == &thumbnail);
    repaint();
}
