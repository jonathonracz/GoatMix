/*
  ==============================================================================

    ReverbPreview.cpp
    Created: 3 Nov 2017 1:40:27am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "ReverbPreview.h"
#include "MMLookAndFeel.h"

ReverbPreview::ReverbPreview(MMReverb::Parameters::Ptr paramsToFollow)
{
    dsp::ProcessSpec spec;
    spec.numChannels = 1;
    spec.sampleRate = 440;
    spec.maximumBlockSize = 1024;
    reverb.params = paramsToFollow;
    reverb.prepare(spec);
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

    /*
    // Run distortion DSP
    {
        processedSignal.makeCopyOf(freshSignal, true);
        dsp::AudioBlock<float> block(processedSignal);
        dsp::ProcessContextReplacing<float> context(block);
        distortion.process(context);
    }

    // Draw preview wave
    {
        Path wavePath;
        wavePath.preallocateSpace(processedSignal.getNumSamples());
        float pathXDelta = getWidth() / processedSignal.getNumSamples();
        for (int channel = 0; channel < processedSignal.getNumChannels(); channel++)
        {
            const float* sample = processedSignal.getReadPointer(channel);
            for (int i = 0; i < processedSignal.getNumSamples(); ++i)
            {
                float yPos = sample[i] * getHeight() * 0.25f;
                if (i == 0)
                    wavePath.startNewSubPath(0, yPos);
                else
                    wavePath.lineTo(pathXDelta * i, yPos);
            }
        }
        g.strokePath(wavePath, PathStrokeType(lf.borderThickness));
    }
     */
}

void ReverbPreview::sliderValueChanged(Slider* slider)
{
    repaint();
}
