/*
  ==============================================================================

    LogMap.h
    Created: 27 Nov 2017 4:27:24pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

class LogMap
{
public:
    LogMap() noexcept = default;

    LogMap(Range<float> logRange) noexcept
    {
        setLogRange(logRange);
    }

    ~LogMap() noexcept = default;

    Range<float> getLogRange() const noexcept
    {
        return logRange;
    }

    void setLogRange(Range<float> _logRange) noexcept
    {
        jassert(_logRange.getLength() > 0.0f);
        logRange = _logRange;
    }

    float linToLog(float linearValue) const noexcept
    {
        // Position within the octave range of our log range.
        float logValue = logRange.getStart() * std::exp(linearValue * numDecades());
        return jlimit(logRange.getStart(), logRange.getEnd(), logValue);
    }

    float logToLin(float logValue) const noexcept
    {
        float decade = std::log(logValue / logRange.getStart());
        float linValue = decade / numDecades();
        return jlimit(0.0f, 1.0f, linValue);
    }

private:
    float numDecades() const noexcept
    {
        return std::log(logRange.getEnd() / logRange.getStart());
    }

    Range<float> logRange;
};
