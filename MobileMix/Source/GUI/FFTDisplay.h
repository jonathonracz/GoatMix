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
#include "../DSP/LogMap.h"

class FFTDisplay :
    public Component,
    private Timer
{
public:
    FFTDisplay(SignalSnapshotter& _source) :
        verticalScale(0.0f, 4.0f), // Hardcode -INF to +12 dB.
        source(_source)
    {
        verticalScale.setSkewForCentre(1.0f); // Hardcode 0 dBFS at center.
        startTimer(source.getActiveSnapshotTimeDeltaSeconds() * 1000.0f);
        logMap.setLogRange(Range<float>(20.0f, 20000.0f));
    }

    ~FFTDisplay() {}

private:
    void paint(Graphics& g) override
    {
        // Draw the contents of fftBuffer, which at this point will have the
        // real-only frequency data in the first quarter of the buffer.
        int numFFTSamples = getNumBins();
        // This is a for loop in case I can somehow squeeze drawing in multiple
        // channels - for now I'm not even going to bother trying and instead
        // draw a single summed frequency curve.
        for (int channel = 0; channel < fftBuffer.getNumChannels(); ++channel)
        {
            Path fftPath;
            fftPath.preallocateSpace(fftBuffer.getNumSamples() - getBinsToSkipForCurrentLogMap() + 4);
            for (int i = 0; i < numFFTSamples; ++i)
            {
                const float* channelBins = fftBuffer.getReadPointer(channel);

                auto calcXPos = [&](float frequency) -> float
                {
                    return logMap.logToLin(frequency) * static_cast<float>(getWidth());
                };

                auto calcYPos = [&](float frequencyAmplitude) -> float
                {
                    return (1.0f - verticalScale.convertTo0to1(frequencyAmplitude)) * static_cast<float>(getHeight());
                };

                float frequency = getFrequencyOfBin(i);
                if (frequency < logMap.getLogRange().getStart())
                    continue;

                if (fftPath.isEmpty())
                {
                    if (frequency != logMap.getLogRange().getStart())
                    {
                        // We need to get our first point via interpolation.
                        float interpAmplitude = getFrequencyAmplitudeWithLinearInterp(logMap.getLogRange().getStart(), channel);
                        fftPath.startNewSubPath(calcXPos(logMap.getLogRange().getStart()), calcYPos(interpAmplitude));
                        fftPath.lineTo(calcXPos(frequency), calcYPos(channelBins[i]));
                    }
                    else
                    {
                        fftPath.startNewSubPath(calcXPos(frequency), calcYPos(channelBins[i]));
                    }
                }
                else
                {
                    fftPath.lineTo(calcXPos(frequency), calcYPos(channelBins[i]));
                }
            }

            fftPath.lineTo(static_cast<float>(getWidth()), static_cast<float>(getHeight()));
            fftPath.lineTo(0.0f, static_cast<float>(getHeight()));
            fftPath.closeSubPath();

            g.setColour(Colours::black);
            g.fillPath(fftPath);
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
            fft->performFrequencyOnlyForwardTransform(fftBuffer.getWritePointer(0));
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

    int getNumBins() const noexcept
    {
        return fft->getSize() / 2;
    }

    float getFrequencyOfBin(int binIndex) const noexcept
    {
        jassert(binIndex < fft->getSize() / 2);
        return binIndex * (source.getActiveSampleRate() / static_cast<float>(source.getActiveSnapshotSampleSize()));
    }

    int findBinJustBeforeFrequency(float frequency) const noexcept
    {
        jassert(frequency > 0 && frequency < source.getActiveSampleRate() / 2.0);
        for (int i = 0; i < fft->getSize() / 2; ++i)
            if (getFrequencyOfBin(i) > frequency)
                return i - 1;

        jassertfalse;
        return -1;
    }

    float getFrequencyAmplitudeWithLinearInterp(float frequency, int channel) const noexcept
    {
        jassert(frequency <= source.getActiveSampleRate() / 2.0); // Leaving nyquist, there's nothing here!
        const float* bins = fftBuffer.getReadPointer(channel);

        if (frequency == source.getActiveSampleRate() / 2.0)
            return bins[(fft->getSize() / 2) - 1];

        int binBefore = findBinJustBeforeFrequency(frequency);
        float binBeforeFrequency = getFrequencyOfBin(binBefore);

        if (binBeforeFrequency == frequency)
        {
            return bins[binBefore];
        }
        else
        {
            float binAfterFrequency = getFrequencyOfBin(binBefore + 1);
            jassert(frequency > binBeforeFrequency && frequency < binAfterFrequency);
            // Simple linear interpolation of the bins.
            float proportionBetweenBins = (frequency - binBeforeFrequency) / (binAfterFrequency - binBeforeFrequency);
            return ((bins[binBefore + 1] - bins[binBefore]) * proportionBetweenBins) + bins[binBefore];
        }
    }

    int getBinsToSkipForCurrentLogMap() const noexcept
    {
        int numBins = getNumBins();
        for (int i = 0; i < numBins; ++i)
        {
            if (getFrequencyOfBin(i) >= logMap.getLogRange().getStart())
                return i;
        }

        return numBins;
    }

    NormalisableRange<float> verticalScale;
    SignalSnapshotter& source;
    AudioBuffer<float> fftBuffer;
    LogMap logMap;
    std::unique_ptr<dsp::FFT> fft;
};
