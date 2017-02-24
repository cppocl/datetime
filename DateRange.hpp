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

#ifndef OCL_GUARD_DATETIME_DATERANGE_HPP
#define OCL_GUARD_DATETIME_DATERANGE_HPP

#include "Date.hpp"

namespace ocl
{

class DateRange
{
// Types.
public:
    typedef Date::size_type size_type;
    typedef Date::diff_type diff_type;
    typedef Date::day_type day_type;
    typedef Date::day_of_week_type day_of_week_type;
    typedef Date::month_type month_type;
    typedef Date::year_type year_type;

// Constructors.
public:
    // Default to range of 0:0:0.0 to 0:0:0.0.
    DateRange()
    {
    }

    DateRange(Date const& start, Date const& stop) throw()
        : m_start(start)
        , m_stop(stop)
    {
    }

    DateRange(DateRange const& range)
        : m_start(range.m_start)
        , m_stop(range.m_stop)
    {
    }

// Member functions.
public:
    Date const& GetStart() const throw()
    {
        return m_start;
    }

    void SetStart(Date const& start) throw()
    {
        m_start.SetDate(start);
    }

    Date const& GetStop() const throw()
    {
        return m_stop;
    }

    void SetStop(Date const& stop) throw()
    {
        m_stop.SetDate(stop);
    }

    bool IsWithin(Date const& date) const throw()
    {
        return (date >= m_start) && (date <= m_stop);
    }

    bool IsOverlapped(DateRange const& other_range) const throw()
    {
        return (m_start <= other_range.m_stop) && (m_stop >= other_range.m_start);
    }

    bool GetOverlap(DateRange const& other_range, DateRange& overlap) const throw()
    {
        bool is_overlapped = IsOverlapped(other_range);

        if (is_overlapped)
        {
            overlap.SetStart(Date::Max(m_start, other_range.m_start));
            overlap.SetStop(Date::Min(m_stop, other_range.m_stop));
        }

        return is_overlapped;
    }

    size_type GetRangeInDays() const throw()
    {
        return m_stop.GetDifferenceInDays(m_start);
    }

    // Start is expected to be less than or equal to stop, otherwise this considered invalid.
    bool IsValid() const throw()
    {
        return m_start <= m_stop;
    }

// Data (internal use only)
private:
    Date m_start;
    Date m_stop;
};

}

#endif // OCL_GUARD_DATETIME_DATERANGE_HPP
