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

#ifndef OCL_GUARD_DATETIME_NOWDATETIME_HPP
#define OCL_GUARD_DATETIME_NOWDATETIME_HPP

#include <ctime>
#include <cstddef>
#include "DateTime.hpp"
#include "TimeZone.hpp"

namespace ocl
{

class NowDateTime
{
// Types and constants
public:
    // Keep name as time_type for compatibility with NowTicks class.
    // This allows these classes to be interchanged with template classes.
    typedef DateTime time_type;

// Static methods.
public:
    static void ToDateTime(DateTime& date_time, tm const& tm_dt) throw()
    {
        // Take a copy as this struct is shared across all threads.
        tm local_tm_dt = tm_dt;

        date_time.SetHours(static_cast<DateTime::hour_type>(local_tm_dt.tm_hour));
        date_time.SetMinutes(static_cast<DateTime::minute_type>(local_tm_dt.tm_min));
        date_time.SetSeconds(static_cast<DateTime::second_type>(local_tm_dt.tm_sec));
        date_time.SetMilliseconds(0U);
        date_time.SetDay(static_cast<DateTime::day_type>(local_tm_dt.tm_mday));
        date_time.SetMonth(static_cast<DateTime::month_type>(local_tm_dt.tm_mon) + DateTime::MIN_MONTH);
        date_time.SetYear(static_cast<DateTime::year_type>(local_tm_dt.tm_year + 1900));
    }

    static time_type Now(TimeZone time_zone = TimeZone::GMT)
    {
        tm* tm_dt = NULL;
        time_type date_time;
        time_t t = ::time(NULL);

        switch (time_zone)
        {
        case TimeZone::Local:
            tm_dt = localtime(&t);
            break;
        case TimeZone::GMT:
            tm_dt = gmtime(&t);
            break;
        }

        if (tm_dt != NULL)
            ToDateTime(date_time, *tm_dt);
        return date_time;
    }
};

} //namespace ocl

#endif // OCL_GUARD_DATETIME_NOWDATETIME_HPP
