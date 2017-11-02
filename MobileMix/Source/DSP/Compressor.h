/*
  ==============================================================================

    Compressor.h
    Created: 2 Nov 2017 1:47:19pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../External/Maximilian/maximilian.h"
#include <vector>

/** Leveraging Maximilian's compressor since we're short on time for our MVP.
    Building something identical would be dead simple, as it's just an envelope
    follower controlled cutoff basically (hard knee). Like I said, no time...
*/
class Compressor :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        size_t attack = 100; // Milliseconds
        size_t release = 100; // Milliseconds
        float threshold = 0.5f; // Linear dB
        size_t ratio = 1; // As 1:ratio
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    Compressor() = default;
    ~Compressor() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        maxiSettings::setup(spec.sampleRate, static_cast<int>(spec.numChannels), static_cast<int>(spec.maximumBlockSize));
        channelStates.resize(spec.numChannels);
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        for (size_t channel = 0; channel < context.getInputBlock().getNumChannels(); ++channel)
        {
            updateParameters();
            const float* sampleRead = context.getInputBlock().getChannelPointer(channel);
            float* sampleWrite = context.getOutputBlock().getChannelPointer(channel);
            for (size_t i = 0; i < context.getInputBlock().getNumSamples(); ++i)
                sampleWrite[i] = channelStates[channel].compressor.compress(sampleRead[i]);
        }
    }

    void reset() noexcept override
    {
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        for (auto& channelState : channelStates)
        {
            channelState.compressor.setAttack(static_cast<double>(params->attack));
            channelState.compressor.setRelease(static_cast<double>(params->release));
            channelState.compressor.setThreshold(static_cast<double>(params->threshold));
            channelState.compressor.setRatio(1.0 / static_cast<double>(params->ratio));
        }
    }

    struct ChannelState
    {
        // TODO: We may need some sort of parameter smoothing...
        maxiDyn compressor;
    };

    std::vector<ChannelState> channelStates;

};
