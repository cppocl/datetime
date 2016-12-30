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

class DateTime
{
// Types.
public:
    typedef Date::size_type size_type;
    typedef Date::day_type day_type;
    typedef Date::day_of_week_type day_of_week_type;
    typedef Date::month_type month_type;
    typedef Date::year_type year_type;
    typedef Time::millisecond_type millisecond_type;
    typedef Time::second_type second_type;
    typedef Time::minute_type minute_type;
    typedef Time::hour_type hour_type;

// Constants.
public:
    static day_type const MIN_DAY = Date::MIN_DAY;
    static day_type const MAX_DAY = Date::MAX_DAY;
    static day_type const DAY_LEAP_YEAR = Date::DAY_LEAP_YEAR;

    static size_type const MONTHS_PER_YEAR = Date::MONTHS_PER_YEAR;

    static year_type const DEFAULT_YEAR = Date::DEFAULT_YEAR;

    static day_of_week_type const SUNDAY = 0;
    static day_of_week_type const MONDAY = 1;
    static day_of_week_type const TUESDAY = 2;
    static day_of_week_type const WEDNESDAY = 3;
    static day_of_week_type const THURSDAY = 4;
    static day_of_week_type const FRIDAY = 5;
    static day_of_week_type const SATURDAY = 6;

    static month_type const JANUARY = 1;
    static month_type const FEBRUARY = 2;
    static month_type const MARCH = 3;
    static month_type const APRIL = 4;
    static month_type const MAY = 5;
    static month_type const JUNE = 6;
    static month_type const JULY = 7;
    static month_type const AUGUST = 8;
    static month_type const SEPTEMBER = 9;
    static month_type const OCTOBER = 10;
    static month_type const NOVEMBER = 11;
    static month_type const DECEMBER = 12;

    static month_type const MIN_MONTH = JANUARY;
    static month_type const MAX_MONTH = DECEMBER;

    static size_type const MILLISECONDS_PER_SECOND = Time::MILLISECONDS_PER_SECOND;
    static size_type const SECONDS_PER_MINUTE = Time::SECONDS_PER_MINUTE;
    static size_type const MINUTES_PER_HOUR = Time::MINUTES_PER_HOUR;
    static size_type const HOURS_PER_DAY = Time::HOURS_PER_DAY;

    static size_type const MILLISECONDS_PER_MINUTE = Time::MILLISECONDS_PER_MINUTE;
    static size_type const MILLISECONDS_PER_HOUR = Time::MILLISECONDS_PER_HOUR;
    static size_type const MILLISECONDS_PER_DAY = Time::MILLISECONDS_PER_DAY;

    static size_type const SECONDS_PER_HOUR = Time::SECONDS_PER_HOUR;
    static size_type const SECONDS_PER_DAY = Time::SECONDS_PER_DAY;

    static size_type const MINUTES_PER_DAY = Time::MINUTES_PER_DAY;

// Constructors.
public:
    DateTime() throw()
    {
    }

    DateTime(Date const& date, Time const& time) throw()
        : m_date(date)
        , m_time(time)
    {
    }

    DateTime(DateTime const& date_time) throw()
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
    DateTime& operator =(DateTime const& date_time) throw()
    {
        m_date.Copy(date_time.m_date);
        m_time.Copy(date_time.m_time);
        return *this;
    }

    bool operator <(DateTime const& date_time) const throw()
    {
        return Compare(date_time) < 0;
    }

    bool operator <=(DateTime const& date_time) const throw()
    {
        return Compare(date_time) <= 0;
    }

    bool operator >(DateTime const& date_time) const throw()
    {
        return Compare(date_time) > 0;
    }

    bool operator >=(DateTime const& date_time) const throw()
    {
        return Compare(date_time) >= 0;
    }

    bool operator ==(DateTime const& date_time) const throw()
    {
        return Compare(date_time) == 0;
    }

    bool operator !=(DateTime const& date_time) const throw()
    {
        return Compare(date_time) != 0;
    }

// Static member functions.
public:
    static size_type DaysInMonth(month_type month) throw()
    {
        return Date::DaysInMonth(month);
    }

    static bool IsLeapYear(year_type year) throw()
    {
        return Date::IsLeapYear(year);
    }

    static bool IsLeapMonth(month_type month, year_type year) throw()
    {
        return month == FEBRUARY && IsLeapYear(year);
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

    uint32_t GetDate() const throw()
    {
        return m_date.GetDate();
    }

    void SetDate(uint32_t date) throw()
    {
        m_date.SetDate(date);
    }

    uint32_t GetTime() const throw()
    {
        return m_time.GetTime();
    }

    void SetTime(uint32_t time) throw()
    {
        m_time.SetTime(time);
    }

    void SetDateTimne(uint32_t date, uint32_t time) throw()
    {
        m_date.SetDate(date);
        m_time.SetTime(time);
    }

    int Compare(DateTime const& date_time) const throw()
    {
        int date_cmp = m_date.Compare(date_time.m_date);
        return date_cmp != 0 ? date_cmp : m_time.Compare(date_time.m_time);
    }

// Data (internal use only)
private:
    Date m_date;
    Time m_time;
};

}

#endif // OCL_GUARD_DATETIME_DATETIME_HPP
