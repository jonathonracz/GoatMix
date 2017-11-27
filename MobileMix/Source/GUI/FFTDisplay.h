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
        // real-only frequency data in the first quarter of the buffer.
        int numFFTSamples = fftBuffer.getNumSamples() / 4;
        float pathDelta = getWidth() / static_cast<float>(numFFTSamples);
        // This is a for loop in case I can somehow squeeze drawing in multiple
        // channels - for now I'm not even going to bother trying and instead
        // draw a single summed frequency curve.
        for (int channel = 0; channel < fftBuffer.getNumChannels(); ++channel)
        {
            Path fftPath;
            fftPath.preallocateSpace(fftBuffer.getNumSamples());
            for (int i = 0; i < numFFTSamples; ++i)
            {
                const float* channelPtr = fftBuffer.getReadPointer(channel);
                float x = i * pathDelta;
                float y = (1.0f - channelPtr[i]) * static_cast<float>(getHeight());
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
        if (currentSnapshot->isValid() && currentSnapshot->getSignal()->getNumChannels() > 0)
        {
            const RefCountedAudioBuffer<float>::Ptr bufferSnap = currentSnapshot->getSignal();
            fftBuffer.setSize(1, bufferSnap->getNumSamples() * 2);

            // Sum all channels into fftBuffer.
            for (int channel = 0; channel < fftBuffer.getNumChannels(); ++channel)
            {
                if (channel == 0)
                    fftBuffer.copyFrom(0, 0, bufferSnap->getReadPointer(channel), bufferSnap->getNumSamples());
                else
                    fftBuffer.addFrom(0, 0, bufferSnap->getReadPointer(channel), bufferSnap->getNumSamples());
            }

            // Perform FFT on the sum of all channels.
            fft->performFrequencyOnlyForwardTransform(fftBuffer.getWritePointer(channel));
            repaint();
        }

        // If our snapshot rate changed, change our refresh rate to match.
        int paramDeltaMs = static_cast<int>(source.getActiveSnapshotTimeDeltaSeconds() * 1000.0f);
        if (paramDeltaMs != getTimerInterval())
            startTimer(paramDeltaMs);
    }

    void initializeFFTIfNeeded() noexcept
    {
        int expectedFFTSize = source.getActiveSnapshotSampleSize();
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
