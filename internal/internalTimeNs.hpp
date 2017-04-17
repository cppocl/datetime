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

#ifndef OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMENS_HPP
#define OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMENS_HPP

#include "TimeDefines.hpp"
#include "TimePrecision.hpp"
#include <cstdint>

namespace ocl
{

/// Defines the bare essentials required to complete Time class.
class InternalTimeNs : public TimeDefines
{
// Types.
public:
    typedef nanosecond_size_type size_type;
    typedef nanosecond_diff_type diff_type;
    typedef std::uint64_t        serialize_type;
    typedef nanosecond_type      smallest_unit_type;

// Constants.
public:
    // Provide easy means for Time class to identify the precision is more accurate than a second.
    static bool const HAS_PARTIAL_SECONDS = true;

    static TimePrecision const        PRECISION        = Nanoseconds;
    static nanosecond_size_type const UNITS_PER_SECOND = NANOSECONDS_PER_SECOND;
    static nanosecond_size_type const UNITS_PER_MINUTE = NANOSECONDS_PER_MINUTE;
    static nanosecond_size_type const UNITS_PER_HOUR   = NANOSECONDS_PER_HOUR;
    static nanosecond_size_type const UNITS_PER_DAY    = NANOSECONDS_PER_DAY;

// Member functions.
public:

// Constructors.
public:
    InternalTimeNs() throw()
        : m_hours(0U)
        , m_minutes(0U)
        , m_seconds(0U)
        , m_nanoseconds(0U)
    {
    }

    InternalTimeNs(hour_type hours,             // 0..23
                   minute_type minutes) throw() // 0..59
        : m_seconds(0U)
        , m_nanoseconds(0U)
    {
        // Let these functions handle the combining of the bits and range limiting.
        SetHours(hours);
        SetMinutes(minutes);
    }

    InternalTimeNs(hour_type hours,             // 0..23
                   minute_type minutes,         // 0..59
                   second_type seconds) throw() // 0..59
        : m_nanoseconds(0U)
    {
        // Let these functions handle the combining of the bits and range limiting.
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(seconds);
    }

    InternalTimeNs(hour_type hours,                     // 0..23
                   minute_type minutes,                 // 0..59
                   second_type seconds,                 // 0..59
                   nanosecond_type nanoseconds) throw() // 0..999999999
    {
        // Let these functions handle the combining of the bits and range limiting.
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(seconds);
        SetNanoseconds(nanoseconds);
    }

    InternalTimeNs(InternalTimeNs const& time_ns) throw()
        : m_hours(time_ns.m_hours)
        , m_minutes(time_ns.m_minutes)
        , m_seconds(time_ns.m_seconds)
        , m_nanoseconds(time_ns.m_nanoseconds)
    {
    }

    ~InternalTimeNs() throw()
    {
    }

// Static member functions.
public:
    /// Split nanoseconds into hours, minutes, seconds and milliseconds.
    static void Split(size_type total_nanoseconds,
                      size_type& hours,
                      size_type& minutes,
                      size_type& seconds,
                      size_type& nanoseconds) throw()
    {
        hours = total_nanoseconds / NANOSECONDS_PER_HOUR;
        total_nanoseconds -= hours * NANOSECONDS_PER_HOUR;
        minutes = total_nanoseconds / NANOSECONDS_PER_MINUTE;
        total_nanoseconds -= minutes * NANOSECONDS_PER_MINUTE;
        seconds = total_nanoseconds / NANOSECONDS_PER_SECOND;
        total_nanoseconds -= seconds * NANOSECONDS_PER_SECOND;
        nanoseconds = total_nanoseconds;
    }

    /// Convert a time into nanoseconds.
    static size_type Merge(size_type hours,
                           size_type minutes,
                           size_type seconds,
                           size_type nanoseconds) throw()
    {
        size_type ns = hours * NANOSECONDS_PER_HOUR;
        ns += minutes * NANOSECONDS_PER_MINUTE;
        ns += seconds * NANOSECONDS_PER_SECOND;
        ns += nanoseconds;
        return ns;
    }

// Member functions.
public:
    nanosecond_type GetNanoseconds() const throw()
    {
        return m_nanoseconds;
    }

    void SetNanoseconds(nanosecond_type nanoseconds) throw()
    {
        m_nanoseconds = nanoseconds > NANOSECONDS_UPPER_BOUND ? NANOSECONDS_UPPER_BOUND : nanoseconds;
    }

    millisecond_type GetMilliseconds() const throw()
    {
        return static_cast<millisecond_type>(
                    GetNanoseconds() / TimeDefines::NANOSECONDS_PER_MILLISECOND);
    }

    void SetMilliseconds(millisecond_type milliseconds) throw()
    {
        SetNanoseconds(TimeDefines::NANOSECONDS_PER_MILLISECOND * milliseconds);
    }

    second_type GetSeconds() const throw()
    {
        return m_seconds;
    }

    void SetSeconds(second_type seconds) throw()
    {
        m_seconds = seconds > SECONDS_UPPER_BOUND ? SECONDS_UPPER_BOUND : seconds;
    }

    minute_type GetMinutes() const throw()
    {
        return m_minutes;
    }

    void SetMinutes(minute_type minutes) throw()
    {
        m_minutes = minutes > MINUTES_UPPER_BOUND ? MINUTES_UPPER_BOUND : minutes;
    }

    hour_type GetHours() const throw()
    {
        return m_hours;
    }

    void SetHours(hour_type hours) throw()
    {
        m_hours = hours > HOURS_UPPER_BOUND ? HOURS_UPPER_BOUND : hours;
    }

    void GetTime(hour_type& hours,
                 minute_type& minutes,
                 second_type& seconds,
                 nanosecond_type& nanoseconds) throw()
    {
        hours = GetHours();
        minutes = GetMinutes();
        seconds = GetSeconds();
        nanoseconds = GetNanoseconds();
    }

    void SetTime(hour_type hours,
                 minute_type minutes,
                 second_type seconds,
                 nanosecond_type nanoseconds) throw()
    {
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(seconds);
        SetNanoseconds(nanoseconds);
    }

    /// Transform time into a milliseconds value.
    /// 0:0:0.0 would returned as 0.
    size_type Transform() const throw()
    {
        return Merge(static_cast<size_type>(GetHours()),
                     static_cast<size_type>(GetMinutes()),
                     static_cast<size_type>(GetSeconds()),
                     static_cast<size_type>(GetNanoseconds()));
    }

    /// Transform the milliseconds to a time.
    /// 0 would set the time to 0:0:0.0.
    void Transform(size_type nanoseconds) throw()
    {
        size_type hours = 0;
        size_type minutes = 0;
        size_type seconds = 0;
        Split(nanoseconds, hours, minutes, seconds, nanoseconds);
        if (hours > HOURS_UPPER_BOUND)
            hours = HOURS_UPPER_BOUND;
        SetHours(static_cast<hour_type>(hours));
        SetMinutes(static_cast<minute_type>(minutes));
        SetSeconds(static_cast<second_type>(seconds));
        SetNanoseconds(static_cast<nanosecond_type>(nanoseconds));
    }

    /// Get the time as a 64-bit value for conveniently serializing the time.
    /// Earlier time is always returned as a lower value.
    serialize_type Serialize() const throw()
    {
        serialize_type serialize_time = m_nanoseconds;
        serialize_time |= static_cast<serialize_type>(m_seconds) << 32U;
        serialize_time |= static_cast<serialize_type>(m_minutes) << 40U;
        serialize_time |= static_cast<serialize_type>(m_hours) << 48U;
        return serialize_time;
    }

    /// Set the time from a 64-bit value for conveniently serializing the time.
    /// Format of serialized_time will be in the same format returned from Serialize.
    void Deserialize(serialize_type serialized_time) throw()
    {
        m_nanoseconds = static_cast<nanosecond_type>(serialized_time);
        m_seconds = static_cast<second_type>(serialized_time >> 32U);
        m_minutes = static_cast<minute_type>(serialized_time >> 40U);
        m_hours = static_cast<hour_type>(serialized_time >> 48U);
    }

    void Copy(InternalTimeNs const& other) throw()
    {
        m_hours       = other.m_hours;
        m_minutes     = other.m_minutes;
        m_seconds     = other.m_seconds;
        m_nanoseconds = other.m_nanoseconds;
    }

    void Swap(InternalTimeNs& other) throw()
    {
        hour_type other_hours = other.m_hours;
        minute_type other_minutes = other.m_minutes;
        second_type other_seconds = other.m_seconds;
        nanosecond_type other_nanoseconds = other.m_nanoseconds;

        other.m_hours = m_hours;
        other.m_minutes = m_minutes;
        other.m_seconds = m_seconds;
        other.m_nanoseconds = m_nanoseconds;

        m_hours = other_hours;
        m_minutes = other_minutes;
        m_seconds = other_seconds;
        m_nanoseconds = other_nanoseconds;
    }

    void SetStart() throw()
    {
        SetHours(0U);
        SetMinutes(0U);
        SetSeconds(0U);
        SetNanoseconds(0U);
    }

    void SetEnd() throw()
    {
        SetHours(HOURS_UPPER_BOUND);
        SetMinutes(MINUTES_UPPER_BOUND);
        SetSeconds(SECONDS_UPPER_BOUND);
        SetNanoseconds(NANOSECONDS_UPPER_BOUND);
    }

// Data (internal use only)
private:
    hour_type m_hours;             // 0..23
    minute_type m_minutes;         // 0..59
    second_type m_seconds;         // 0..59
    nanosecond_type m_nanoseconds; // 0..999999999
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMENS_HPP
