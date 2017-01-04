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

#ifndef OCL_GUARD_DATETIME_PERFORMANCETIME_HPP
#define OCL_GUARD_DATETIME_PERFORMANCETIME_HPP

#include "PerformanceCount.hpp"

namespace ocl
{

/*
    Get the time in seconds for a function call, calculated over a user specified duration.
    The specified duration will be updated if this time is exceeded internally to
    calculate the function call time.
*/
template<typename ticks_type = Ticks<> >
class PerformanceTime
{
public:
    typedef typename ticks_type::time_type time_type;
    typedef PerformanceCount<ticks_type> performance_count;

    // Convert the total count and the total duration ticks into seconds per call.
    template<typename count_type>
    static double CalculateCallTimeInSeconds(count_type total_count, time_type duration_ticks)
    {
        time_type ms = TicksTime<time_type>::TicksToMilliseconds(duration_ticks, ticks_type::TICKS_PER_SECOND);
        return TimeAlgorithms::CalculateCallTimeInSeconds(total_count, ms);
    }

    // Performance a timing within the requested duration for a member function with a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename return_type, typename... varargs>
    static void Call(double& call_time_in_seconds,
                     time_type& duration_ticks,
                     return_type& return_value,
                     class_type& obj,
                     return_type (class_type::*func)(varargs...),
                     varargs... args)
    {
        typedef unsigned long long count_type;

        count_type total_count = 0ULL;
        performance_count::Call<class_type, return_type, count_type, varargs...>(
            total_count, duration_ticks, return_value, obj, func, args...);

        call_time_in_seconds = CalculateCallTimeInSeconds(total_count, duration_ticks);
    }

    // Performance a timing within the requested duration for a member function without a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename... varargs>
    static void Call(double& call_time_in_seconds,
                     time_type& duration_ticks,
                     class_type& obj,
                     void (class_type::*func)(varargs...),
                     varargs... args)
    {
        typedef unsigned long long count_type;

        count_type total_count = 0ULL;
        performance_count::Call<class_type, count_type, varargs...>(
            total_count, duration_ticks, obj, func, args...);

        call_time_in_seconds = CalculateCallTimeInSeconds(total_count, duration_ticks);
    }

    // Performance a timing within the requested duration for a const member function with a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename return_type, typename... varargs>
    static void Call(double& call_time_in_seconds,
                     time_type& duration_ticks,
                     return_type& return_value,
                     class_type const& obj,
                     return_type (class_type::*func)(varargs...) const,
                     varargs... args)
    {
        typedef unsigned long long count_type;

        count_type total_count = 0ULL;
        performance_count::Call<class_type, return_type, count_type, varargs...>(
            total_count, duration_ticks, return_value, obj, func, args...);

        call_time_in_seconds = CalculateCallTimeInSeconds(total_count, duration_ticks);
    }

    // Performance a timing within the requested duration for a const member function without a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename... varargs>
    static void Call(double& call_time_in_seconds,
                     time_type& duration_ticks,
                     class_type const& obj,
                     void (class_type::*func)(varargs...) const,
                     varargs... args)
    {
        typedef unsigned long long count_type;

        count_type total_count = 0ULL;
        performance_count::Call<class_type, count_type, varargs...>(
            total_count, duration_ticks, obj, func, args...);

        call_time_in_seconds = CalculateCallTimeInSeconds(total_count, duration_ticks);
    }

    // Performance a timing within the requested duration for a function with a return value,
    // and return the number of calls for the duration.
    template<typename return_type, typename... varargs>
    static void Call(double& call_time_in_seconds,
                     time_type& duration_ticks,
                     return_type& return_value,
                     return_type (*func)(varargs...),
                     varargs... args)
    {
        typedef unsigned long long count_type;

        count_type total_count = 0ULL;
        performance_count::Call<return_type, count_type, varargs...>(
            total_count, duration_ticks, return_value, func, args...);

        call_time_in_seconds = CalculateCallTimeInSeconds(total_count, duration_ticks);
    }

    // Performance a timing within the requested duration for a function without a return value,
    // and return the number of calls for the duration.
    template<typename... varargs>
    static void Call(double& call_time_in_seconds,
                     time_type& duration_ticks,
                     void (*func)(varargs...),
                     varargs... args)
    {
        typedef unsigned long long count_type;

        count_type total_count = 0ULL;
        performance_count::Call<count_type, varargs...>(
            total_count, duration_ticks, func, args...);

        call_time_in_seconds = CalculateCallTimeInSeconds(total_count, duration_ticks);
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_PERFORMANCETIME_HPP
