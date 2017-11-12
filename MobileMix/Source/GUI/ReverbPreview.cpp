/*
  ==============================================================================

    ReverbPreview.cpp
    Created: 3 Nov 2017 1:40:27am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "ReverbPreview.h"
#include "MMLookAndFeel.h"

ReverbPreview::ReverbPreview(MMReverb::Parameters::Ptr paramsToFollow, ChangeBroadcaster& _paramChangeSource) :
    paramChangeSource(_paramChangeSource),
    cache(1),
    thumbnail(1, formatManager, cache)
{
    spec.numChannels = 1;
    spec.sampleRate = 4410;
    spec.maximumBlockSize = 1024;
    buffer.setSize(spec.numChannels, spec.maximumBlockSize);
    reverb.params = paramsToFollow;
    reverb.prepare(spec);
    thumbnail.addChangeListener(this);
    paramChangeSource.addChangeListener(this);
}

void ReverbPreview::paint(Graphics& g)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    g.setColour(findColour(MMLookAndFeel::ColourIds::outline));

    // Outer border
    {
        Path outline;
        outline.addRectangle(getLocalBounds());
        g.strokePath(outline, PathStrokeType(lf.borderThickness));
    }

    if (reverb.params->freeze)
    {
        g.drawFittedText(NEEDS_TRANS("Freeze enabled\n(Feedback loop is infinite)"), getLocalBounds(), Justification::Flags::centred, 1, 1.0f);
    }
    else
    {
        thumbnail.drawChannel(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 0, 1.0f);
    }
}

void ReverbPreview::processPreviewSignal()
{
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
    if (source == &thumbnail)
    {
        repaint();
    }
    else if (source == &paramChangeSource)
    {
        if (reverb.params->freeze)
            repaint();
        else
            processPreviewSignal();
    }
}
