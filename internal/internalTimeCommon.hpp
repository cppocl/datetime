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

#ifndef OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMECOMMON_HPP
#define OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMECOMMON_HPP

namespace ocl
{

/// BaseTimeType would be internalTimeMs, internalTimeNs, etc.
template<typename BaseTimeType>
class InternalTimeCommon : public BaseTimeType
{
// Types (Internal use only).
private:
    typedef BaseTimeType base_type;

// Types.
public:
    typedef InternalTimeCommon<BaseTimeType> type;

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
    typedef typename base_type::smallest_unit_type    smallest_unit_type;

    /// Types for hours, minutes, seconds, milliseconds and nanoseconds,
    // that don't exceed their limit within a time period.
    typedef typename base_type::nanosecond_type       nanosecond_type;
    typedef typename base_type::microsecond_type      microsecond_type;
    typedef typename base_type::millisecond_type      millisecond_type;
    typedef typename base_type::second_type           second_type;
    typedef typename base_type::minute_type           minute_type;
    typedef typename base_type::hour_type             hour_type;

// Construction and destruction.
protected:
    InternalTimeCommon() throw()
    {
    }

    InternalTimeCommon(hour_type hours,             // 0..23
                       minute_type minutes) throw() // 0..59
        : base_type(hours, minutes)
    {
    }

    InternalTimeCommon(hour_type hours,             // 0..23
                       minute_type minutes,         // 0..59
                       second_type seconds) throw() // 0..59
        : base_type(hours, minutes, seconds)
    {
    }

    InternalTimeCommon(hour_type hours,                           // 0..23
                       minute_type minutes,                       // 0..59
                       second_type seconds,                       // 0..59
                       smallest_unit_type smallest_units) throw() // 0..999 or 0..999999999
        : base_type(hours, minutes, seconds, smallest_units)
    {
    }

    InternalTimeCommon(type const& other) throw()
        : base_type(other)
    {
    }

// Static member functions.
public:
    template<typename T>
    static T Min(T a, T b) throw()
    {
        return a < b ? a : b;
    }

    template<typename T>
    static T Max(T a, T b) throw()
    {
        return a > b ? a : b;
    }

// Comparison member functions.
public:
    bool IsLess(type const& other) const throw()
    {
        return Serialize() < other.Serialize();
    }

    bool IsLessEqual(type const& other) const throw()
    {
        return Serialize() <= other.Serialize();
    }

    bool IsGreater(type const& other) const throw()
    {
        return Serialize() > other.Serialize();
    }

    bool IsGreaterEqual(type const& other) const throw()
    {
        return Serialize() >= other.Serialize();
    }

    bool IsEqual(type const& other) const throw()
    {
        return Serialize() == other.Serialize();
    }

    bool IsNotEqual(type const& other) const throw()
    {
        return Serialize() != other.Serialize();
    }

    /// Add smallest units, which could be milliseconds, nanoseconds, etc, depending on precision.
    // The time will not exceed a whole day.
    void Add(size_type smallest_units_to_add) throw()
    {
        size_type smallest_units = Transform() + smallest_units_to_add;
        if (smallest_units >= UNITS_PER_DAY)
            SetEnd();
        else
            Transform(smallest_units);
    }

    /// Add smallest units, which could be milliseconds, nanoseconds, etc, depending on precision.
    // The time will not exceed a whole day, and overflow will be set if addition is too big.
    void Add(size_type smallest_units_to_add, size_type& overflow) throw()
    {
        size_type smallest_units = Transform() + smallest_units_to_add;
        if (smallest_units >= UNITS_PER_DAY)
        {
            overflow = 1U + smallest_units - UNITS_PER_DAY;
            SetEnd();
        }
        else
        {
            overflow = 0U;
            Transform(smallest_units);
        }
    }

    /// Subtract milliseconds to 0:0:0:0.
    void Subtract(size_type smallest_units_to_subtract) throw()
    {
        size_type smallest_units = Transform();
        if (smallest_units_to_subtract >= smallest_units)
            SetStart();
        else
            Transform(smallest_units - smallest_units_to_subtract);
    }

    /// Subtract smallest units, which could be milliseconds, nanoseconds, etc, depending on precision.
    // The time will not exceed 0:0:0:0, and underflow will be set if addition is too big.
    void Subtract(size_type smallest_units_to_subtract, size_type& underflow) throw()
    {
        size_type smallest_units = Transform();
        if (smallest_units_to_subtract > smallest_units)
        {
            underflow = smallest_units_to_subtract - smallest_units;
            SetStart();
        }
        else
        {
            underflow = 0U;
            Transform(smallest_units - smallest_units_to_subtract);
        }
    }

    /// Get the difference between this time and the other time in smallest units,
    /// i.e. milliseconds or nanoseconds.
    /// with this time expected to be less or equal to the other time.
    size_type GetDifference(type const& other) const throw()
    {
        size_type this_units = Transform();
        size_type other_units = other.Transform();
        return other_units - this_units;
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMECOMMON_HPP
