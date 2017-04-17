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

#ifndef OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEMS_HPP
#define OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEMS_HPP

#include "TimeDefines.hpp"
#include "TimePrecision.hpp"
#include <cstdint>

namespace ocl
{

/// Defines the bare essentials required to complete Time class.
class InternalTimeMs : public TimeDefines
{
// Types.
public:
    typedef millisecond_size_type size_type;
    typedef millisecond_diff_type diff_type;
    typedef std::uint32_t         serialize_type;
    typedef millisecond_type      smallest_unit_type;

// Constants.
public:
    // Provide easy means for Time class to identify the precision is more accurate than a second.
    static bool const HAS_PARTIAL_SECONDS = true;

    static TimePrecision const         PRECISION        = Milliseconds;
    static millisecond_size_type const UNITS_PER_SECOND = MILLISECONDS_PER_SECOND;
    static millisecond_size_type const UNITS_PER_MINUTE = MILLISECONDS_PER_MINUTE;
    static millisecond_size_type const UNITS_PER_HOUR   = MILLISECONDS_PER_HOUR;
    static millisecond_size_type const UNITS_PER_DAY    = MILLISECONDS_PER_DAY;

// Constructors.
public:
    InternalTimeMs() throw()
        : m_hours(0U)
        , m_minutes(0U)
        , m_seconds(0U)
        , m_milliseconds(0U)
    {
    }

    InternalTimeMs(hour_type hours,             // 0..23
                   minute_type minutes) throw() // 0..59
    {
        // Let these functions handle the combining of the bits and range limiting.
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(0U);
        SetMilliseconds(0U);
    }

    InternalTimeMs(hour_type hours,             // 0..23
                   minute_type minutes,         // 0..59
                   second_type seconds) throw() // 0..59
    {
        // Let these functions handle the combining of the bits and range limiting.
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(seconds);
        SetMilliseconds(0U);
    }

    InternalTimeMs(hour_type hours,                       // 0..23
                   minute_type minutes,                   // 0..59
                   second_type seconds,                   // 0..59
                   millisecond_type milliseconds) throw() // 0..999
    {
        // Let these functions handle the combining of the bits and range limiting.
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(seconds);
        SetMilliseconds(milliseconds);
    }

    InternalTimeMs(InternalTimeMs const& time_ms) throw()
        : m_hours(time_ms.m_hours)
        , m_minutes(time_ms.m_minutes)
        , m_seconds(time_ms.m_seconds)
        , m_milliseconds(time_ms.m_milliseconds)
    {
    }

    ~InternalTimeMs() throw()
    {
    }

// Static member functions.
public:
    /// Split milliseconds into hours, minutes, seconds and milliseconds.
    static void Split(size_type total_milliseconds,
                      size_type& hours,
                      size_type& minutes,
                      size_type& seconds,
                      size_type& milliseconds) throw()
    {
        hours = total_milliseconds / MILLISECONDS_PER_HOUR;
        total_milliseconds -= hours * MILLISECONDS_PER_HOUR;
        minutes = total_milliseconds / MILLISECONDS_PER_MINUTE;
        total_milliseconds -= minutes * MILLISECONDS_PER_MINUTE;
        seconds = total_milliseconds / MILLISECONDS_PER_SECOND;
        total_milliseconds -= seconds * MILLISECONDS_PER_SECOND;
        milliseconds = total_milliseconds;
    }

    /// Convert a time into milliseconds.
    static size_type Merge(size_type hours,
                           size_type minutes,
                           size_type seconds,
                           size_type milliseconds) throw()
    {
        size_type ms = hours * MILLISECONDS_PER_HOUR;
        ms += minutes * MILLISECONDS_PER_MINUTE;
        ms += seconds * MILLISECONDS_PER_SECOND;
        ms += milliseconds;
        return ms;
    }

// Member functions.
public:
    nanosecond_type GetNanoseconds() const throw()
    {
        return GetMilliseconds() * TimeDefines::NANOSECONDS_PER_MILLISECOND;
    }

    void SetNanoseconds(nanosecond_type nanoseconds) throw()
    {
        SetMilliseconds(static_cast<millisecond_type>(
                    nanoseconds / TimeDefines::NANOSECONDS_PER_MILLISECOND));
    }

    millisecond_type GetMilliseconds() const throw()
    {
        millisecond_type milliseconds = m_milliseconds;
        milliseconds |= static_cast<millisecond_type>(m_seconds & MILLISECONDS_FROM_SECONDS_MASK) << 8U;

        return milliseconds;
    }

    void SetMilliseconds(millisecond_type milliseconds) throw()
    {
        if (milliseconds > MILLISECONDS_UPPER_BOUND)
        {
            m_milliseconds = MAX_MILLISECONDS_LOW_8_BITS;
            m_seconds |= MAX_MILLISECONDS_HI_BYTE_2_BITS;
        }
        else
        {
            second_type seconds = m_seconds & SECONDS_MASK;
            m_milliseconds = static_cast<millisecond_internal_type>(milliseconds);
            m_seconds = seconds | (static_cast<second_type>(milliseconds >> 8U) & MILLISECONDS_FROM_SECONDS_MASK);
        }
    }

    second_type GetSeconds() const throw()
    {
        return static_cast<second_type>(m_seconds >> 2U);
    }

    void SetSeconds(second_type seconds) throw()
    {
        second_type millisecond_bits = m_seconds & MILLISECONDS_FROM_SECONDS_MASK;
        if (seconds > SECONDS_UPPER_BOUND)
            m_seconds = static_cast<second_type>(SECONDS_UPPER_BOUND << 2U) | millisecond_bits;
        else
            m_seconds = static_cast<second_type>(seconds << 2U) | millisecond_bits;
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
                 millisecond_type& milliseconds) throw()
    {
        hours = GetHours();
        minutes = GetMinutes();
        seconds = GetSeconds();
        milliseconds = GetMilliseconds();
    }

    void SetTime(hour_type hours,
                 minute_type minutes,
                 second_type seconds,
                 millisecond_type milliseconds) throw()
    {
        SetHours(hours);
        SetMinutes(minutes);
        SetSeconds(seconds);
        SetMilliseconds(milliseconds);
    }

    /// Transform time into a milliseconds value.
    /// 0:0:0.0 would returned as 0.
    size_type Transform() const throw()
    {
        return Merge(static_cast<size_type>(GetHours()),
                     static_cast<size_type>(GetMinutes()),
                     static_cast<size_type>(GetSeconds()),
                     static_cast<size_type>(GetMilliseconds()));
    }

    /// Transform the milliseconds to a time.
    /// 0 would set the time to 0:0:0.0.
    void Transform(size_type milliseconds) throw()
    {
        size_type hours = 0;
        size_type minutes = 0;
        size_type seconds = 0;
        Split(milliseconds, hours, minutes, seconds, milliseconds);
        if (hours > HOURS_UPPER_BOUND)
            hours = HOURS_UPPER_BOUND;
        SetHours(static_cast<hour_type>(hours));
        SetMinutes(static_cast<minute_type>(minutes));
        SetSeconds(static_cast<second_type>(seconds));
        SetMilliseconds(static_cast<millisecond_type>(milliseconds));
    }

    /// Get the time as a 32-bit value for conveniently serializing the time.
    /// Earlier time is always returned as a lower value.
    serialize_type Serialize() const throw()
    {
        serialize_type serialize_time = m_milliseconds;
        serialize_time |= static_cast<serialize_type>(m_seconds) << 8U;
        serialize_time |= static_cast<serialize_type>(m_minutes) << 16U;
        serialize_time |= static_cast<serialize_type>(m_hours) << 24U;
        return serialize_time;
    }

    /// Set the time from a 32-bit value for conveniently serializing the time.
    /// Format of serialized_time will be in the same format returned from Serialize.
    void Deserialize(serialize_type serialized_time) throw()
    {
        m_milliseconds = static_cast<millisecond_internal_type>(serialized_time);
        m_seconds = static_cast<second_type>(serialized_time >> 8U);
        m_minutes = static_cast<minute_type>(serialized_time >> 16U);
        m_hours = static_cast<hour_type>(serialized_time >> 24U);
    }

    void Copy(InternalTimeMs const& other) throw()
    {
        m_hours        = other.m_hours;
        m_minutes      = other.m_minutes;
        m_seconds      = other.m_seconds;
        m_milliseconds = other.m_milliseconds;
    }

    void Swap(InternalTimeMs& other) throw()
    {
        hour_type other_hours = other.m_hours;
        minute_type other_minutes = other.m_minutes;
        second_type other_seconds = other.m_seconds;
        millisecond_internal_type other_milliseconds = other.m_milliseconds;

        other.m_hours = m_hours;
        other.m_minutes = m_minutes;
        other.m_seconds = m_seconds;
        other.m_milliseconds = m_milliseconds;

        m_hours = other_hours;
        m_minutes = other_minutes;
        m_seconds = other_seconds;
        m_milliseconds = other_milliseconds;
    }

    void SetStart() throw()
    {
        SetHours(0U);
        SetMinutes(0U);
        SetSeconds(0U);
        SetMilliseconds(0U);
    }

    void SetEnd() throw()
    {
        SetHours(HOURS_UPPER_BOUND);
        SetMinutes(MINUTES_UPPER_BOUND);
        SetSeconds(SECONDS_UPPER_BOUND);
        SetMilliseconds(MILLISECONDS_UPPER_BOUND);
    }

// constants (internal use only)
private:
    /// Milliseconds are stored as a 10 bit value, 8 bits in m_milliseconds
    /// and 2 bits in the top 2 bits of m_seconds.
    typedef std::uint8_t millisecond_internal_type;

    /// Masks for handling m_milliseconds and m_seconds.
    /// m_seconds bottom two bits contain the top two bits of the 10 bits used for milliseconds.
    /// Storing seconds in top 8 bits allows for quick time comparison.
    static second_type const SECONDS_MASK = static_cast<second_type>(0xfc);
    static second_type const MILLISECONDS_FROM_SECONDS_MASK = static_cast<second_type>(0x03);

    /// When milliseconds is the maximum value, the lower 8 bits and
    /// the upper 2 bits will always be the same value, and can be optimized with constants.
    static millisecond_internal_type const MAX_MILLISECONDS_LOW_8_BITS =
                            static_cast<millisecond_internal_type>(MILLISECONDS_UPPER_BOUND & 0xffU);
    static millisecond_internal_type const MAX_MILLISECONDS_HI_BYTE_2_BITS =
            static_cast<second_type>(MILLISECONDS_UPPER_BOUND >> 8U) & MILLISECONDS_FROM_SECONDS_MASK;

// Data (internal use only)
private:
    hour_type m_hours;                        // 0..23
    minute_type m_minutes;                    // 0..59
    second_type m_seconds;                    // 0..59 (6 - bits)
    millisecond_internal_type m_milliseconds; // 0..999 (8 - bits + 2 bottom bits stored in m_seconds)
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEMS_HPP
