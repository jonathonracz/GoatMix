/*
  ==============================================================================

    FFTDisplay.h
    Created: 23 Nov 2017 10:09:36pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/SignalSnapshotter.h"

class FFTDisplay :
    public Component,
    private Timer
{
public:
    FFTDisplay(SignalSnapshotter& _source) :
        source(_source)
    {
        startTimer(source.getActiveSnapshotTimeDeltaSeconds() * 1000.0f);
    }

    ~FFTDisplay() {}

private:
    void paint(Graphics& g) override
    {
        // Draw the contents of fftBuffer, which at this point will have the
        // real-only frequency data.
        float pathDelta = getWidth() / static_cast<float>(fftBuffer.getNumSamples());
        for (int channel = 0; channel < fftBuffer.getNumChannels(); ++channel)
        {
            Path fftPath;
            fftPath.preallocateSpace(fftBuffer.getNumSamples());
            for (int i = 0; i < fftBuffer.getNumSamples(); ++i)
            {
                const float* channelPtr = fftBuffer.getReadPointer(channel);
                float x = i * pathDelta;
                float y = channelPtr[i] * static_cast<float>(getWidth());
                if (i == 0)
                    fftPath.startNewSubPath(x, y);
                else
                    fftPath.lineTo(x, y);
            }

            g.setColour(Colours::black);
            g.strokePath(fftPath, PathStrokeType(2.0f));
        }
    }

    void timerCallback() override
    {
        // If our snapshot size changed, resize our FFT to match.
        initializeFFTIfNeeded();

        // Update our paint data and repaint if we can grab the data we want to
        // update for painting from whatever thread the paint code is running
        // on.
        SignalSnapshotter::Snapshot::Ptr currentSnapshot = source.getLatestSnapshot();
        bool shouldRepaint = currentSnapshot->isValid();
        if (shouldRepaint)
        {
            fftBuffer.makeCopyOf(*currentSnapshot->getSignal(), true);
            for (int channel = 0; channel < fftBuffer.getNumChannels(); ++channel)
            {
                jassert(fftBuffer.getNumSamples() / 2 == fft->getSize());
                fft->performFrequencyOnlyForwardTransform(fftBuffer.getWritePointer(channel));
            }
            jcf::BufferDebugger::capture("Snapshot", fftBuffer.getReadPointer(0), fftBuffer.getNumSamples(), -1.0f, 1.0f);
        }

        if (shouldRepaint)
            repaint();

        // If our snapshot rate changed, change our refresh rate to match.
        int paramDeltaMs = static_cast<int>(source.getActiveSnapshotTimeDeltaSeconds() * 1000.0f);
        if (paramDeltaMs != getTimerInterval())
            startTimer(paramDeltaMs);
    }

    void initializeFFTIfNeeded() noexcept
    {
        int expectedFFTSize = source.getActiveSnapshotSampleSize() / 2;
        if (!fft || fft->getSize() != expectedFFTSize)
        {
            jassert(isPowerOfTwo(expectedFFTSize));
            fft = std::unique_ptr<dsp::FFT>(new dsp::FFT(findHighestSetBit(expectedFFTSize)));
        }
    }

    SignalSnapshotter& source;
    AudioBuffer<float> fftBuffer;
    std::unique_ptr<dsp::FFT> fft;
};
