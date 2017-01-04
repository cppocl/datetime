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

#ifndef OCL_GUARD_DATETIME_PERFORMANCECOUNT_HPP
#define OCL_GUARD_DATETIME_PERFORMANCECOUNT_HPP

#include "TimeFunction.hpp"
#include "TimeAlgorithms.hpp"
#include "Ticks.hpp"
#include "TicksTime.hpp"

namespace ocl
{

/*
    Get the count for the number of function calls for a user specified duration.
    The specified duration will be updated if this time is exceeded internally to
    calculate the count.
*/
template<typename ticks_type = Ticks<> >
class PerformanceCount
{
public:
    typedef typename ticks_type::time_type time_type;
    typedef TimeFunction<ticks_type> time_function;

    // Performance a timing within the requested duration for a member function with a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename return_type, typename count_type, typename... varargs>
    static void Call(count_type& total_count,
                     time_type& duration_ticks,
                     return_type& return_value,
                     class_type& obj,
                     return_type (class_type::*func)(varargs...),
                     varargs... args)
    {
        count_type sample_count = 0;
        time_type current_ticks = 0;
        time_type sample_ticks = 0;
        total_count = 0;

        // Keep looping until the requested duration for timing the function has expired.
        do
        {
            // Estimate the count required for current ticks and count.
            sample_count = TimeAlgorithms::CalculateTotalCount(duration_ticks,
                                                               current_ticks,
                                                               sample_ticks,
                                                               sample_count);
            total_count += sample_count;

            // Sample the time taken for current sample count.
            sample_ticks = time_function::Call(return_value, sample_count, obj, func, args...);
            current_ticks += sample_ticks;
        }
        while (current_ticks < duration_ticks);

        // Ensure the total duration reflects the total count.
        duration_ticks = current_ticks;
    }

    // Performance a timing within the requested duration for a member function without a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename count_type, typename... varargs>
    static void Call(count_type& total_count,
                     time_type& duration_ticks,
                     class_type& obj,
                     void (class_type::*func)(varargs...),
                     varargs... args)
    {
        count_type sample_count = 0;
        time_type current_ticks = 0;
        time_type sample_ticks = 0;
        total_count = 0;

        // Keep looping until the requested duration for timing the function has expired.
        do
        {
            // Estimate the count required for current ticks and count.
            sample_count = TimeAlgorithms::CalculateTotalCount(duration_ticks,
                                                               current_ticks,
                                                               sample_ticks,
                                                               sample_count);
            total_count += sample_count;

            // Sample the time taken for current sample count.
            sample_ticks = time_function::Call(sample_count, obj, func, args...);
            current_ticks += sample_ticks;
        }
        while (current_ticks < duration_ticks);

        // Ensure the total duration reflects the total count.
        duration_ticks = current_ticks;
    }

    // Performance a timing within the requested duration for a const member function with a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename return_type, typename count_type, typename... varargs>
    static void Call(count_type& total_count,
                     time_type& duration_ticks,
                     return_type& return_value,
                     class_type const& obj,
                     return_type (class_type::*func)(varargs...) const,
                     varargs... args)
    {
        count_type sample_count = 0;
        time_type current_ticks = 0;
        time_type sample_ticks = 0;
        total_count = 0;

        // Keep looping until the requested duration for timing the function has expired.
        do
        {
            // Estimate the count required for current ticks and count.
            sample_count = TimeAlgorithms::CalculateTotalCount(duration_ticks,
                                                               current_ticks,
                                                               sample_ticks,
                                                               sample_count);
            total_count += sample_count;

            // Sample the time taken for current sample count.
            sample_ticks = time_function::Call(return_value, sample_count, obj, func, args...);
            current_ticks += sample_ticks;
        }
        while (current_ticks < duration_ticks);

        // Ensure the total duration reflects the total count.
        duration_ticks = current_ticks;
    }

    // Performance a timing within the requested duration for a const member function without a return value,
    // and return the number of calls for the duration.
    template<typename class_type, typename count_type, typename... varargs>
    static void Call(count_type& total_count,
                     time_type& duration_ticks,
                     class_type const& obj,
                     void (class_type::*func)(varargs...) const,
                     varargs... args)
    {
        count_type sample_count = 0;
        time_type current_ticks = 0;
        time_type sample_ticks = 0;
        total_count = 0;

        // Keep looping until the requested duration for timing the function has expired.
        do
        {
            // Estimate the count required for current ticks and count.
            sample_count = TimeAlgorithms::CalculateTotalCount(duration_ticks,
                                                               current_ticks,
                                                               sample_ticks,
                                                               sample_count);
            total_count += sample_count;

            // Sample the time taken for current sample count.
            sample_ticks = time_function::Call(sample_count, obj, func, args...);
            current_ticks += sample_ticks;
        }
        while (current_ticks < duration_ticks);

        // Ensure the total duration reflects the total count.
        duration_ticks = current_ticks;
    }

    // Performance a timing within the requested duration for a function with a return value,
    // and return the number of calls for the duration.
    template<typename return_type, typename count_type, typename... varargs>
    static void Call(count_type& total_count,
                     time_type& duration_ticks,
                     return_type& return_value,
                     return_type (*func)(varargs...),
                     varargs... args)
    {
        count_type sample_count = 0;
        time_type current_ticks = 0;
        time_type sample_ticks = 0;
        total_count = 0;

        // Keep looping until the requested duration for timing the function has expired.
        do
        {
            // Estimate the count required for current ticks and count.
            sample_count = TimeAlgorithms::CalculateTotalCount(duration_ticks,
                                                               current_ticks,
                                                               sample_ticks,
                                                               sample_count);
            total_count += sample_count;

            // Sample the time taken for current sample count.
            sample_ticks = time_function::Call(return_value, sample_count, func, args...);
            current_ticks += sample_ticks;
        }
        while (current_ticks < duration_ticks);

        // Ensure the total duration reflects the total count.
        duration_ticks = current_ticks;
    }

    // Performance a timing within the requested duration for a function without a return value,
    // and return the number of calls for the duration.
    template<typename count_type, typename... varargs>
    static void Call(count_type& total_count,
                     time_type& duration_ticks,
                     void (*func)(varargs...),
                     varargs... args)
    {
        count_type sample_count = 0;
        time_type current_ticks = 0;
        time_type sample_ticks = 0;
        total_count = 0;

        // Keep looping until the requested duration for timing the function has expired.
        do
        {
            // Estimate the count required for current ticks and count.
            sample_count = TimeAlgorithms::CalculateTotalCount(duration_ticks,
                                                               current_ticks,
                                                               sample_ticks,
                                                               sample_count);
            total_count += sample_count;

            // Sample the time taken for current sample count.
            sample_ticks = time_function::Call(sample_count, func, args...);
            current_ticks += sample_ticks;
        }
        while (current_ticks < duration_ticks);

        // Ensure the total duration reflects the total count.
        duration_ticks = current_ticks;
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_PERFORMANCECOUNT_HPP
