/*
Copyright 2017 Colin Girling

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef OCL_GUARD_DATETIME_TIMERANGE_HPP
#define OCL_GUARD_DATETIME_TIMERANGE_HPP

#include "Time.hpp"

namespace ocl
{

class TimeRange
{
// Types.
public:
    typedef Time::size_type size_type;
    typedef Time::diff_type diff_type;
    typedef Time::millisecond_type millisecond_type;
    typedef Time::second_type second_type;
    typedef Time::minute_type minute_type;
    typedef Time::hour_type hour_type;

// Constructors.
public:
    // Default to range of 0:0:0.0 to 0:0:0.0.
    TimeRange()
    {
    }

    TimeRange(Time const& start, Time const& stop) throw()
        : m_start(start)
        , m_stop(stop)
    {
    }

    TimeRange(TimeRange const& range)
        : m_start(range.m_start)
        , m_stop(range.m_stop)
    {
    }

// Member functions.
public:
    Time const& GetStart() const throw()
    {
        return m_start;
    }

    void SetStart(Time const& start) throw()
    {
        m_start.SetTime(start);
        m_stop.SetTime(start);
    }

    Time const& GetStop() const throw()
    {
        return m_stop;
    }

    void SetStop(Time const& stop) throw()
    {
        m_stop.SetTime(stop);
    }

    // Set start and stop to 0:0:0.0.
    void ResetToStart() throw()
    {
        m_start.SetStart();
        m_stop.SetStart();
    }

    bool IsWithin(Time const& time) const throw()
    {
        return (time >= m_start) && (time <= m_stop);
    }

    bool IsOverlapped(TimeRange const& other_range) const throw()
    {
        return (m_start <= other_range.m_stop) && (m_stop >= other_range.m_start);
    }

    bool GetOverlap(TimeRange const& other_range, TimeRange& overlap) const throw()
    {
        bool is_overlapped = IsOverlapped(other_range);

        if (is_overlapped)
        {
            overlap.SetStart(Time::Max(m_start, other_range.m_start));
            overlap.SetStop(Time::Min(m_stop, other_range.m_stop));
        }

        return is_overlapped;
    }

    size_type GetRangeInMilliseconds() const throw()
    {
        return m_stop.GetDifferenceInMilliseconds(m_start);
    }

    // Start is expected to be less than or equal to stop, otherwise this considered invalid.
    bool IsValid() const throw()
    {
        return m_start <= m_stop;
    }

// Data (internal use only)
private:
    Time m_start;
    Time m_stop;
};

}

#endif // OCL_GUARD_DATETIME_TIMERANGE_HPP
