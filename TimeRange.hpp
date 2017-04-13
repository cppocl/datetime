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

template<TimePrecision precision>
class TimeRange
{
// Types.
public:
    typedef Time<precision> time_type;
    typedef typename time_type::size_type size_type;
    typedef typename time_type::diff_type diff_type;
    typedef typename time_type::millisecond_type millisecond_type;
    typedef typename time_type::second_type second_type;
    typedef typename time_type::minute_type minute_type;
    typedef typename time_type::hour_type hour_type;

// Constructors.
public:
    // Default to range of 0:0:0.0 to 0:0:0.0.
    TimeRange()
    {
    }

    TimeRange(time_type const& start, time_type const& stop) throw()
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
    time_type const& GetStart() const throw()
    {
        return m_start;
    }

    void SetStart(time_type const& start) throw()
    {
        m_start.Copy(start);
    }

    time_type const& GetStop() const throw()
    {
        return m_stop;
    }

    void SetStop(time_type const& stop) throw()
    {
        m_stop.Copy(stop);
    }

    // Set start and stop to 0:0:0.0.
    void ResetToStart() throw()
    {
        m_start.SetStart();
        m_stop.SetStart();
    }

    bool IsWithin(time_type const& time) const throw()
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
            overlap.SetStart(time_type::Max(m_start, other_range.m_start));
            overlap.SetStop(time_type::Min(m_stop, other_range.m_stop));
        }

        return is_overlapped;
    }

    /// Get the difference between start and stop, expecting start to be less or equal to stop.
    size_type GetRange() const throw()
    {
        return m_start.GetDifference(m_stop);
    }

    // Start is expected to be less than or equal to stop, otherwise this considered invalid.
    bool IsValid() const throw()
    {
        return m_start <= m_stop;
    }

// Data (internal use only)
private:
    time_type m_start;
    time_type m_stop;
};

}

#endif // OCL_GUARD_DATETIME_TIMERANGE_HPP
