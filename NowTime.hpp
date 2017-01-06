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

class NowTime
{
// Types and constants
public:
    // Keep name as time_type for compatibility with NowTicks class.
    // This allows these classes to be interchanged with template classes.
    typedef Time time_type;

// Static methods.
public:
    static void ToTime(Time& time, tm const& tm_time) throw()
    {
        // Take a copy as this struct is shared across all threads.
        tm local_tm_time = tm_time;

        time.SetHours(static_cast<Time::hour_type>(local_tm_time.tm_hour));
        time.SetMinutes(static_cast<Time::minute_type>(local_tm_time.tm_min));
        time.SetSeconds(static_cast<Time::second_type>(local_tm_time.tm_sec));
        time.SetMilliseconds(0U);
    }

    static time_type Now(TimeZone time_zone = TimeZone::GMT)
    {
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
            ToTime(time, *tm_time);
        return time;
    }
};

} //namespace ocl

#endif // OCL_GUARD_DATETIME_NOWTIME_HPP
