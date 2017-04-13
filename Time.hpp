/*
Copyright 2017 Colin Girling

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

#ifndef OCL_GUARD_DATETIME_TIME_HPP
#define OCL_GUARD_DATETIME_TIME_HPP

#include "TimeDefines.hpp"
#include "TimePrecision.hpp"
#include "internal/internalTimeMs.hpp"
#include "internal/internalTimeNs.hpp"
#include "internal/internalTimeCommon.hpp"
#include "internal/internalTimePrecisionType.hpp"

namespace ocl
{

/*
    24 hour time storing hours, minutes, seconds and milliseconds or nanoseconds.
    The time is guaranteed to fit into 4 bytes for milliseconds or 8 bytes for nanoseconds.
*/
template<TimePrecision const time_precision>
class Time : public InternalTimeCommon<typename InternalTimePrecisionType<time_precision>::precision_time_type>
{
// helper types (for internal use only)
private:
    typedef Time<time_precision> type;
    typedef InternalTimeCommon<typename InternalTimePrecisionType<time_precision>::precision_time_type> base_type;

// Types.
public:
    // Size types when converting into values larger than the limit
    // stored within a time period.
    typedef typename base_type::nanosecond_size_type  nanosecond_size_type;
    typedef typename base_type::nanosecond_diff_type  nanosecond_diff_type;
    typedef typename base_type::microsecond_size_type microsecond_size_type;
    typedef typename base_type::microsecond_diff_type microsecond_diff_type;
    typedef typename base_type::millisecond_size_type millisecond_size_type;
    typedef typename base_type::millisecond_diff_type millisecond_diff_type;
    typedef typename base_type::second_size_type      second_size_type;
    typedef typename base_type::second_diff_type      second_diff_type;
    typedef typename base_type::minute_size_type      minute_size_type;
    typedef typename base_type::minute_diff_type      minute_diff_type;
    typedef typename base_type::hour_size_type        hour_size_type;
    typedef typename base_type::hour_diff_type        hour_diff_type;
    typedef typename base_type::size_type             size_type;
    typedef typename base_type::diff_type             diff_type;
    typedef typename base_type::serialize_type        serialize_type;

    // For Time<Milliseconds> this will be millisecond_type,
    // and for Time<Nanoseconds> this will be nanosecond_type.
    typedef typename base_type::smallest_unit_type    smallest_unit_type;

    /// Types for hours, minutes, seconds, milliseconds and nanoseconds,
    // that don't exceed their limit within a time period.
    typedef typename base_type::nanosecond_type       nanosecond_type;
    typedef typename base_type::microsecond_type      microsecond_type;
    typedef typename base_type::millisecond_type      millisecond_type;
    typedef typename base_type::second_type           second_type;
    typedef typename base_type::minute_type           minute_type;
    typedef typename base_type::hour_type             hour_type;

// Constants.
public:
    static hour_type const             HOURS_PER_DAY                = base_type::HOURS_PER_DAY;

    static minute_type const           MINUTES_PER_HOUR             = base_type::MINUTES_PER_HOUR;
    static minute_size_type const      MINUTES_PER_DAY              = base_type::MINUTES_PER_DAY;

    static second_type const           SECONDS_PER_MINUTE           = base_type::SECONDS_PER_MINUTE;
    static second_size_type const      SECONDS_PER_HOUR             = base_type::SECONDS_PER_HOUR;
    static second_size_type const      SECONDS_PER_DAY              = base_type::SECONDS_PER_DAY;

    static millisecond_type const      MILLISECONDS_PER_SECOND      = base_type::MILLISECONDS_PER_SECOND;
    static millisecond_size_type const MILLISECONDS_PER_MINUTE      = base_type::MILLISECONDS_PER_MINUTE;
    static millisecond_size_type const MILLISECONDS_PER_HOUR        = base_type::MILLISECONDS_PER_HOUR;
    static millisecond_size_type const MILLISECONDS_PER_DAY         = base_type::MILLISECONDS_PER_DAY;

    static microsecond_type const      MICROSECONDS_PER_MILLISECOND = base_type::MICROSECONDS_PER_MILLISECOND;
    static microsecond_type const      MICROSECONDS_PER_SECOND      = base_type::MICROSECONDS_PER_SECOND;
    static microsecond_size_type const MICROSECONDS_PER_MINUTE      = base_type::MICROSECONDS_PER_MINUTE;
    static microsecond_size_type const MICROSECONDS_PER_HOUR        = base_type::MICROSECONDS_PER_HOUR;
    static microsecond_size_type const MICROSECONDS_PER_DAY         = base_type::MICROSECONDS_PER_DAY;

    static nanosecond_type const       NANOSECONDS_PER_MICROSECOND  = base_type::NANOSECONDS_PER_MICROSECOND;
    static nanosecond_type const       NANOSECONDS_PER_MILLISECOND  = base_type::NANOSECONDS_PER_MILLISECOND;
    static nanosecond_type const       NANOSECONDS_PER_SECOND       = base_type::NANOSECONDS_PER_SECOND;
    static nanosecond_size_type const  NANOSECONDS_PER_MINUTE       = base_type::NANOSECONDS_PER_MINUTE;
    static nanosecond_size_type const  NANOSECONDS_PER_HOUR         = base_type::NANOSECONDS_PER_HOUR;
    static nanosecond_size_type const  NANOSECONDS_PER_DAY          = base_type::NANOSECONDS_PER_DAY;

    /// Maximum values for nanoseconds, microseconds, milliseconds, seconds, minutes and hours.
    static nanosecond_type const       NANOSECONDS_UPPER_BOUND      = base_type::NANOSECONDS_UPPER_BOUND;
    static microsecond_type const      MICROSECONDS_UPPER_BOUND     = base_type::MICROSECONDS_UPPER_BOUND;
    static millisecond_type const      MILLISECONDS_UPPER_BOUND     = base_type::MILLISECONDS_UPPER_BOUND;
    static second_type const           SECONDS_UPPER_BOUND          = base_type::SECONDS_UPPER_BOUND;
    static minute_type const           MINUTES_UPPER_BOUND          = base_type::MINUTES_UPPER_BOUND;
    static hour_type const             HOURS_UPPER_BOUND            = base_type::HOURS_UPPER_BOUND;

    // Provide easy means for Time class to identify if the precision is more accurate than a second.
    // This is true when Time precision is Milliseconds or Nanoseconds.
    static bool const                  HAS_PARTIAL_SECONDS          = base_type::HAS_PARTIAL_SECONDS;

    // For generic use of the smallest units of precision for the Time.
    // If PRECISION is Milliseconds then units is in milliseconds,
    // If PRECISION is Nanoseconds then units is in nanoseconds.
    static TimePrecision const         PRECISION                    = base_type::PRECISION;
    static size_type const             UNITS_PER_SECOND             = base_type::UNITS_PER_SECOND;
    static size_type const             UNITS_PER_MINUTE             = base_type::UNITS_PER_MINUTE;
    static size_type const             UNITS_PER_HOUR               = base_type::UNITS_PER_HOUR;
    static size_type const             UNITS_PER_DAY                = base_type::UNITS_PER_DAY;

// Constructors.
public:
    Time() throw()
    {
    }

    Time(hour_type hours,             // 0..23
         minute_type minutes) throw() // 0..59
        : base_type(hours, minutes)
    {
    }

    Time(hour_type hours,             // 0..23
         minute_type minutes,         // 0..59
         second_type seconds) throw() // 0..59
        : base_type(hours, minutes, seconds)
    {
    }

    Time(hour_type hours,                           // 0..23
         minute_type minutes,                       // 0..59
         second_type seconds,                       // 0..59
         smallest_unit_type smallest_units) throw() // 0..999 or 0..999999999
        : base_type(hours, minutes, seconds, smallest_units)
    {
    }

    Time(type const& time) throw()
        : base_type(time)
    {
    }

// Overloaded operators.
public:
    Time& operator =(type const& time) throw()
    {
        base_type::Copy(time);
        return *this;
    }

    bool operator <(type const& other) const throw()
    {
        return base_type::IsLess(other);
    }

    bool operator <=(type const& other) const throw()
    {
        return base_type::IsLessEqual(other);
    }

    bool operator >(type const& other) const throw()
    {
        return base_type::IsGreater(other);
    }

    bool operator >=(type const& other) const throw()
    {
        return base_type::IsGreaterEqual(other);
    }

    bool operator ==(type const& other) const throw()
    {
        return base_type::IsEqual(other);
    }

    bool operator !=(type const& other) const throw()
    {
        return base_type::IsNotEqual(other);
    }

    /// Depending on the precision, add the smallest unit type to this time.
    /// E.g. if precision is Milliseconds then the partial value will be in milliseconds.
    Time& operator +=(size_type smallest_units)
    {
        Add(smallest_units);
        return *this;
    }

    /// Depending on the precision, subtract the smallest unit type to this time.
    /// E.g. if precision is Milliseconds then the partial value will be in milliseconds.
    Time& operator -=(size_type smallest_units)
    {
        Subtract(smallest_units);
        return *this;
    }

    /// Get difference between two times in milliseconds.
    Time operator +(size_type smallest_units) const throw()
    {
        Time time(*this);
        time.Add(smallest_units);
        return time;
    }

    /// Get difference between two times in milliseconds.
    Time operator -(size_type smallest_units) const throw()
    {
        Time time(*this);
        time.Subtract(smallest_units);
        return time;
    }

    /// Get difference between two times in milliseconds.
    diff_type operator -(type const& other) const throw()
    {
        size_type this_smallest_units  = Transform();
        size_type other_smallest_units = other.Transform();

        return static_cast<diff_type>(this_smallest_units) -
               static_cast<diff_type>(other_smallest_units);
    }

    Time operator ++() throw() // Prefix
    {
        Add(1U);
        return *this;
    }

    Time operator ++(int) throw() // Postfix
    {
        Time time(*this);
        time.Add(1U);
        return time;
    }

    Time operator --() throw() // Prefix
    {
        Subtract(1U);
        return *this;
    }

    Time operator --(int) throw() // Postfix
    {
        Time time(*this);
        time.Subtract(1U);
        return time;
    }

// Public interface pulled through from base class.
// Although these functions don't need to be here and can be called from base,
// for easier readability of the Time class interface,
// they have been pulled into the Time class.
public:
    /// Add smallest units, which could be milliseconds, nanoseconds, etc, depending on precision.
    // The time will not exceed a whole day.
    void Add(size_type smallest_units_to_add) throw()
    {
        base_type::Add(smallest_units_to_add);
    }

    /// Add smallest units, which could be milliseconds, nanoseconds, etc, depending on precision.
    // The time will not exceed a whole day, and overflow will be set if addition is too big.
    void Add(size_type smallest_units_to_add, size_type& overflow) throw()
    {
        base_type::Add(smallest_units_to_add, overflow);
    }

    /// Subtract milliseconds to 0:0:0:0.
    void Subtract(size_type smallest_units_to_subtract) throw()
    {
        base_type::Subtract(smallest_units_to_subtract);
    }

    /// Subtract smallest units, which could be milliseconds, nanoseconds, etc, depending on precision.
    // The time will not exceed 0:0:0:0, and underflow will be set if addition is too big.
    void Subtract(size_type smallest_units_to_subtract, size_type& underflow) throw()
    {
        base_type::Subtract(smallest_units_to_subtract, underflow);
    }

    /// Get the difference between this time and the other time in smallest units,
    /// i.e. milliseconds or nanoseconds.
    /// with this time expected to be less or equal to the other time.
    size_type GetDifference(type const& other) const throw()
    {
        return base_type::GetDifference(other);
    }

    int Compare(type const& other) const throw()
    {
        return IsLess(other) ? -1 : (IsGreater(other) ? 1 : 0);
    }

    nanosecond_type GetNanoseconds() const throw()
    {
        return base_type::GetNanoseconds();
    }

    void SetNanoseconds(nanosecond_type nanoseconds) throw()
    {
        base_type::SetNanoseconds(nanoseconds);
    }

    millisecond_type GetMilliseconds() const throw()
    {
        return base_type::GetMilliseconds();
    }

    void SetMilliseconds(millisecond_type milliseconds) throw()
    {
        base_type::SetMilliseconds(milliseconds);
    }

    second_type GetSeconds() const throw()
    {
        return base_type:: GetSeconds();
    }

    void SetSeconds(second_type seconds) throw()
    {
        base_type::SetSeconds(seconds);
    }

    minute_type GetMinutes() const throw()
    {
        return base_type::GetMinutes();
    }

    void SetMinutes(minute_type minutes) throw()
    {
        base_type::SetMinutes(minutes);
    }

    hour_type GetHours() const throw()
    {
        return base_type::GetHours();
    }

    void SetHours(hour_type hours) throw()
    {
        base_type::SetHours(hours);
    }

    /*
    /// GetTime and SetTime are public via the base class,
    /// and are specific to the precision of the time.
    /// i.e. smallest unit could be Milliseconds or Nanoseconds.
    void GetTime(hour_type& hours,
                 minute_type& minutes,
                 second_type& seconds,
                 smallest_unit_type& smallest_units) throw();

    void SetTime(hour_type hours,
                 minute_type minutes,
                 second_type seconds,
                 smallest_unit_type smallest_units) throw();
    */

    /// Transform time into the smallest units, i.e. milliseconds or nanoseconds value.
    /// 0:0:0.0 would returned as 0.
    size_type Transform() const throw()
    {
        return base_type::Transform();
    }

    /// Transform the smallest units, i.e. milliseconds or nanoseconds into a time.
    /// 0 would set the time to 0:0:0.0.
    void Transform(size_type smallest_units) throw()
    {
        base_type::Transform(smallest_units);
    }

    /// Get the time as a 32-bit value for conveniently serializing the time.
    /// Earlier time is always returned as a lower value.
    serialize_type Serialize() const throw()
    {
        return base_type::Serialize();
    }

    /// Set the time from a 32-bit value for conveniently serializing the time.
    /// Format of serialized_time will be in the same format returned from Serialize.
    void Deserialize(serialize_type serialized_time) throw()
    {
        base_type::Deserialize(serialized_time);
    }

    void Copy(type const& other) throw()
    {
        base_type::Copy(other);
    }

    void Swap(type& other) throw()
    {
        base_type::Swap(other);
    }

    void SetStart() throw()
    {
        base_type::SetStart();
    }

    void SetEnd() throw()
    {
        base_type::SetEnd();
    }
};

typedef Time<Milliseconds> TimeMs;
typedef Time<Nanoseconds>  TimeNs;

} // namespace ocl

#endif // OCL_GUARD_DATETIME_TIME_HPP
