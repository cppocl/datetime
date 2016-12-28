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

#ifndef OCL_GUARD_DATETIME_DATE_HPP
#define OCL_GUARD_DATETIME_DATE_HPP

#include <cstddef>

namespace ocl
{

/*
    Date class representing the Gregorian date format.
*/
class Date
{
// Types.
public:
    typedef uint32_t size_type;
    typedef uint8_t day_type;
    typedef uint8_t day_of_week_type;
    typedef uint8_t month_type;
    typedef uint16_t year_type;

// Constants.
public:
    static day_type const MIN_DAY = 1;
    static day_type const MAX_DAY = 31;
    static day_type const DAY_LEAP_YEAR = 29;

    static size_type const MONTHS_PER_YEAR = 12;

    static year_type const DEFAULT_YEAR = 1970;

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

// Static member functions.
public:
    // Specify month from 1 to 12.
    static size_type DaysInMonth(month_type month) throw()
    {
        static size_type const days[MONTHS_PER_YEAR] =
        {
            31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
        };

        return (month > 0 && month <= MONTHS_PER_YEAR) ? days[month-1] : static_cast<size_type>(0);
    }

    static bool IsLeapYear(year_type year) throw()
    {
        /* Leap year is when an extra day is added to February,
           making it 29 days on a leap year.
           To calculate the leap year, If the year is divisible by 4.
           If the year is divisible by 100 then it's not a leap year,
           unless the year is divisible by 400.
           Note that different countries adopted the Gregorian calendar
           in different years, and the last country adopted the calendar in 1927. */
        if ((year % 4) == 0)
        {
            if ((year % 100) == 0)
                return (year % 400) == 0;
            return true;
        }
        return false;
    }

    static bool IsLeapMonth(month_type month, year_type year) throw()
    {
        return month == FEBRUARY && IsLeapYear(year);
    }

// Constructors.
public:
    Date() throw()
        : m_day(MIN_DAY)
        , m_month(JANUARY)
        , m_year(DEFAULT_YEAR)
    {
    }

    // Set day (1..31), month (1..12) and year (e.g. 1970)
    Date(day_type day,
         month_type month,
         year_type year) throw()
    {
        SetDate(day, month, year);
    }

    Date(Date const& date) throw()
        : m_day(date.m_day)
        , m_month(date.m_month)
        , m_year(date.m_year)
    {
    }

// Overloaded operators.
public:
    Date& operator =(Date const& date) throw()
    {
        m_day = date.m_day;
        m_month = date.m_month;
        m_year = date.m_year;
        return *this;
    }

    bool operator <(Date const& date) const throw()
    {
        return Compare(date) < 0;
    }

    bool operator <=(Date const& date) const throw()
    {
        return Compare(date) <= 0;
    }

    bool operator >(Date const& date) const throw()
    {
        return Compare(date) > 0;
    }

    bool operator >=(Date const& date) const throw()
    {
        return Compare(date) >= 0;
    }

    bool operator ==(Date const& date) const throw()
    {
        return Compare(date) == 0;
    }

    bool operator !=(Date const& date) const throw()
    {
        return Compare(date) != 0;
    }

// Member functions.
public:
    // Get a day between 1 and 31.
    day_type GetDay() const throw()
    {
        return m_day;
    }

    // Set a day between 1 and 31.
    void SetDay(day_type day) throw()
    {
        if (day >= MIN_DAY)
            m_day = (day <= MAX_DAY) ? day : MAX_DAY;
        else
            m_day = MIN_DAY;
    }

    // Get a month between 1 and 12.
    month_type GetMonth() const throw()
    {
        return m_month;
    }

    // Set a month between 1 and 12.
    void SetMonth(month_type month) throw()
    {
        if (month >= MIN_MONTH)
            m_month = (month <= MAX_MONTH) ? month : MAX_MONTH;
        else
            m_month = MIN_MONTH;
    }

    year_type GetYear() const throw()
    {
        return m_year;
    }

    void SetYear(year_type year) throw()
    {
        m_year = year;
    }

    bool IsLeapYear() const throw()
    {
        return IsLeapYear(m_year);
    }

    // Get the date as a 32-bit value for conveniently serializing the date.
    uint32_t GetDate() const throw()
    {
        uint32_t date = m_day;
        date |= static_cast<uint32_t>(m_month) << 8U;
        date |= static_cast<uint32_t>(m_year) << 16U;
        return date;
    }

    // Set the date from a 32-bit value for conveniently serializing the date.
    void SetDate(uint32_t date) throw()
    {
        m_day = static_cast<day_type>(date);
        m_month = static_cast<month_type>(date >> 8U);
        m_year = static_cast<year_type>(date >> 16U);
    }

    void SetDate(day_type day, month_type month, year_type year) throw()
    {
        day_type days_in_month = DaysInMonth(month);
        if (day >= MIN_DAY)
        {
            if (day > days_in_month)
                m_day = IsLeapMonth(month, year) ? DAY_LEAP_YEAR : days_in_month;
            else
                m_day = day;
        }
        else
            m_day = MIN_DAY;
        SetMonth(month);
        SetYear(year);
    }

    void Copy(Date const& date) throw()
    {
        m_day = date.m_day;
        m_month = date.m_month;
        m_year = date.m_year;
    }

    int Compare(Date const& date) const throw()
    {
        uint32_t d1 = GetDate();
        uint32_t d2 = date.GetDate();
        return d1 > d2 ? 1 : (d1 < d2 ? -1 : 0);
    }

// Data (internal use only)
private:
    day_type   m_day;   // 1..31
    month_type m_month; // 1..12
    year_type  m_year;  // YYYY. e.g. 1970
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_DATE_HPP
