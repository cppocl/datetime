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

#ifndef OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEFUNCTION_HPP
#define OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEFUNCTION_HPP

#include "Ticks.hpp"

namespace ocl
{

/*
    Time a function or member function with or without a return type X times,
    using a timer that provides a Now function and can subtract two times.
    Note this is an internal class because the return type needs to be a
    template parameter so that void return type can be specialized.
    TimeFunction class in the folder up using this internal class.
*/

// Performance test a member function with a return value n times.
template<typename return_type,
         typename ticks_type = Ticks<> >
class InternalTimeFunction
{
public:
    typedef typename ticks_type::time_type time_type;

    // Get elapsed time for a specified count of calls
    // for a member function with a return value, executed N times.
    template<typename class_type, typename count_type, typename... varargs>
    static time_type Call(return_type& return_value,
                          count_type count,
                          class_type& obj,
                          return_type (class_type::*func)(varargs...),
                          varargs... args)
    {
        time_type start = ticks_type::Now();
        for (count_type i = 0; i < count; ++i)
            return_value = (obj.*func)(args...);
        return ticks_type::Now() - start;
    }

    // Get elapsed time for a specified count of calls
    // for a member function with a return value, executed N times.
    template<typename class_type, typename count_type, typename... varargs>
    static time_type Call(return_type& return_value,
                          count_type count,
                          class_type const& obj,
                          return_type (class_type::*func)(varargs...) const,
                          varargs... args)
    {
        time_type start = ticks_type::Now();
        for (count_type i = 0; i < count; ++i)
            return_value = (obj.*func)(args...);
        return ticks_type::Now() - start;
    }

    // Get elapsed time for a specified count of calls
    // for a function with a return value, executed N times.
    template<typename count_type, typename... varargs>
    static time_type Call(return_type& return_value,
                          count_type count,
                          return_type (*func)(varargs...),
                          varargs... args)
    {
        time_type start = ticks_type::Now();
        for (count_type i = 0; i < count; ++i)
            return_value = (*func)(args...);
        return ticks_type::Now() - start;
    }
};

template<typename ticks_type>
class InternalTimeFunction<void, ticks_type>
{
public:
    typedef typename ticks_type::time_type time_type;

    // Get elapsed time for a specified count of calls
    // for a member function without a return value, executed N times.
    template<typename class_type, typename count_type, typename... varargs>
    static time_type Call(count_type count,
                          class_type& obj,
                          void (class_type::*func)(varargs...),
                          varargs... args)
    {
        time_type start = ticks_type::Now();
        for (count_type i = 0; i < count; ++i)
            (obj.*func)(args...);
        return ticks_type::Now() - start;
    }

    // Get elapsed time for a specified count of calls
    // for a member function without a return value, executed N times.
    template<typename class_type, typename count_type, typename... varargs>
    static time_type Call(count_type count,
                          class_type const& obj,
                          void (class_type::*func)(varargs...) const,
                          varargs... args)
    {
        time_type start = ticks_type::Now();
        for (count_type i = 0; i < count; ++i)
            (obj.*func)(args...);
        return ticks_type::Now() - start;
    }

    // Get elapsed time for a specified count of calls
    // for a function without a return value, executed N times.
    template<typename count_type, typename... varargs>
    static time_type Call(count_type count,
                          void (*func)(varargs...),
                          varargs... args)
    {
        time_type start = ticks_type::Now();
        for (count_type i = 0; i < count; ++i)
            (*func)(args...);
        return ticks_type::Now() - start;
    }
};

template<typename ticks_type,
         typename return_type,
         typename class_type,
         typename count_type,
         typename... varargs>
inline
typename ticks_type::time_type
TimeCall(count_type count,
         class_type& obj,
         return_type (class_type::*func)(varargs...),
         varargs... args)
{
    typedef InternalTimeFunction<return_type, ticks_type> time_function;
    return time_function::Call<class_type, count_type, varargs...>(count, obj, func, args...);
}

template<typename ticks_type,
         typename return_type,
         typename count_type,
         typename... varargs>
inline
typename ticks_type::time_type
TimeCall(count_type count,
         return_type (*func)(varargs...),
         varargs... args)
{
    typedef InternalTimeFunction<return_type, ticks_type> time_function;
    return time_function::Call<class_type, count_type, varargs...>(count, obj, func, args...);
}

} // namespace ocl

#endif // OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEFUNCTION_HPP
