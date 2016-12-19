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

#ifndef OCL_GUARD_DATETIME_NOWTICKS_HPP
#define OCL_GUARD_DATETIME_NOWTICKS_HPP

#include <ctime>

namespace ocl
{

// Provide a basic class that defines the type for ticks, number of ticks per second
// obtain the current time in ticks.
template<typename TimeType = clock_t>
class NowTicks
{
// Types and constants
public:
    typedef TimeType time_type;

    static time_type const TICKS_PER_SECOND = CLOCKS_PER_SEC;

public:
    static time_type Now()
    {
        return static_cast<time_type>(::clock());
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_NOWTICKS_HPP
