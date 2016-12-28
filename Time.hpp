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

#include <cstddef>

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
    typedef uint16_t millisecond_type;
    typedef uint8_t second_type;
    typedef uint8_t minute_type;
    typedef uint8_t hour_type;

// Constants.
public:
    static size_type const MILLISECONDS_PER_SECOND = 1000;
    static size_type const SECONDS_PER_MINUTE = 60;
    static size_type const MINUTES_PER_HOUR = 60;
    static size_type const HOURS_PER_DAY = 24;

    static size_type const MILLISECONDS_PER_MINUTE = MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE;
    static size_type const MILLISECONDS_PER_HOUR = MILLISECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static size_type const MILLISECONDS_PER_DAY = MILLISECONDS_PER_HOUR * HOURS_PER_DAY;

    static size_type const SECONDS_PER_HOUR = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static size_type const SECONDS_PER_DAY = SECONDS_PER_HOUR * HOURS_PER_DAY;

    static size_type const MINUTES_PER_DAY = MINUTES_PER_HOUR * HOURS_PER_DAY;

// constants (internal use only)
private:
    // Milliseconds are stored as a 10 bit value, 8 bits in m_milliseconds
    // and 2 bits in the top 2 bits of m_seconds.
    typedef uint8_t millisecond_internal_type;

    // Masks for handling m_milliseconds and m_seconds.
    // m_seconds bottom two bits contain the top two bits of the 10 bits used for milliseconds.
    // Storing seconds in top 8 bits allows for quick time comparison.
    static second_type const SECONDS_MASK = static_cast<second_type>(0xfc);
    static second_type const MILLISECONDS_FROM_SECONDS_MASK = static_cast<second_type>(0x03);

// Constructors.
public:
    Time()
        : m_hours(0)
        , m_minutes(0)
        , m_seconds(0)
        , m_milliseconds(0)
    {
    }

    Time(hour_type hours,         // 0..23
         minute_type minutes,       // 0..59
         second_type seconds,       // 0..59
         millisecond_type milliseconds) // 0..999
        : m_hours(hours)
        , m_minutes(minutes)
    {
        SetSeconds(seconds);
        SetMilliseconds(milliseconds);
    }

    Time(Time const& time)
        : m_hours(time.m_hours)
        , m_minutes(time.m_minutes)
        , m_seconds(time.m_seconds)
        , m_milliseconds(time.m_milliseconds)
    {
    }

// Overloaded operators.
public:
    Time& operator =(Time const& time)
    {
        m_hours = time.m_hours;
        m_minutes = time.m_minutes;
        m_seconds = time.m_seconds;
        m_milliseconds = time.m_milliseconds;
        return *this;
    }

    bool operator <(Time const& time) const throw()
    {
        return Compare(time) < 0;
    }

    bool operator <=(Time const& time) const throw()
    {
        return Compare(time) <= 0;
    }

    bool operator >(Time const& time) const throw()
    {
        return Compare(time) > 0;
    }

    bool operator >=(Time const& time) const throw()
    {
        return Compare(time) >= 0;
    }

    bool operator ==(Time const& time) const throw()
    {
        return Compare(time) == 0;
    }

    bool operator !=(Time const& time) const throw()
    {
        return Compare(time) != 0;
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
        second_type seconds = m_seconds & SECONDS_MASK;
        m_milliseconds = static_cast<millisecond_internal_type>(milliseconds);
        m_seconds = seconds | (static_cast<second_type>(milliseconds >> 8U) & MILLISECONDS_FROM_SECONDS_MASK);
    }

    second_type GetSeconds() const throw()
    {
        return static_cast<second_type>(m_seconds >> 2U);
    }

    void SetSeconds(second_type seconds) throw()
    {
        second_type millisecond_bits = m_seconds & MILLISECONDS_FROM_SECONDS_MASK;
        m_seconds = static_cast<second_type>(seconds << 2U) | millisecond_bits;
    }

    minute_type GetMinutes() const throw()
    {
        return m_minutes;
    }

    void SetMinutes(minute_type minutes) throw()
    {
        m_minutes = minutes;
    }

    hour_type GetHours() const throw()
    {
        return m_hours;
    }

    void SetHours(hour_type hours) throw()
    {
        m_hours = hours;
    }

    // Get the time as a 32-bit value for conveniently serializing the time.
    uint32_t GetTime() const throw()
    {
        uint32_t time = m_milliseconds;
        time |= static_cast<uint32_t>(m_seconds) << 8U;
        time |= static_cast<uint32_t>(m_minutes) << 16U;
        time |= static_cast<uint32_t>(m_hours) << 24U;
        return time;
    }

    // Set the time from a 32-bit value for conveniently serializing the time.
    void SetTime(uint32_t time) throw()
    {
        m_milliseconds = static_cast<millisecond_internal_type>(time);
        m_seconds = static_cast<second_type>(time >> 8U);
        m_minutes = static_cast<minute_type>(time >> 16U);
        m_hours = static_cast<hour_type>(time >> 24U);
    }

    int Compare(Time const& time) const throw()
    {
        uint32_t t1 = GetTime();
        uint32_t t2 = time.GetTime();
        return t1 > t2 ? 1 : (t1 < t2 ? -1 : 0);
    }

// Data (internal use only)
private:
    hour_type m_hours;        // 0..23
    minute_type m_minutes;      // 0..59
    second_type m_seconds;      // 0..59 (6 - bits)
    millisecond_internal_type m_milliseconds; // 0..999 (8 - bits + 2 top bits stored in m_seconds)
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_TIME_HPP
