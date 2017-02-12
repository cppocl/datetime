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

#include <stdint.h>

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
    typedef int32_t diff_type;
    typedef uint8_t day_type;
    typedef uint8_t day_of_week_type;
    typedef uint8_t month_type;
    typedef uint16_t year_type;

// Constants.
public:
    static day_type const MIN_DAY = 1U;
    static day_type const MAX_DAY = 31U;
    static day_type const DAYS_IN_LEAP_FEBRUARY = 29U;

    static size_type const DAYS_PER_YEAR = 365U;
    static size_type const DAYS_PER_LEAP_YEAR = 366U;

    static day_type const DAYS_IN_JANUARY = 31U;
    static day_type const DAYS_IN_FEBRUARY = 28U;
    static day_type const DAYS_IN_MARCH = 31U;
    static day_type const DAYS_IN_APRIL = 30U;
    static day_type const DAYS_IN_MAY = 31U;
    static day_type const DAYS_IN_JUNE = 30U;
    static day_type const DAYS_IN_JULY = 31U;
    static day_type const DAYS_IN_AUGUST = 31U;
    static day_type const DAYS_IN_SEPTEMBER = 30U;
    static day_type const DAYS_IN_OCTOBER = 31U;
    static day_type const DAYS_IN_NOVEMBER = 30U;
    static day_type const DAYS_IN_DECEMBER = 31U;

    static size_type const MONTHS_PER_YEAR = 12U;

    static year_type const DEFAULT_YEAR = 1970U;

    static day_of_week_type const SUNDAY = 0U;
    static day_of_week_type const MONDAY = 1U;
    static day_of_week_type const TUESDAY = 2U;
    static day_of_week_type const WEDNESDAY = 3U;
    static day_of_week_type const THURSDAY = 4U;
    static day_of_week_type const FRIDAY = 5U;
    static day_of_week_type const SATURDAY = 6U;

    static month_type const JANUARY = 1U;
    static month_type const FEBRUARY = 2U;
    static month_type const MARCH = 3U;
    static month_type const APRIL = 4U;
    static month_type const MAY = 5U;
    static month_type const JUNE = 6U;
    static month_type const JULY = 7U;
    static month_type const AUGUST = 8U;
    static month_type const SEPTEMBER = 9U;
    static month_type const OCTOBER = 10U;
    static month_type const NOVEMBER = 11U;
    static month_type const DECEMBER = 12U;

    static month_type const MIN_MONTH = JANUARY;
    static month_type const MAX_MONTH = DECEMBER;

// Static member functions.
public:
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

    /// Get days in the month, ignoring leap year.
    static day_type GetDaysInMonth(month_type month) throw()
    {
        static day_type const days[MONTHS_PER_YEAR] =
        {
            DAYS_IN_JANUARY, DAYS_IN_FEBRUARY, DAYS_IN_MARCH,
            DAYS_IN_APRIL,   DAYS_IN_MAY,      DAYS_IN_JUNE,
            DAYS_IN_JULY,    DAYS_IN_AUGUST,   DAYS_IN_SEPTEMBER,
            DAYS_IN_OCTOBER, DAYS_IN_NOVEMBER, DAYS_IN_DECEMBER
        };

        return (month >= JANUARY && month <= DECEMBER) ? days[month - JANUARY]
                                                       : static_cast<size_type>(0);
    }

    /// Get days in the month, adjusting for the leap year and month.
    static day_type GetDaysInMonth(month_type month, year_type year) throw()
    {
        bool const is_leap_month = (month == FEBRUARY) && IsLeapYear(year);
        return is_leap_month ? DAYS_IN_LEAP_FEBRUARY : GetDaysInMonth(month);
    }

    static month_type GetNextMonth(month_type month) throw()
    {
        return month == DECEMBER ? JANUARY : month + 1U;
    }

    /// Move to next month and increment year, if month is December.
    static void MoveToNextMonth(month_type& month, year_type& year) throw()
    {
        if (month == DECEMBER)
        {
            month = JANUARY;
            ++year;
        }
        else
            ++month;
    }

    static month_type GetPreviousMonth(month_type month) throw()
    {
        return month == JANUARY ? DECEMBER : month - 1U;
    }

    /// Move to previous month and decrement year, if month is January.
    static void MoveToPreviousMonth(month_type& month, year_type& year) throw()
    {
        if (month == JANUARY)
        {
            month = DECEMBER;
            --year;
        }
        else
            --month;
    }

    /// Return remaining days in month, e.g.
    /// if it's 30th Jan then 1 is returned, ignoring leap year.
    static day_type GetDaysToEndOfMonth(day_type day, month_type month) throw()
    {
        return GetDaysInMonth(month) - day;
    }

    /// Return remaining days in month, e.g.
    /// if it's 30th Jan then 1 is returned, adjusting for the leap year and month.
    static day_type GetDaysToEndOfMonth(day_type day,
                                        month_type month,
                                        year_type year) throw()
    {
        return GetDaysInMonth(month, year) - day;
    }

    /// Get number of days in the year, adjusting for the leap year.
    static size_type GetDaysInYear(year_type year) throw()
    {
        return IsLeapYear(year) ? DAYS_PER_LEAP_YEAR : DAYS_PER_YEAR;
    }

    /// Get number of days in the year, adjusting for the leap year.
    static size_type GetDaysInYears(year_type start_year, year_type end_year) throw()
    {
        size_type days = 0U;

        // Total days until first leap year.
        while ((start_year <= end_year) && !IsLeapYear(start_year))
        {
            days += DAYS_PER_YEAR;
            ++start_year;
        }

        year_type years_to_leap_year = 0U; // First time in loop is always a leap year.
        while (start_year <= end_year)
        {
            if (years_to_leap_year == 0U)
            {
                days += IsLeapYear(start_year) ? DAYS_PER_LEAP_YEAR : DAYS_PER_YEAR;
                years_to_leap_year = 4U;
            }
            else
                days += DAYS_PER_YEAR;
            --years_to_leap_year;
            ++start_year;
        }

        return days;
    }

    /// Get days from 1st of January to current day and month for the year,
    /// adjusting for the leap year and month.
    static size_type GetDaysFromStartOfyear(day_type day,
                                            month_type month,
                                            year_type year) throw()
    {
        size_type days = 0U;
        month_type curr_month = JANUARY;
        while (curr_month < month)
            days += GetDaysInMonth(curr_month++, year);
        days += day - 1;
        return days;
    }

    /// Get number of days to end of year from current date, adjusting for leap year.
    static size_type GetDaysToEndOfYear(day_type day, month_type month, year_type year) throw()
    {
        size_type days = GetDaysToEndOfMonth(day, month++, year);
        while (month <= DECEMBER)
            days += GetDaysInMonth(month++, year);
        return days;
    }

    /// If the next day is less than the provided day, then it will be 1,
    /// as it has wrapped past end of month, ignoring leap year.
    static day_type GetNextDay(day_type day, month_type month) throw()
    {
        day_type days_in_month = GetDaysInMonth(month);
        day_type next_day = (day < days_in_month) ? day + 1U : MIN_DAY;
        return next_day;
    }

    /// If the next day is less than the provided day, then it will be 1,
    /// as it has wrapped past end of month, adjusting for the leap year and month.
    static day_type GetNextDay(day_type day, month_type month, year_type year) throw()
    {
        day_type days_in_month = GetDaysInMonth(month, year);
        day_type next_day = (day < days_in_month) ? day + 1U : MIN_DAY;
        return next_day;
    }

    /// If the previous day is more than the provided day,
    /// then it will be maximum day for the previous month,
    /// as it has wrapped past start of month, ignoring leap year.
    static day_type GetPreviousDay(day_type day, month_type month) throw()
    {
        day_type prev_day = (day > MIN_DAY) ? day - 1U : GetDaysInMonth(GetPreviousMonth(month));
        return prev_day;
    }

    /// If the previous day is more than the provided day,
    /// then it will be maximum day for the previous month,
    /// as it has wrapped past start of month, adjusting for the leap year and month.
    static day_type GetPreviousDay(day_type day, month_type month, year_type year) throw()
    {
        day_type prev_day;

        if (day > MIN_DAY)
            prev_day = day - 1U;
        else
            prev_day = GetDaysInMonth(GetPreviousMonth(month),
                                      month == MIN_MONTH ? year - 1U : year);

        return prev_day;
    }

    /// Calculates the number of days for next whole years,
    /// and days to end of the current year.
    /// If the user doesn't want to include the current year,
    /// then start from the 1st of January of the following year.
    /// Note that year will be updated to be the year past the counted days.
    /// The days returned will be the number of days up to the 1st of January,
    /// where there were not enough days remaining to complete a full year.
    static size_type AddDaysForYears(size_type days,
                                     day_type &day,
                                     month_type& month,
                                     year_type& year) throw()
    {
        size_type days_to_start_of_next_year = GetDaysToEndOfYear(day, month, year) + 1U;
        size_type total_days;

        if (days >= days_to_start_of_next_year)
        {
            day = MIN_DAY;
            month = JANUARY;
            total_days = days_to_start_of_next_year;
            days -= days_to_start_of_next_year;
            ++year;
            size_type days_in_year = GetDaysInYear(year);
            while (days >= days_in_year)
            {
                ++year;
                days -= days_in_year;
                total_days += days_in_year;
                days_in_year = GetDaysInYear(year);
            }
        }
        else
            total_days = 0U;

        return total_days;
    }

    /// Calculates the number of days for next whole months,
    /// and days to end of the current month.
    /// If the user doesn't want to include the current month,
    /// then start from the 1st of the following month.
    /// Note that month will be updated to be the month past the counted days.
    /// The days returned will be the number of days up to the 1st of the last month,
    /// where there were not enough days remaining to complete a full month.
    static size_type AddDaysForMonths(size_type days,
                                      day_type& day,
                                      month_type &month,
                                      year_type& year) throw()
    {
        size_type days_to_start_of_next_month = GetDaysToEndOfMonth(day, month, year) + 1U;
        size_type total_days;

        if (days >= days_to_start_of_next_month)
        {
            day = MIN_DAY;
            total_days = days_to_start_of_next_month;
            days -= days_to_start_of_next_month;
            MoveToNextMonth(month, year);
            size_type days_in_month = GetDaysInMonth(month, year);
            while (days >= days_in_month)
            {
                MoveToNextMonth(month, year);
                days -= days_in_month;
                total_days += days_in_month;
                days_in_month = GetDaysInMonth(month, year);
            }
        }
        else
            total_days = 0U;

        return total_days;
    }

    /// Calculates the number of days for previous whole years,
    /// and days to start of the current year.
    /// If the user doesn't want to include the current year,
    /// then start from the 1st of January of the current year.
    /// Note that year will be updated to be the year before the counted days.
    /// The days returned will be the number of days up to the 1st of January,
    /// where there were not enough days remaining to complete a full year.
    static size_type SubtractDaysForYears(size_type days,
                                          day_type& day,
                                          month_type& month,
                                          year_type& year) throw()
    {
        size_type days_to_end_of_prev_year = GetDaysFromStartOfyear(day, month, year) + 1U;
        size_type total_days;

        if (days >= days_to_end_of_prev_year)
        {
            day = DAYS_IN_DECEMBER;
            month = DECEMBER;
            total_days = days_to_end_of_prev_year;
            days -= days_to_end_of_prev_year;
            --year;
            size_type days_in_year = GetDaysInYear(year);
            while (days >= days_in_year)
            {
                --year;
                days -= days_in_year;
                total_days += days_in_year;
                days_in_year = GetDaysInYear(year);
            }
        }
        else
            total_days = 0U;

        return total_days;
    }

    /// Calculates the number of days for previous whole months,
    /// and days to start of the current month.
    /// If the user doesn't want to include the current month,
    /// then start from the 1st of the current month.
    /// Note that month will be updated to be the month past the counted days.
    /// The days returned will be the number of days up to the 1st of the last month,
    /// where there were not enough days remaining to complete a full month.
    static size_type SubtractDaysForMonths(size_type days,
                                           day_type& day,
                                           month_type &month,
                                           year_type& year) throw()
    {
        size_type total_days;

        if (days >= day)
        {
            total_days = day; // Count days to last day of previous month.
            days -= day;
            MoveToPreviousMonth(month, year);
            size_type days_in_month = GetDaysInMonth(month, year);
            day = days_in_month;
            while (days >= days_in_month)
            {
                MoveToPreviousMonth(month, year);
                days -= days_in_month;
                total_days += days_in_month;
                days_in_month = GetDaysInMonth(month, year);
                day = days_in_month;
            }
        }
        else
            total_days = 0U;

        return total_days;
    }

// Constructors.
public:
    Date() throw()
        : m_day(MIN_DAY)
        , m_month(JANUARY)
        , m_year(DEFAULT_YEAR)
    {
    }

    /// Set day (1..31), month (1..12) and year (e.g. 1970)
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
        SetDate(date);
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

    Date& operator +=(size_type days_to_add) throw()
    {
        AddDays(days_to_add);
        return *this;
    }

    Date& operator -=(size_type days_to_subtract) throw()
    {
        SubtractDays(days_to_subtract);
        return *this;
    }

    Date operator++() throw() // Prefix
    {
        IncrementDay();
        return *this;
    }

    Date operator++(int) throw() // Postfix
    {
        Date curr_date(*this);
        IncrementDay();
        return curr_date;
    }

    Date operator--() throw() // Prefix
    {
        DecrementDay();
        return *this;
    }

    Date operator--(int) throw() // Postfix
    {
        Date curr_date(*this);
        DecrementDay();
        return curr_date;
    }

// Member functions.
public:
    /// Get a day between 1 and 31.
    day_type GetDay() const throw()
    {
        return m_day;
    }

    /// Set a day between 1 and max days for current month and year, with leap year handled.
    void SetDay(day_type day) throw()
    {
        privateSetDay(day, GetMonth(), GetYear());
    }

    /// Get a month between 1 and 12.
    month_type GetMonth() const throw()
    {
        return m_month;
    }

    /// Set a month between 1 and 12.
    void SetMonth(month_type month) throw()
    {
        if (month >= MIN_MONTH)
            m_month = (month <= MAX_MONTH) ? month : MAX_MONTH;
        else
            m_month = MIN_MONTH;
    }

    /// Get the year as is, i.e. 1990.
    year_type GetYear() const throw()
    {
        return m_year;
    }

    /// Set the year as is, i.e. 1990.
    void SetYear(year_type year) throw()
    {
        m_year = year;
    }

    bool IsLeapYear() const throw()
    {
        return IsLeapYear(GetYear());
    }

    year_type GetNextLeapYear() const throw()
    {
        year_type year = GetYear() + 1U;
        while (!IsLeapYear(year))
            ++year;
        return year;
    }

    day_type GetDaysInMonth() const throw()
    {
        return GetDaysInMonth(GetMonth(), GetYear());
    }

    size_type GetDaysToEndOfMonth() const throw()
    {
        return GetDaysToEndOfMonth(GetDay(), GetMonth(), GetYear());
    }

    size_type GetDaysFromStartOfyear() const throw()
    {
        return GetDaysFromStartOfyear(GetDay(), GetMonth(), GetYear());
    }

    size_type GetDaysToEndOfYear() const throw()
    {
        return GetDaysToEndOfYear(GetDay(), GetMonth(), GetYear());
    }

    size_type GetDaysInYear() const throw()
    {
        return GetDaysInYear(GetYear());
    }

    /// Set to the 1st of January for the current year.
    void SetStartOfYear() throw()
    {
        SetDay(1U);
        SetMonth(JANUARY);
    }

    /// Set to the 1st of January for the current year, and return numbers of days to start.
    void SetStartOfYear(size_type& days_to_start) throw()
    {
        days_to_start = GetDaysFromStartOfyear();
        SetDay(1U);
        SetMonth(JANUARY);
    }

    /// Set to the 31st of December for the current year.
    void SetEndtOfYear() throw()
    {
        SetDay(DAYS_IN_DECEMBER);
        SetMonth(DECEMBER);
    }

    /// Set to the 31st of December for the current year, and return numbers of days to end.
    void SetEndtOfYear(size_type& days_to_end) throw()
    {
        days_to_end = GetDaysToEndOfMonth();
        SetDay(DAYS_IN_DECEMBER);
        SetMonth(DECEMBER);
    }

    /// Get the date as a 32-bit value for conveniently serializing the date.
    uint32_t GetDate() const throw()
    {
        uint32_t date = m_day;
        date |= static_cast<uint32_t>(m_month) << 8U;
        date |= static_cast<uint32_t>(m_year) << 16U;
        return date;
    }

    /// Set the date from a 32-bit value for conveniently serializing the date.
    void SetDate(uint32_t date) throw()
    {
        m_day = static_cast<day_type>(date);
        m_month = static_cast<month_type>(date >> 8U);
        m_year = static_cast<year_type>(date >> 16U);
    }

    void SetDate(Date const& date) throw()
    {
        m_day = date.m_day;
        m_month = date.m_month;
        m_year = date.m_year;
    }

    void SetDate(day_type day, month_type month, year_type year) throw()
    {
        privateSetDay(day, month, year);
        SetMonth(month);
        SetYear(year);
    }

    /// Increment the day, wrapping the month and year if required.
    /// This is also adjusted for leap year.
    void IncrementDay() throw()
    {
        month_type month = GetMonth();
        year_type year = GetYear();
        day_type next_day = GetNextDay(GetDay(), month, year);
        if (next_day == MIN_DAY)
        {
            month_type next_month = GetNextMonth(month);
            if (next_month == MIN_MONTH)
                SetYear(year + 1U);
            SetMonth(next_month);
        }
        SetDay(next_day);
    }

    /// Decrement the day, wrapping the month and year if required.
    /// This is also adjusted for leap year.
    void DecrementDay() throw()
    {
        day_type day = GetDay();
        month_type month = GetMonth();
        year_type year = GetYear();
        day_type prev_day = GetPreviousDay(day, month, year);
        if (day == MIN_DAY)
        {
            month_type prev_month = GetPreviousMonth(month);
            if (prev_month == MAX_MONTH)
                SetYear(year - 1U);
            SetMonth(prev_month);
        }
        SetDay(prev_day);
    }

    /// Moves onto next month, wrapping year if required.
    /// If the day is past the limit for the next month, the day is
    /// adjusted to the valid maximum day, taking into consideration leap year.
    void IncrementMonth() throw()
    {
        day_type day = GetDay();
        month_type month = GetMonth();
        year_type year = GetYear();
        month_type next_month = GetNextMonth(month);
        day_type max_days = GetDaysInMonth(next_month, year);
        if (day > max_days)
            SetDay(max_days); // Limit day in month to valid range.
        SetMonth(next_month);
        if (next_month == MIN_MONTH)
            SetYear(year + 1U);
    }

    /// Moves onto previous month, wrapping year if required.
    /// If the day is past the limit for the previous month, the day is
    /// adjusted to the valid maximum day, taking into consideration leap year.
    void DecrementMonth() throw()
    {
        day_type day = GetDay();
        month_type month = GetMonth();
        year_type year = GetYear();
        month_type prev_month = GetPreviousMonth(month);
        day_type max_days = GetDaysInMonth(prev_month, year);
        if (day > max_days)
            SetDay(max_days); // Limit day in month to valid range.
        SetMonth(prev_month);
        if (prev_month == MAX_MONTH)
            SetYear(year - 1U);
    }

    void AddDays(size_type days)
    {
        if (days > 0U)
        {
            year_type year = GetYear();
            month_type month = GetMonth();
            day_type day = GetDay();
            // Remove days to end of year and days for whole next years.
            days -= AddDaysForYears(days, day, month, year);
            // Remove days to end of month and days for whole next month.
            days -= AddDaysForMonths(days, day, month, year);
            if (days > 0U)
                day = static_cast<day_type>(day + days);
            SetDate(day, month, year);
        }
    }

    void SubtractDays(size_type days)
    {
        if (days > 0U)
        {
            year_type year = GetYear();
            month_type month = GetMonth();
            day_type day = GetDay();
            // Remove days to start of year and days for whole previous years.
            days -= SubtractDaysForYears(days, day, month, year);
            // Remove days to start of month and days for whole previous month.
            days -= SubtractDaysForMonths(days, day, month, year);
            day_type days_in_month = GetDaysInMonth(month, year);
            if (day > days)
                day = static_cast<day_type>(day - days);
            SetDate(day, month, year);
        }
    }

    int Compare(Date const& date) const throw()
    {
        uint32_t d1 = GetDate();
        uint32_t d2 = date.GetDate();
        return d1 > d2 ? 1 : (d1 < d2 ? -1 : 0);
    }

private:
    void privateSetDay(day_type day, month_type month, year_type year) throw()
    {
        if (day >= MIN_DAY)
        {
            day_type days_in_month = GetDaysInMonth(month, year);
            m_day = (day <= days_in_month) ? day : days_in_month;
        }
        else
            m_day = MIN_DAY;
    }

// Data (internal use only)
private:
    day_type   m_day;   /// 1..31
    month_type m_month; /// 1..12
    year_type  m_year;  /// YYYY. e.g. 1970
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_DATE_HPP
