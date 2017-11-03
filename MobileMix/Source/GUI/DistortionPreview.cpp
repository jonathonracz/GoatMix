/*
  ==============================================================================

    DistortionPreview.cpp
    Created: 30 Oct 2017 5:22:47pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "DistortionPreview.h"
#include "MMLookAndFeel.h"

DistortionPreview::DistortionPreview(DistortionChain::Parameters::Ptr paramsToFollow) :
    freshSignal(1, generatorFrequency),
    processedSignal(1, generatorFrequency)
{
    // Generate a clean signal.
    dsp::Oscillator<float> signalGenerator(&std::sinf, generatorFrequency);
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = generatorFrequency;
    spec.numChannels = 1;
    spec.sampleRate = generatorFrequency;
    signalGenerator.prepare(spec);
    distortion.params = paramsToFollow;
    distortion.prepare(spec);

    dsp::AudioBlock<float> block(freshSignal);
    dsp::ProcessContextReplacing<float> context(block);
    signalGenerator.process(context);
}

void DistortionPreview::paint(Graphics& g)
{
    MMLookAndFeel& lf = static_cast<MMLookAndFeel&>(getLookAndFeel());

    // Center line
    {
        g.setColour(findColour(MMLookAndFeel::ColourIds::outlineLight));
        g.fillRect(Rectangle<int>(0,
                                  (getHeight() / 2) - lf.borderThickness / 2,
                                  getWidth(),
                                  lf.borderThickness));
    }

    g.setColour(findColour(MMLookAndFeel::ColourIds::outline));

    // Outer border
    {
        Path outline;
        outline.addRectangle(getLocalBounds());
        g.strokePath(outline, PathStrokeType(lf.borderThickness));
    }

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
}

void DistortionPreview::sliderValueChanged(Slider* slider)
{
    repaint();
}
