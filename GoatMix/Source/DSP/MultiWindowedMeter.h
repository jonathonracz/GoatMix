/*
  ==============================================================================

    MultiWindowedMeter.h
    Created: 4 Dec 2017 12:01:39am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "WindowedMeter.h"

class MultiWindowedMeter :
    public dsp::ProcessorBase
{
public:
    MultiWindowedMeter() = default;
    ~MultiWindowedMeter() = default;

    bool allocateMeters(int numMeters) noexcept
    {
        if (numMeters != meters.size())
        {
            meters.clear();
            while (numMeters != meters.size())
                meters.add(new WindowedMeter);

            return true;
        }

        return false;
    }

    float getPeakInstant() const noexcept
    {
        return calcAverage([](WindowedMeter* meter) {
            return &meter->peakInstant;
        });
    }

    float getPeakWindowed() const noexcept
    {
        return calcAverage([](WindowedMeter* meter) {
            return &meter->peakWindowed;
        });
    }

    float getRMS() const noexcept
    {
        return calcAverage([](WindowedMeter* meter) {
            return &meter->rms;
        });
    }

    float getPeakHold() const noexcept
    {
        return calcAverage([](WindowedMeter* meter) {
            return &meter->peakHold;
        });
    }

    float getPeakOverall() const noexcept
    {
        return calcAverage([](WindowedMeter* meter) {
            return &meter->peakOverall;
        });
    }

    void resetPeakOverall() noexcept
    {
        for (WindowedMeter* meter : meters)
            meter->resetPeakOverall();
    }

    bool getClippingStatus() const noexcept
    {
        return getPeakOverall() > 1.0f;
    }

    void resetClippingStatus() noexcept
    {
        for (WindowedMeter* meter : meters)
            meter->resetClippingStatus();
    }

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        allocateMeters(static_cast<int>(spec.numChannels));
        for (uint32 i = 0; i < spec.numChannels; ++i)
        {
            meters[i]->params = params;
            meters[i]->prepare(spec);
        }
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        for (size_t i = 0; i < context.getInputBlock().getNumChannels(); ++i)
        {
            dsp::AudioBlock<float> monoBlock = context.getInputBlock().getSingleChannelBlock(i);
            dsp::ProcessContextReplacing<float> monoContext(monoBlock);
            meters[static_cast<int>(i)]->process(monoContext);
        }
    }

    void reset() noexcept override
    {
        for (auto& meter : meters)
            meter->reset();
    }

    WindowedMeter::Parameters::Ptr params = new WindowedMeter::Parameters;
    OwnedArray<WindowedMeter> meters;

private:
    float calcAverage(std::atomic<float>* (*getter)(WindowedMeter*)) const noexcept
    {
        float sum = 0.0f;
        for (WindowedMeter* meter : meters)
            sum += getter(meter)->load(std::memory_order_relaxed);

        std::atomic_thread_fence(std::memory_order_acquire);
        return sum / meters.size();
    }

    JUCE_DECLARE_WEAK_REFERENCEABLE(MultiWindowedMeter)
};
