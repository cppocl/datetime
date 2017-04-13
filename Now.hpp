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

template<typename time_type>
inline time_type Now(TimeZone /*time_zone*/ = TimeZone::GMT)
{
    return static_cast<time_type>(NowTicks<time_type>::Now());
}

template<>
inline Date Now<Date>(TimeZone time_zone)
{
    return NowDate::Now(time_zone);
}

template<>
inline Time<Milliseconds> Now< Time<Milliseconds> >(TimeZone time_zone)
{
    return NowTime<Milliseconds>::Now(time_zone);
}

template<>
inline Time<Nanoseconds> Now< Time<Nanoseconds> >(TimeZone time_zone)
{
    return NowTime<Nanoseconds>::Now(time_zone);
}

template<>
DateTime<Milliseconds> Now< DateTime<Milliseconds> >(TimeZone time_zone)
{
    return NowDateTime<Milliseconds>::Now(time_zone);
}

template<>
DateTime<Nanoseconds> Now< DateTime<Nanoseconds> >(TimeZone time_zone)
{
    return NowDateTime<Nanoseconds>::Now(time_zone);
}

} // namespace ocl

#endif // OCL_GUARD_DATETIME_NOW_HPP
