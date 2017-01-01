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
#include <cstddef>

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

// Static methods.
public:
    static time_type Now()
    {
        return static_cast<time_type>(::clock());
    }

// Constructors and destructor.
public:
    NowTicks() throw()
        : m_start(0)
        , m_stop(0)
        , m_elapsed_ref(NULL)
    {
    }

    NowTicks(bool record_start)
        : m_start(record_start ? Now() : 0)
        , m_stop(0)
        , m_elapsed_ref(NULL)
    {
    }

    // Provide a reference to an elapsed time that can be updated when
    // the object is destroyed or goes out of scope.
    NowTicks(time_type& elapsed)
        : m_start(Now())
        , m_stop(0)
        , m_elapsed_ref(&elapsed)
    {
    }

    ~NowTicks()
    {
        if (m_elapsed_ref != NULL)
            *m_elapsed_ref = Now() - m_start;
    }

// Member functions.
public:
    void Clear() throw()
    {
        m_start = m_stop = static_cast<time_type>(0);
    }

    // Reset the start and stop time to now time.
    void Reset()
    {
        m_start = Now();
        m_stop = m_start;
    }

    // Get elapsed time, and update the stop time if refresh is true.
    time_type GetElapsed(bool refresh = true)
    {
        if (refresh)
            m_stop = Now();
        return m_stop - m_start;
    }

    time_type GetStart() const throw()
    {
        return m_start;
    }

    time_type GetStop() const throw()
    {
        return m_stop;
    }

// Data (internal use only)
private:
    time_type  m_start;
    time_type  m_stop;
    time_type* m_elapsed_ref;
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_NOWTICKS_HPP
