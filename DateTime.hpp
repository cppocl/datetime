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

#ifndef OCL_GUARD_DATETIME_DATETIME_HPP
#define OCL_GUARD_DATETIME_DATETIME_HPP

#include "Date.hpp"
#include "Time.hpp"

namespace ocl
{

template<TimePrecision precision>
class DateTime
{
// Types.
public:
    typedef          Date                             date_type;
    typedef          Time<precision>                  time_type;
    typedef          DateTime<precision>              date_time_type;

    typedef          date_type::size_type             date_size_type;
    typedef          date_type::diff_type             date_diff_type;
    typedef          date_type::day_type              day_type;
    typedef          date_type::day_of_week_type      day_of_week_type;
    typedef          date_type::month_type            month_type;
    typedef          date_type::year_type             year_type;
    typedef typename time_type::serialize_type        serialize_time_type;
    typedef typename date_type::serialize_type        serialize_date_type;
    typedef typename time_type::smallest_unit_type    smallest_unit_type;

    typedef typename time_type::size_type             time_size_type;
    typedef typename time_type::diff_type             time_diff_type;
    typedef typename time_type::nanosecond_size_type  nanosecond_size_type;
    typedef typename time_type::nanosecond_diff_type  nanosecond_diff_type;
    typedef typename time_type::millisecond_size_type millisecond_size_type;
    typedef typename time_type::millisecond_diff_type millisecond_diff_type;
    typedef typename time_type::nanosecond_type       nanosecond_type;
    typedef typename time_type::millisecond_type      millisecond_type;
    typedef typename time_type::second_type           second_type;
    typedef typename time_type::minute_type           minute_type;
    typedef typename time_type::hour_type             hour_type;

// Constants.
public:
    // Date related constants.
    static day_type const              MIN_DAY                 = date_type::MIN_DAY;
    static day_type const              MAX_DAY                 = date_type::MAX_DAY;
    static day_type const              DAYS_IN_LEAP_FEBRUARY   = date_type::DAYS_IN_LEAP_FEBRUARY;

    static date_size_type const        MONTHS_PER_YEAR         = date_type::MONTHS_PER_YEAR;

    static year_type const             DEFAULT_YEAR            = date_type::DEFAULT_YEAR;

    static day_of_week_type const      SUNDAY                  = date_type::SUNDAY;
    static day_of_week_type const      MONDAY                  = date_type::MONDAY;
    static day_of_week_type const      TUESDAY                 = date_type::TUESDAY;
    static day_of_week_type const      WEDNESDAY               = date_type::WEDNESDAY;
    static day_of_week_type const      THURSDAY                = date_type::THURSDAY;
    static day_of_week_type const      FRIDAY                  = date_type::FRIDAY;
    static day_of_week_type const      SATURDAY                = date_type::SATURDAY;

    static month_type const            JANUARY                 = date_type::JANUARY;
    static month_type const            FEBRUARY                = date_type::FEBRUARY;
    static month_type const            MARCH                   = date_type::MARCH;
    static month_type const            APRIL                   = date_type::APRIL;
    static month_type const            MAY                     = date_type::MAY;
    static month_type const            JUNE                    = date_type::JUNE;
    static month_type const            JULY                    = date_type::JULY;
    static month_type const            AUGUST                  = date_type::AUGUST;
    static month_type const            SEPTEMBER               = date_type::SEPTEMBER;
    static month_type const            OCTOBER                 = date_type::OCTOBER;
    static month_type const            NOVEMBER                = date_type::NOVEMBER;
    static month_type const            DECEMBER                = date_type::DECEMBER;

    static month_type const            MIN_MONTH               = date_type::MIN_MONTH;
    static month_type const            MAX_MONTH               = date_type::MAX_MONTH;

    // Time related constants.
    static nanosecond_type const       NANOSECONDS_PER_SECOND  = time_type::NANOSECONDS_PER_SECOND;
    static millisecond_type const      MILLISECONDS_PER_SECOND = time_type::MILLISECONDS_PER_SECOND;
    static second_type const           SECONDS_PER_MINUTE      = time_type::SECONDS_PER_MINUTE;
    static minute_type const           MINUTES_PER_HOUR        = time_type::MINUTES_PER_HOUR;
    static hour_type const             HOURS_PER_DAY           = time_type::HOURS_PER_DAY;

    static nanosecond_size_type const  NANOSECONDS_PER_MINUTE  = time_type::NANOSECONDS_PER_MINUTE;
    static nanosecond_size_type const  NANOSECONDS_PER_HOUR    = time_type::NANOSECONDS_PER_HOUR;
    static nanosecond_size_type const  NANOSECONDS_PER_DAY     = time_type::NANOSECONDS_PER_DAY;

    static time_size_type const        MILLISECONDS_PER_MINUTE = time_type::MILLISECONDS_PER_MINUTE;
    static time_size_type const        MILLISECONDS_PER_HOUR   = time_type::MILLISECONDS_PER_HOUR;
    static time_size_type const        MILLISECONDS_PER_DAY    = time_type::MILLISECONDS_PER_DAY;

    static time_size_type const        SECONDS_PER_HOUR        = time_type::SECONDS_PER_HOUR;
    static time_size_type const        SECONDS_PER_DAY         = time_type::SECONDS_PER_DAY;

    static time_size_type const        MINUTES_PER_DAY         = time_type::MINUTES_PER_DAY;

    /// Maximum values for milliseconds, seconds, minutes and hours.
    static nanosecond_type const       NANOSECONDS_UPPER_BOUND         = time_type::NANOSECONDS_UPPER_BOUND;
    static millisecond_type const      MILLISECONDS_UPPER_BOUND        = time_type::MILLISECONDS_UPPER_BOUND;
    static second_type const           SECONDS_UPPER_BOUND             = time_type::SECONDS_UPPER_BOUND;
    static minute_type const           MINUTES_UPPER_BOUND             = time_type::MINUTES_UPPER_BOUND;
    static hour_type const             HOURS_UPPER_BOUND               = time_type::HOURS_UPPER_BOUND;

// Constructors.
public:
    DateTime() throw()
    {
    }

    explicit DateTime(Date const& date) throw()
        : m_date(date)
    {
    }

    DateTime(Date const& date, time_type const& time) throw()
        : m_date(date)
        , m_time(time)
    {
    }

    DateTime(date_time_type const& date_time) throw()
        : m_date(date_time.m_date)
        , m_time(date_time.m_time)
    {
    }

    DateTime(day_type day,              // 1..31
             month_type month,          // 1..12
             year_type year,
             hour_type hours,           // 0..23
             minute_type minutes,       // 0..59
             second_type seconds,       // 0..59
             millisecond_type milliseconds) throw() // 0..999
        : m_date(day, month, year)
        , m_time(hours, minutes, seconds, milliseconds)
    {
    }

// Overloaded operators.
public:
    date_time_type& operator =(date_time_type const& date_time) throw()
    {
        m_date.Copy(date_time.m_date);
        m_time.Copy(date_time.m_time);
        return *this;
    }

    bool operator <(date_time_type const& date_time) const throw()
    {
        return Compare(date_time) < 0;
    }

    bool operator <=(date_time_type const& date_time) const throw()
    {
        return Compare(date_time) <= 0;
    }

    bool operator >(date_time_type const& date_time) const throw()
    {
        return Compare(date_time) > 0;
    }

    bool operator >=(date_time_type const& date_time) const throw()
    {
        return Compare(date_time) >= 0;
    }

    bool operator ==(date_time_type const& date_time) const throw()
    {
        return Compare(date_time) == 0;
    }

    bool operator !=(date_time_type const& date_time) const throw()
    {
        return Compare(date_time) != 0;
    }

// Static member functions.
public:
    static date_size_type GetDaysInMonth(month_type month) throw()
    {
        return date_type::GetDaysInMonth(month);
    }

    static bool IsLeapYear(year_type year) throw()
    {
        return date_type::IsLeapYear(year);
    }

    static bool IsLeapMonth(month_type month, year_type year) throw()
    {
        return date_type::IsLeapMonth(month, year);
    }

    /// Get the difference in days and time units between tow DateTime objects.
    /// The first date/time must be less or equal to the second date/time,
    /// or then results will be unexpected.
    static void GetDifference(date_time_type const& first,
                              date_time_type const& second,
                              date_size_type& days,
                              time_size_type& units) throw()
    {
        Date const& first_date  = first.m_date;
        time_type const& first_time  = first.m_time;
        Date const& second_date = second.m_date;
        time_type const& second_time = second.m_time;

        if (first_date < second_date)
        {
            days = first_date.GetDifferenceInDays(second_date);
            if (first_time > second_time)
            {
                --days;
                time_size_type diff = second_time.GetDifference(first_time);
                units = time_type::UNITS_PER_DAY - diff;
            }
            else
                units = first_time.GetDifference(second_time);
        }
        else
        {
            days = 0U;
            // It's assumed the second time is less or equal to the first time.
            units = first_time.GetDifference(second_time);
        }
    }

    /// Get the difference in milliseconds between tow DateTime objects.
    /// The first date/time must be less or equal to the second date/time,
    /// or then results will be unexpected.
    template<typename return_type>
    static void GetDifference(date_time_type const& first,
                              date_time_type const& second,
                              return_type& units) throw()
    {
        date_size_type days;
        GetDifference(first, second, days, units);
        units += static_cast<return_type>(days) *
                 static_cast<return_type>(time_type::UNITS_PER_DAY);
    }

    static date_time_type const& Min(date_time_type const& first, date_time_type const& second) throw()
    {
        return first < second ? first : second;
    }

    static date_time_type const& Max(date_time_type const& first, date_time_type const& second) throw()
    {
        return first > second ? first : second;
    }

// Member functions.
public:
    day_type GetDay() const throw()
    {
        return m_date.GetDay();
    }

    // Set a day between 1 and 31.
    void SetDay(day_type day) throw()
    {
        m_date.SetDay(day);
    }

    // Get a month between 1 and 12.
    month_type GetMonth() const throw()
    {
        return m_date.GetMonth();
    }

    // Set a month between 1 and 12.
    void SetMonth(month_type month) throw()
    {
        m_date.SetMonth(month);
    }

    year_type GetYear() const throw()
    {
        return m_date.GetYear();
    }

    void SetYear(year_type year) throw()
    {
        m_date.SetYear(year);
    }

    bool IsLeapYear() const throw()
    {
        return m_date.IsLeapYear();
    }

    nanosecond_type GetNanoseconds() const throw()
    {
        return m_time.GetNanoseconds();
    }

    void SetNanoseconds(nanosecond_type nanoseconds) throw()
    {
        m_time.SetNanoseconds(nanoseconds);
    }

    millisecond_type GetMilliseconds() const throw()
    {
        return m_time.GetMilliseconds();
    }

    void SetMilliseconds(millisecond_type milliseconds) throw()
    {
        m_time.SetMilliseconds(milliseconds);
    }

    second_type GetSeconds() const throw()
    {
        return m_time.GetSeconds();
    }

    void SetSeconds(second_type seconds) throw()
    {
        m_time.SetSeconds(seconds);
    }

    minute_type GetMinutes() const throw()
    {
        return m_time.GetMinutes();
    }

    void SetMinutes(minute_type minutes) throw()
    {
        m_time.SetMinutes(minutes);
    }

    hour_type GetHours() const throw()
    {
        return m_time.GetHours();
    }

    void SetHours(hour_type hours) throw()
    {
        m_time.SetHours(hours);
    }

    serialize_date_type SerializeDate() const throw()
    {
        return m_date.Serialize();
    }

    void DeserializeDate(serialize_date_type date) throw()
    {
        m_date.Deserialize(date);
    }

    void Copy(Date const& date) throw()
    {
        m_date.Copy(date);
    }

    void SetDate(day_type day, month_type month, year_type year) throw()
    {
        m_date.SetDate(day, month, year);
    }

    serialize_time_type SerializeTime() const throw()
    {
        return m_time.Serialize();
    }

    void DeserializeTime(serialize_time_type time) throw()
    {
        m_time.Deserialize(time);
    }

    void SetTime(time_type const& time) throw()
    {
        m_time.SetTime(time);
    }

    void SetTime(hour_type hours,
                 minute_type minutes,
                 second_type seconds,
                 millisecond_type milliseconds) throw()
    {
        m_time.SetTime(hours, minutes, seconds, milliseconds);
    }

    void SetStartTime() throw()
    {
        m_time.SetStart();
    }

    void SetEndTime() throw()
    {
        m_time.SetEnd();
    }

    void Deserialize(serialize_date_type date, serialize_time_type time) throw()
    {
        m_date.Deserialize(date);
        m_time.Deserialize(time);
    }

    void Copy(date_time_type const date_time) throw()
    {
        m_date.Copy(date_time.m_date);
        m_time.Copy(date_time.m_time);
    }

    void AddDays(date_size_type days) throw()
    {
        m_date.AddDays(days);
    }

    /// Add milliseconds or nanoseconds, incrementing days
    /// if the milliseconds or nanoseconds overflows the time.
    void Add(time_size_type units) throw()
    {
        time_size_type overflow = 0U;
        m_time.Add(units, overflow);
        if (overflow > 0U)
        {
            --overflow;
            date_size_type overflow_days = static_cast<date_size_type>(overflow / time_type::UNITS_PER_DAY);
            if (overflow_days > 0)
            {
                m_date.AddDays(overflow_days + 1U);
                overflow -= overflow_days * time_type::UNITS_PER_DAY;
            }
            else
                m_date.IncrementDay();

            // Subtract 1 as an overflow of 1 would set time to 0:0:0:0.
            m_time.SetStart();
            m_time.Add(overflow);
        }
    }

    /// Subtract milliseconds or nanoseconds, decrementing days
    /// if the milliseconds or nanoseconds underflows the time.
    void Subtract(time_size_type units) throw()
    {
        time_size_type underflow = 0U;
        m_time.Subtract(units, underflow);
        if (underflow > 0U)
        {
            --underflow;
            date_size_type underflow_days = static_cast<date_size_type>(underflow / time_type::UNITS_PER_DAY);
            if (underflow_days > 0)
            {
                m_date.SubtractDays(underflow_days + 1U);
                underflow -= underflow_days * time_type::UNITS_PER_DAY;
            }
            else
                m_date.DecrementDay();

            // Subtract 1 as an overflow of 1 would set time to 0:0:0:0.
            m_time.SetEnd();
            m_time.Subtract(underflow);
        }
    }

    /// Get difference in days and milliseconds.
    /// Other DateTime object is expected to greater or equal to this DateTime object.
    void GetDifference(date_time_type const& other,
                       date_size_type& days,
                       time_size_type& milliseconds) const throw()
    {
        GetDifference(*this, other, days, milliseconds);
    }

    /// Get difference in milliseconds.
    /// Other DateTime object is expected to greater or equal to this DateTime object.
    template<typename return_type>
    void GetDifference(date_time_type const& other, return_type& milliseconds) const throw()
    {
        GetDifference<return_type>(*this, other, milliseconds);
    }

    void Swap(date_time_type& other) throw()
    {
        m_date.Swap(other.m_date);
        m_time.Swap(other.m_time);
    }

    /// Return 0 when the same, -1 when less than other date or 1 when greater than other date.
    int Compare(date_time_type const& other) const throw()
    {
        int date_cmp = m_date.Compare(other.m_date);
        return date_cmp != 0 ? date_cmp : m_time.Compare(other.m_time);
    }

// Data (internal use only)
private:
    Date m_date;
    time_type m_time;
};

typedef DateTime<Milliseconds> DateTimeMs;
typedef DateTime<Nanoseconds>  DateTimeNs;

}

#endif // OCL_GUARD_DATETIME_DATETIME_HPP
