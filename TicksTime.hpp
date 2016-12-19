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

#ifndef OCL_GUARD_DATETIME_TICKSTIME_HPP
#define OCL_GUARD_DATETIME_TICKSTIME_HPP

namespace ocl
{

// Utility class for converting ticks to time.
template<typename TimeType>
class TicksTime
{
public:
    typedef TimeType time_type;

public:
    static time_type SecondsToTicks(time_type const seconds,
                                    time_type const ticks_per_sec)
    {
        return seconds * ticks_per_sec;
    }

    static time_type MillisecondsToTicks(time_type const milliseconds,
                                         time_type const ticks_per_sec)
    {
        return (milliseconds * ticks_per_sec) / static_cast<time_type>(1000);
    }

    static time_type MicrosecondsToTicks(time_type const microseconds,
                                         time_type const ticks_per_sec)
    {
        return (microseconds * ticks_per_sec) / static_cast<time_type>(1000000);
    }

    static time_type NanosecondsToTicks(time_type const nanoseconds,
                                        time_type const ticks_per_sec)
    {
        return (nanoseconds * ticks_per_sec) / static_cast<time_type>(1000000000);
    }

    static time_type TicksToSeconds(time_type const ticks,
                                    time_type const ticks_per_sec)
    {
        return ticks / ticks_per_sec;
    }

    static time_type TicksToMilliseconds(time_type const ticks,
                                         time_type const ticks_per_sec)
    {
        return (ticks * static_cast<time_type>(1000)) / ticks_per_sec;
    }

    static time_type TicksToMicroseconds(time_type const ticks,
                                         time_type const ticks_per_sec)
    {
        return (ticks * static_cast<time_type>(1000000)) / ticks_per_sec;
    }

    static time_type TicksToNanoseconds(time_type const ticks,
                                        time_type const ticks_per_sec)
    {
        return (ticks * static_cast<time_type>(1000000000)) / ticks_per_sec;
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_TICKSTIME_HPP
