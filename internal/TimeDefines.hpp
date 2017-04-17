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

#ifndef OCL_GUARD_DATETIME_INTERNAL_TIMEDEFINES_HPP
#define OCL_GUARD_DATETIME_INTERNAL_TIMEDEFINES_HPP

#include <cstdint>

namespace ocl
{

class TimeDefines
{
// Types.
public:
    // Size types when converting into values larger than the limit
    // stored within a time period.
    typedef std::uint64_t nanosecond_size_type;
    typedef std::int64_t  nanosecond_diff_type;
    typedef std::uint64_t microsecond_size_type;
    typedef std::int64_t  microsecond_diff_type;
    typedef std::uint32_t millisecond_size_type;
    typedef std::int32_t  millisecond_diff_type;
    typedef std::uint32_t second_size_type;
    typedef std::int32_t  second_diff_type;
    typedef std::uint32_t minute_size_type;
    typedef std::int32_t  minute_diff_type;
    typedef std::uint32_t hour_size_type;
    typedef std::int32_t  hour_diff_type;

    /// Types for hours, minutes, seconds, milliseconds and nanoseconds,
    // that don't exceed their limit within a time period.
    typedef std::uint32_t nanosecond_type;
    typedef std::uint32_t microsecond_type;
    typedef std::uint16_t millisecond_type;
    typedef std::uint8_t second_type;
    typedef std::uint8_t minute_type;
    typedef std::uint8_t hour_type;

// Constants.
public:
    static hour_type const             HOURS_PER_DAY                = 24U;

    static minute_type const           MINUTES_PER_HOUR             = 60U;
    static minute_size_type const      MINUTES_PER_DAY              = MINUTES_PER_HOUR * HOURS_PER_DAY;

    static second_type const           SECONDS_PER_MINUTE           = 60U;
    static second_size_type const      SECONDS_PER_HOUR             = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static second_size_type const      SECONDS_PER_DAY              = SECONDS_PER_HOUR * HOURS_PER_DAY;

    static millisecond_type const      MILLISECONDS_PER_SECOND      = 1000U;
    static millisecond_size_type const MILLISECONDS_PER_MINUTE      = static_cast<millisecond_size_type>(MILLISECONDS_PER_SECOND) * SECONDS_PER_MINUTE;
    static millisecond_size_type const MILLISECONDS_PER_HOUR        = MILLISECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static millisecond_size_type const MILLISECONDS_PER_DAY         = MILLISECONDS_PER_HOUR * HOURS_PER_DAY;

    static microsecond_type const      MICROSECONDS_PER_MILLISECOND = 1000UL;
    static microsecond_type const      MICROSECONDS_PER_SECOND      = 1000000UL;
    static microsecond_size_type const MICROSECONDS_PER_MINUTE      = static_cast<microsecond_size_type>(MICROSECONDS_PER_SECOND) * SECONDS_PER_MINUTE;
    static microsecond_size_type const MICROSECONDS_PER_HOUR        = MICROSECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static microsecond_size_type const MICROSECONDS_PER_DAY         = MICROSECONDS_PER_HOUR * HOURS_PER_DAY;

    static nanosecond_type const       NANOSECONDS_PER_MICROSECOND  = 1000UL;
    static nanosecond_type const       NANOSECONDS_PER_MILLISECOND  = 1000000UL;
    static nanosecond_type const       NANOSECONDS_PER_SECOND       = 1000000000UL;
    static nanosecond_size_type const  NANOSECONDS_PER_MINUTE       = static_cast<nanosecond_size_type>(NANOSECONDS_PER_SECOND) * SECONDS_PER_MINUTE;
    static nanosecond_size_type const  NANOSECONDS_PER_HOUR         = NANOSECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    static nanosecond_size_type const  NANOSECONDS_PER_DAY          = NANOSECONDS_PER_HOUR * HOURS_PER_DAY;

    /// Maximum values for nanoseconds, microseconds, milliseconds, seconds, minutes and hours.
    static nanosecond_type const       NANOSECONDS_UPPER_BOUND      = NANOSECONDS_PER_SECOND - 1UL;
    static microsecond_type const      MICROSECONDS_UPPER_BOUND     = MICROSECONDS_PER_SECOND - 1UL;
    static millisecond_type const      MILLISECONDS_UPPER_BOUND     = MILLISECONDS_PER_SECOND - 1U;
    static second_type const           SECONDS_UPPER_BOUND          = SECONDS_PER_MINUTE - 1U;
    static minute_type const           MINUTES_UPPER_BOUND          = MINUTES_PER_HOUR - 1U;
    static hour_type const             HOURS_UPPER_BOUND            = HOURS_PER_DAY - 1U;
}; // class TimeDefines

} // namespace ocl

#endif // OCL_GUARD_DATETIME_INTERNAL_TIMEDEFINES_HPP
