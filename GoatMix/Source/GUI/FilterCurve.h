/*
  ==============================================================================

    FilterCurve.h
    Created: 29 Nov 2017 2:11:16am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

/*
#include "JuceHeader.h"
#include "../DSP/GMIIRFilter.h"
#include "../DSP/LogMap.h"
#include <unordered_map>
#include <vector>

class FilterCurve :
    public Component
{
public:
    FilterCurve() = default;
    FilterCurve(Range<float> _frequencyRange) :
        frequencyRange(_frequencyRange) {}
    ~FilterCurve() = default;

    void addFilter(GMIIRFilter* filter) noexcept
    {
        for (auto& _filter : filters)
            if (_filter == filter)
                return;

        filters.push_back(filter);
    }

    int getNumPoints() const noexcept
    {
        return numPoints;
    }

    void setNumPoints(int _numPoints)
    {
        numPoints = _numPoints;
        filterCache.clear();
    }

    Range<float> getFrequencyRange() const noexcept
    {
        return frequencyRange;
    }

    void setFrequencyRange(Range<float> _frequencyRange)
    {
        frequencyRange = _frequencyRange;
        filterCache.clear();
    }

private:
    void resized() noexcept override
    {
    }

    void paint(Graphics& g) noexcept override
    {
        LogMap map(frequencyRange);

    }

    void generateFrequenciesToDisplay() noexcept
    {
        displayFrequencies.clear();
        displayFrequencies.reserve(static_cast<size_t>(numPoints));
    }

    namespace std
    {
        template <>
        struct hash<dsp::IIR::Coefficients<float>::Ptr>
        {
            size_t operator()(dsp::IIR::Coefficients<float>::Ptr k) const
            {
                return reinterpret_cast<size_t>(k.get());
            }
        };
    }

    std::vector<float> displayFrequencies;
    std::vector<WeakReference<GMIIRFilter>> filters;
    std::unordered_map<dsp::IIR::Coefficients<float>::Ptr, std::vector<float>> filterCache;
    Range<float> frequencyRange;
    int numPoints;
};
 */
