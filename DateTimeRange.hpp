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

#ifndef OCL_GUARD_DATETIME_DATETIMERANGE_HPP
#define OCL_GUARD_DATETIME_DATETIMERANGE_HPP

#include "DateTime.hpp"

namespace ocl
{

class DateTimeRange
{
// Types.
public:
    typedef DateTime::size_type size_type;
    typedef DateTime::diff_type diff_type;
    typedef DateTime::day_type day_type;
    typedef DateTime::day_of_week_type day_of_week_type;
    typedef DateTime::month_type month_type;
    typedef DateTime::year_type year_type;

// Constructors.
public:
    // Default to range of 0:0:0.0 to 0:0:0.0.
    DateTimeRange()
    {
    }

    DateTimeRange(DateTime const& start, DateTime const& stop) throw()
        : m_start(start)
        , m_stop(stop)
    {
    }

    DateTimeRange(DateTimeRange const& range)
        : m_start(range.m_start)
        , m_stop(range.m_stop)
    {
    }

// Member functions.
public:
    DateTime const& GetStart() const throw()
    {
        return m_start;
    }

    void SetStart(DateTime const& start) throw()
    {
        m_start.SetDateTime(start);
    }

    DateTime const& GetStop() const throw()
    {
        return m_stop;
    }

    void SetStop(DateTime const& stop) throw()
    {
        m_stop.SetDateTime(stop);
    }

    bool IsWithin(DateTime const& date) const throw()
    {
        return (date >= m_start) && (date <= m_stop);
    }

    bool IsOverlapped(DateTimeRange const& other_range) const throw()
    {
        return (m_start <= other_range.m_stop) && (m_stop >= other_range.m_start);
    }

    bool GetOverlap(DateTimeRange const& other_range, DateTimeRange& overlap) const throw()
    {
        bool is_overlapped = IsOverlapped(other_range);

        if (is_overlapped)
        {
            overlap.SetStart(DateTime::Max(m_start, other_range.m_start));
            overlap.SetStop(DateTime::Min(m_stop, other_range.m_stop));
        }

        return is_overlapped;
    }

    void GetDifference(size_type& days, size_type& milliseconds) const throw()
    {
        m_start.GetDifference(m_stop, days, milliseconds);
    }

    template<typename return_type>
    void GetDifference(return_type& milliseconds) const throw()
    {
        m_start.GetDifference<return_type>(m_stop, milliseconds);
    }


    // Start is expected to be less than or equal to stop, otherwise this considered invalid.
    bool IsValid() const throw()
    {
        return m_start <= m_stop;
    }

// Data (internal use only)
private:
    DateTime m_start;
    DateTime m_stop;
};

}

#endif // OCL_GUARD_DATETIME_DATETIMERANGE_HPP
