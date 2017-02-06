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

#ifndef OCL_GUARD_DATETIME_NOW_HPP
#define OCL_GUARD_DATETIME_NOW_HPP

#include "NowTicks.hpp"
#include "NowDate.hpp"
#include "NowTime.hpp"
#include "NowDateTime.hpp"

namespace ocl
{

template<typename TimeType>
class Now
{
// Types.
public:
    typedef TimeType time_type;

// Static methods.
public:
    static time_type GetNow(TimeZone time_zone = TimeZone::GMT)
    {
        return static_cast<time_type>(NowTicks<time_type>::Now());
    }

// Constructors.
public:
    Now(time_type& now_ticks, TimeZone time_zone = TimeZone::GMT)
    {
        now_ticks = GetNow(time_zone);
    }
};

template<>
class Now<Date>
{
// Types.
public:
    typedef Date time_type;

// Static methods.
public:
    static time_type GetNow(TimeZone time_zone = TimeZone::GMT)
    {
        return NowDate::Now(time_zone);
    }

// Constructors.
public:
    Now(time_type& now_date, TimeZone time_zone = TimeZone::GMT)
    {
        now_date = GetNow(time_zone);
    }
};

template<>
class Now<Time>
{
// Types.
public:
    typedef Time time_type;

// Static methods.
public:
    static time_type GetNow(TimeZone time_zone = TimeZone::GMT)
    {
        return NowTime::Now(time_zone);
    }

// Constructors.
public:
    Now(time_type& now_time, TimeZone time_zone = TimeZone::GMT)
    {
        now_time = GetNow(time_zone);
    }
};

template<>
class Now<DateTime>
{
// Types.
public:
    typedef DateTime time_type;

// Static methods.
public:
    static time_type GetNow(TimeZone time_zone = TimeZone::GMT)
    {
        return NowDateTime::Now(time_zone);
    }

// Constructors.
public:
    Now(time_type& now_date_time, TimeZone time_zone = TimeZone::GMT)
    {
        now_date_time = GetNow(time_zone);
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_NOW_HPP
