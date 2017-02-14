/*
Copyright 2016 Colin Girling

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

#ifndef OCL_GUARD_DATETIME_TIME_HPP
#define OCL_GUARD_DATETIME_TIME_HPP

#include <stdint.h>

namespace ocl
{

/*
    24 hour time storing hours, minutes, seconds and milliseconds.
    The time is guaranteed to fit into 4 bytes.
*/
class Time
{
// Types.
public:
    typedef uint32_t size_type;
    typedef int32_t diff_type;
    typedef uint16_t millisecond_type;
    typedef uint8_t second_type;
    typedef uint8_t minute_type;
    typedef uint8_t hour_type;

// Constants.
public:
    static size_type const MILLISECONDS_PER_SECOND = 1000U;
    static size_type const SECONDS_PER_MINUTE = 60U;
    static size_type const MINUTES_PER_HOUR = 60U;
    static size_type const HOURS_PER_DAY = 24U;

    static size_type const MILLISECONDS_PER_MINUTE = MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE;
    static size_type const MILLISECONDS_PER_HOUR = MILLISECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static size_type const MILLISECONDS_PER_DAY = MILLISECONDS_PER_HOUR * HOURS_PER_DAY;

    static size_type const SECONDS_PER_HOUR = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static size_type const SECONDS_PER_DAY = SECONDS_PER_HOUR * HOURS_PER_DAY;

    static size_type const MINUTES_PER_DAY = MINUTES_PER_HOUR * HOURS_PER_DAY;

    static millisecond_type const MAX_MILLISECONDS = 999U;
    static second_type const MAX_SECONDS = 59U;
    static minute_type const MAX_MINUTES = 59U;
    static hour_type const MAX_HOURS = 23U;

// constants (internal use only)
private:
    /// Milliseconds are stored as a 10 bit value, 8 bits in m_milliseconds
    /// and 2 bits in the top 2 bits of m_seconds.
    typedef uint8_t millisecond_internal_type;

    /// Masks for handling m_milliseconds and m_seconds.
    /// m_seconds bottom two bits contain the top two bits of the 10 bits used for milliseconds.
    /// Storing seconds in top 8 bits allows for quick time comparison.
    static second_type const SECONDS_MASK = static_cast<second_type>(0xfc);
    static second_type const MILLISECONDS_FROM_SECONDS_MASK = static_cast<second_type>(0x03);

    /// When milliseconds is the maximum value, the lower 8 bits and
    /// the upper 2 bits will always be the same value, and can be optimized with constants.
    static millisecond_internal_type const MAX_MILLISECONDS_LOW_8_BITS =
                            static_cast<millisecond_internal_type>(MAX_MILLISECONDS & 0xffU);
    static millisecond_internal_type const MAX_MILLISECONDS_HI_BYTE_2_BITS =
            static_cast<second_type>(MAX_MILLISECONDS >> 8U) & MILLISECONDS_FROM_SECONDS_MASK;

// Constructors.
public:
    Time() throw()
        : m_hours(0U)
        , m_minutes(0U)
        , m_seconds(0U)
        , m_milliseconds(0U)
    {
    }

    Time(hour_type hours,         // 0..23
         minute_type minutes,       // 0..59
         second_type seconds,       // 0..59
         millisecond_type milliseconds) throw() // 0..999
    {
        SetTime(hours, minutes, seconds, milliseconds);
    }

    Time(Time const& time) throw()
        : m_hours(time.m_hours)
        , m_minutes(time.m_minutes)
        , m_seconds(time.m_seconds)
        , m_milliseconds(time.m_milliseconds)
    {
    }

// Overloaded operators.
public:
    Time& operator =(Time const& time) throw()
    {
        SetTime(time);
        return *this;
    }

    bool operator <(Time const& other) const throw()
    {
        return IsLess(other);
    }

    bool operator <=(Time const& other) const throw()
    {
        return IsLessEqual(other);
    }

    bool operator >(Time const& other) const throw()
    {
        return IsGreater(other);
    }

    bool operator >=(Time const& other) const throw()
    {
        return IsGreaterEqual(other);
    }

    bool operator ==(Time const& other) const throw()
    {
        return IsEqual(other);
    }

    bool operator !=(Time const& other) const throw()
    {
        return IsNotEqual(other);
    }

    Time& operator +=(uint32_t milliseconds)
    {
        AddMilliseconds(milliseconds);
        return *this;
    }

    Time& operator -=(uint32_t milliseconds)
    {
        SubtractMilliseconds(milliseconds);
        return *this;
    }

    /// Get difference between two times in milliseconds.
    Time operator +(size_type milliseconds) const throw()
    {
        Time time(*this);
        time += milliseconds;
        return time;
    }

    /// Get difference between two times in milliseconds.
    Time operator -(size_type milliseconds) const throw()
    {
        Time time(*this);
        time -= milliseconds;
        return time;
    }

    /// Get difference between two times in milliseconds.
    diff_type operator -(Time const& other) const throw()
    {
        size_type this_millisecds = GetAsMilliseconds();
        size_type other_millisecds = other.GetAsMilliseconds();
        return static_cast<diff_type>(this_millisecds) - static_cast<diff_type>(other_millisecds);
    }

    Time operator ++() throw() // Prefix
    {
        AddMilliseconds(1U);
        return *this;
    }

    Time operator ++(int) throw() // Postfix
    {
        Time time(*this);
        time.AddMilliseconds(1U);
        return time;
    }

    Time operator --() throw() // Prefix
    {
        SubtractMilliseconds(1U);
        return *this;
    }

    Time operator --(int) throw() // Postfix
    {
        Time time(*this);
        time.SubtractMilliseconds(1U);
        return time;
    }

// Static member functions.
public:
    /// Split milliseconds into hours, minutes, seconds and milliseconds.
    static void SplitMilliseconds(size_type& hours,
                                  size_type& minutes,
                                  size_type& seconds,
                                  size_type& milliseconds) throw()
    {
        size_type ms = milliseconds;
        hours = ms / MILLISECONDS_PER_HOUR;
        ms -= hours * MILLISECONDS_PER_HOUR;
        minutes = ms / MILLISECONDS_PER_MINUTE;
        ms -= minutes * MILLISECONDS_PER_MINUTE;
        seconds = ms / MILLISECONDS_PER_SECOND;
        ms -= seconds * MILLISECONDS_PER_SECOND;
        milliseconds = ms;
    }

    /// Convert a time into milliseconds.
    static size_type ToMilliseconds(size_type hours,
                                    size_type minutes,
                                    size_type seconds,
                                    size_type milliseconds) throw()
    {
        uint32_t ms = hours * MILLISECONDS_PER_HOUR;
        ms += minutes * MILLISECONDS_PER_MINUTE;
        ms += seconds * MILLISECONDS_PER_SECOND;
        ms += milliseconds;
        return ms;
    }

// Member functions.
public:
    millisecond_type GetMilliseconds() const throw()
    {
        millisecond_type milliseconds = m_milliseconds;
        milliseconds |= static_cast<millisecond_type>(m_seconds & MILLISECONDS_FROM_SECONDS_MASK) << 8U;

        return milliseconds;
    }

    void SetMilliseconds(millisecond_type milliseconds) throw()
    {
        if (milliseconds > MAX_MILLISECONDS)
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
        if (seconds > MAX_SECONDS)
            m_seconds = static_cast<second_type>(MAX_SECONDS << 2U) | millisecond_bits;
        else
            m_seconds = static_cast<second_type>(seconds << 2U) | millisecond_bits;
    }

    minute_type GetMinutes() const throw()
    {
        return m_minutes;
    }

    void SetMinutes(minute_type minutes) throw()
    {
        m_minutes = minutes > MAX_MINUTES ? MAX_MINUTES : minutes;
    }

    hour_type GetHours() const throw()
    {
        return m_hours;
    }

    void SetHours(hour_type hours) throw()
    {
        m_hours = hours > MAX_HOURS ? MAX_HOURS : hours;
    }

    /// Convert time into a milliseconds value.
    size_type GetAsMilliseconds() const throw()
    {
        return ToMilliseconds(static_cast<size_type>(GetHours()),
                              static_cast<size_type>(GetMinutes()),
                              static_cast<size_type>(GetSeconds()),
                              static_cast<size_type>(GetMilliseconds()));
    }

    /// Convert the milliseconds to a time.
    void SetFromMilliseconds(size_type milliseconds) throw()
    {
        size_type hours = 0;
        size_type minutes = 0;
        size_type seconds = 0;
        SplitMilliseconds(hours, minutes, seconds, milliseconds);
        if (hours > MAX_HOURS)
            hours = MAX_HOURS;
        SetHours(static_cast<hour_type>(hours));
        SetMinutes(static_cast<minute_type>(minutes));
        SetSeconds(static_cast<second_type>(seconds));
        SetMilliseconds(static_cast<millisecond_type>(milliseconds));
    }

    /// Get the difference between this time and the other time in milliseconds.
    size_type GetDifference(Time const& other) const throw()
    {
        size_type this_milliseconds = GetAsMilliseconds();
        size_type other_millisecds = other.GetAsMilliseconds();
        return this_milliseconds > other_millisecds ? this_milliseconds - other_millisecds
                                                    : other_millisecds - this_milliseconds;
    }

    void AddMilliseconds(size_type milliseconds) throw()
    {
        size_type time_ms = GetAsMilliseconds() + milliseconds;
        if (time_ms >= MILLISECONDS_PER_DAY)
            SetFromMilliseconds(MILLISECONDS_PER_DAY - 1U);
        else
            SetFromMilliseconds(time_ms);
    }

    /// Add milliseconds and return any overflow.
    void AddMilliseconds(size_type milliseconds, size_type& overflow) throw()
    {
        size_type time_ms = GetAsMilliseconds() + milliseconds;
        if (time_ms >= MILLISECONDS_PER_DAY)
        {
            overflow = 1U + time_ms - MILLISECONDS_PER_DAY;
            SetFromMilliseconds(MILLISECONDS_PER_DAY - 1U);
        }
        else
        {
            overflow = 0U;
            SetFromMilliseconds(time_ms);
        }
    }

    void SubtractMilliseconds(size_type milliseconds) throw()
    {
        size_type time_ms = GetAsMilliseconds();
        if (milliseconds >= time_ms)
            SetFromMilliseconds(0U);
        else
            SetFromMilliseconds(time_ms - milliseconds);
    }

    void SubtractMilliseconds(size_type milliseconds, size_type& underflow) throw()
    {
        size_type time_ms = GetAsMilliseconds();
        if (milliseconds > time_ms)
        {
            underflow = milliseconds - time_ms;
            SetFromMilliseconds(0U);
        }
        else
        {
            underflow = 0U;
            SetFromMilliseconds(time_ms - milliseconds);
        }
    }

    /// Get the time as a 32-bit value for conveniently serializing the time.
    uint32_t GetTime() const throw()
    {
        uint32_t time = m_milliseconds;
        time |= static_cast<uint32_t>(m_seconds) << 8U;
        time |= static_cast<uint32_t>(m_minutes) << 16U;
        time |= static_cast<uint32_t>(m_hours) << 24U;
        return time;
    }

    /// Set the time from a 32-bit value for conveniently serializing the time.
    void SetTime(uint32_t time) throw()
    {
        m_milliseconds = static_cast<millisecond_internal_type>(time);
        m_seconds = static_cast<second_type>(time >> 8U);
        m_minutes = static_cast<minute_type>(time >> 16U);
        m_hours = static_cast<hour_type>(time >> 24U);
    }

    void SetTime(Time const& time) throw()
    {
        m_hours = time.m_hours;
        m_minutes = time.m_minutes;
        m_seconds = time.m_seconds;
        m_milliseconds = time.m_milliseconds;
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

    bool IsLess(Time const& other) const throw()
    {
        return GetTime() < other.GetTime();
    }

    bool IsLessEqual(Time const& other) const throw()
    {
        return GetTime() <= other.GetTime();
    }

    bool IsGreater(Time const& other) const throw()
    {
        return GetTime() > other.GetTime();
    }

    bool IsGreaterEqual(Time const& other) const throw()
    {
        return GetTime() >= other.GetTime();
    }

    bool IsEqual(Time const& other) const throw()
    {
        return GetTime() == other.GetTime();
    }

    bool IsNotEqual(Time const& other) const throw()
    {
        return GetTime() != other.GetTime();
    }

    /// Return -1 when this time is less than other time, 0 when equal or
    // 1 when this time is greater than other time.
    int Compare(Time const& other) const throw()
    {
        uint32_t t1 = GetTime();
        uint32_t t2 = other.GetTime();
        return t1 > t2 ? 1 : (t1 < t2 ? -1 : 0);
    }

// Data (internal use only)
private:
    hour_type m_hours;                        // 0..23
    minute_type m_minutes;                    // 0..59
    second_type m_seconds;                    // 0..59 (6 - bits)
    millisecond_internal_type m_milliseconds; // 0..999 (8 - bits + 2 bottom bits stored in m_seconds)
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_TIME_HPP
