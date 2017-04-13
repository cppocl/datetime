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

#ifndef OCL_GUARD_DATETIME_NOWTIME_HPP
#define OCL_GUARD_DATETIME_NOWTIME_HPP

#include <ctime>
#include <cstddef>
#include "Time.hpp"
#include "TimeZone.hpp"

namespace ocl
{

template<TimePrecision precision>
class NowTime;

template<>
class NowTime<Milliseconds>
{
// Types and constants
public:
    static TimePrecision const PRECISION = Milliseconds;

    // Keep name as time_type for compatibility with NowTicks class.
    // This allows these classes to be interchanged with template classes.
    typedef Time<PRECISION> time_type;

// Static methods.
public:
    static void ToTime(time_type& time, tm const& tm_time) throw()
    {
        // Take a copy as this struct is shared across all threads.
        tm local_tm_time = tm_time;

        time.SetHours(static_cast<time_type::hour_type>(local_tm_time.tm_hour));
        time.SetMinutes(static_cast<time_type::minute_type>(local_tm_time.tm_min));
        time.SetSeconds(static_cast<time_type::second_type>(local_tm_time.tm_sec));
        time.SetMilliseconds(0U);
    }

    static time_type Now(TimeZone time_zone = TimeZone::GMT)
    {
        typedef TimeMs::millisecond_type millisecond_type;

        // Find a reference point for calculating elapsed time.
        static clock_t const start_clocks = ::clock();

        tm* tm_time = NULL;
        time_type time;
        time_t t = ::time(NULL);

        switch (time_zone)
        {
        case TimeZone::Local:
            tm_time = localtime(&t);
            break;
        case TimeZone::GMT:
            tm_time = gmtime(&t);
            break;
        }

        if (tm_time != NULL)
        {
            clock_t elapsed = ::clock() - start_clocks;
            time_type::size_type ms = (static_cast<time_type::size_type>(elapsed) * TimeNs::MILLISECONDS_PER_SECOND) /
                                       static_cast<time_type::size_type>(CLOCKS_PER_SEC);
            ToTime(time, *tm_time);
            time.SetMilliseconds(static_cast<millisecond_type>(ms));
        }
        return time;
    }
};

template<>
class NowTime<Nanoseconds>
{
// Types and constants
public:
    static TimePrecision const PRECISION = Nanoseconds;

    // Keep name as time_type for compatibility with NowTicks class.
    // This allows these classes to be interchanged with template classes.
    typedef Time<PRECISION> time_type;

// Static methods.
public:
    static void ToTime(time_type& time, tm const& tm_time) throw()
    {
        // Take a copy as this struct is shared across all threads.
        tm local_tm_time = tm_time;

        time.SetHours(static_cast<time_type::hour_type>(local_tm_time.tm_hour));
        time.SetMinutes(static_cast<time_type::minute_type>(local_tm_time.tm_min));
        time.SetSeconds(static_cast<time_type::second_type>(local_tm_time.tm_sec));
        time.SetNanoseconds(0U);
    }

    static time_type Now(TimeZone time_zone = TimeZone::GMT)
    {
        typedef TimeMs::nanosecond_type nanosecond_type;

        // Find a reference point for calculating elapsed time.
        static clock_t const start_clocks = ::clock();

        tm* tm_time = NULL;
        time_type time;
        time_t t = ::time(NULL);

        switch (time_zone)
        {
        case TimeZone::Local:
            tm_time = localtime(&t);
            break;
        case TimeZone::GMT:
            tm_time = gmtime(&t);
            break;
        }

        if (tm_time != NULL)
        {
            clock_t elapsed = (::clock() - start_clocks) % CLOCKS_PER_SEC;
            time_type::size_type ns = (static_cast<time_type::size_type>(elapsed) * TimeNs::NANOSECONDS_PER_SECOND) /
                                       static_cast<time_type::size_type>(CLOCKS_PER_SEC);
            ToTime(time, *tm_time);
            time.SetNanoseconds(static_cast<nanosecond_type>(ns));
        }
        return time;
    }
};

typedef NowTime<Milliseconds> NowTimeMs;
typedef NowTime<Nanoseconds>  NowTimeNs;

} //namespace ocl

#endif // OCL_GUARD_DATETIME_NOWTIME_HPP
