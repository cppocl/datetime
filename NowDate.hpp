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

#ifndef OCL_GUARD_DATETIME_NOWDATE_HPP
#define OCL_GUARD_DATETIME_NOWDATE_HPP

#include <ctime>
#include <cstddef>
#include "Date.hpp"
#include "TimeZone.hpp"

namespace ocl
{

class NowDate
{
// Types and constants
public:
    // Keep name as date_type for compatibility with NowTicks class.
    // This allows these classes to be interchanged with template classes.
    typedef Date date_type;

// Static methods.
public:
    static void ToDate(Date& date, tm const& tm_date) throw()
    {
        // Take a copy as this struct is shared across all threads.
        tm local_tm_date = tm_date;

        date.SetDay(static_cast<Date::day_type>(local_tm_date.tm_mday));
        date.SetMonth(static_cast<Date::month_type>(local_tm_date.tm_mon) + Date::MIN_MONTH);
        date.SetYear(static_cast<Date::year_type>(local_tm_date.tm_year + 1900));
    }

    static date_type Now(TimeZone time_zone = TimeZone::GMT)
    {
        tm* tm_date = NULL;
        date_type date;
        time_t t = ::time(NULL);

        switch (time_zone)
        {
        case TimeZone::Local:
            tm_date = localtime(&t);
            break;
        case TimeZone::GMT:
            tm_date = gmtime(&t);
            break;
        }

        if (tm_date != NULL)
            ToDate(date, *tm_date);
        return date;
    }
};

} //namespace ocl

#endif // OCL_GUARD_DATETIME_NOWDATE_HPP
