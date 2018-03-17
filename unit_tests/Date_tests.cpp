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

#include "../../unit_test_framework/test/Test.hpp"
#include "../Date.hpp"

using ocl::Date;

TEST_MEMBER_FUNCTION(Date, IsLeapYear, year_type)
{
    CHECK_FALSE(Date::IsLeapYear(1800U));
    CHECK_FALSE(Date::IsLeapYear(1900U));
    CHECK_TRUE(Date::IsLeapYear(2000U));
    CHECK_FALSE(Date::IsLeapYear(2003U));
    CHECK_TRUE(Date::IsLeapYear(2004U));
    CHECK_FALSE(Date::IsLeapYear(2005U));
    CHECK_FALSE(Date::IsLeapYear(2006U));
    CHECK_FALSE(Date::IsLeapYear(2007U));
    CHECK_TRUE(Date::IsLeapYear(2008U));
    CHECK_FALSE(Date::IsLeapYear(2100U));
    CHECK_FALSE(Date::IsLeapYear(2200U));
}

TEST_CONST_MEMBER_FUNCTION(Date, IsLeapMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 1800U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 1900U));
    CHECK_TRUE(Date::IsLeapMonth(Date::FEBRUARY, 2000U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 2003U));
    CHECK_TRUE(Date::IsLeapMonth(Date::FEBRUARY, 2004U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 2005U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 2006U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 2007U));
    CHECK_TRUE(Date::IsLeapMonth(Date::FEBRUARY, 2008U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 2100U));
    CHECK_FALSE(Date::IsLeapMonth(Date::FEBRUARY, 2200U));

    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 1800U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 1900U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2000U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2003U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2004U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2005U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2006U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2007U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2008U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2100U));
    CHECK_FALSE(Date::IsLeapMonth(Date::JANUARY, 2200U));
}

TEST_MEMBER_FUNCTION(Date, GetDaysInMonth, month_type)
{
    Date::day_type days_in_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    for (Date::month_type month = Date::MIN_MONTH; month <= Date::MAX_MONTH; ++month)
        CHECK_EQUAL(days_in_month[month - Date::JANUARY], Date::GetDaysInMonth(month));
}

TEST_MEMBER_FUNCTION(Date, GetDaysInMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    Date::day_type days_in_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    Date::day_type days_in_leap_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    // Test days in month for a non-leap year.
    for (Date::month_type month = Date::MIN_MONTH; month <= Date::MAX_MONTH; ++month)
        CHECK_EQUAL(days_in_month[month - Date::JANUARY], Date::GetDaysInMonth(month, 2007U));

    // Test days in month for a leap year.
    for (Date::month_type month = Date::MIN_MONTH; month <= Date::MAX_MONTH; ++month)
        CHECK_EQUAL(days_in_leap_month[month - Date::JANUARY], Date::GetDaysInMonth(month, 2008U));
}

TEST_MEMBER_FUNCTION(Date, GetNextMonth, month_type)
{
    CHECK_EQUAL(Date::GetNextMonth(Date::JANUARY), Date::FEBRUARY);
    CHECK_EQUAL(Date::GetNextMonth(Date::FEBRUARY), Date::MARCH);
    CHECK_EQUAL(Date::GetNextMonth(Date::MARCH), Date::APRIL);
    CHECK_EQUAL(Date::GetNextMonth(Date::APRIL), Date::MAY);
    CHECK_EQUAL(Date::GetNextMonth(Date::MAY), Date::JUNE);
    CHECK_EQUAL(Date::GetNextMonth(Date::JUNE), Date::JULY);
    CHECK_EQUAL(Date::GetNextMonth(Date::JULY), Date::AUGUST);
    CHECK_EQUAL(Date::GetNextMonth(Date::AUGUST), Date::SEPTEMBER);
    CHECK_EQUAL(Date::GetNextMonth(Date::SEPTEMBER), Date::OCTOBER);
    CHECK_EQUAL(Date::GetNextMonth(Date::OCTOBER), Date::NOVEMBER);
    CHECK_EQUAL(Date::GetNextMonth(Date::NOVEMBER), Date::DECEMBER);
    CHECK_EQUAL(Date::GetNextMonth(Date::DECEMBER), Date::JANUARY);
}

TEST_MEMBER_FUNCTION(Date, SetToNextMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    Date::month_type month = Date::JANUARY;
    Date::year_type year = 2000U;

    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::FEBRUARY);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::MARCH);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::APRIL);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::MAY);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::JUNE);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::JULY);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::AUGUST);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::SEPTEMBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::OCTOBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::NOVEMBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::DECEMBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToNextMonth(month, year);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2001U);
}

TEST_MEMBER_FUNCTION(Date, GetPreviousMonth, month_type)
{
    CHECK_EQUAL(Date::GetPreviousMonth(Date::JANUARY), Date::DECEMBER);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::FEBRUARY), Date::JANUARY);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::MARCH), Date::FEBRUARY);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::APRIL), Date::MARCH);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::MAY), Date::APRIL);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::JUNE), Date::MAY);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::JULY), Date::JUNE);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::AUGUST), Date::JULY);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::SEPTEMBER), Date::AUGUST);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::OCTOBER), Date::SEPTEMBER);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::NOVEMBER), Date::OCTOBER);
    CHECK_EQUAL(Date::GetPreviousMonth(Date::DECEMBER), Date::NOVEMBER);
}

TEST_MEMBER_FUNCTION(Date, SetToPreviousMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    Date::month_type month = Date::JANUARY;
    Date::year_type year = 2001U;

    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::DECEMBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::NOVEMBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::OCTOBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::SEPTEMBER);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::AUGUST);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::JULY);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::JUNE);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::MAY);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::APRIL);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::MARCH);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::FEBRUARY);
    CHECK_EQUAL(year, 2000U);
    Date::SetToPreviousMonth(month, year);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2000U);
}

TEST_MEMBER_FUNCTION(Date, GetDaysToEndOfMonth, day_type_month_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type");

    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::JANUARY), Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::FEBRUARY), Date::DAYS_IN_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::MARCH), Date::DAYS_IN_MARCH - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::APRIL), Date::DAYS_IN_APRIL - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::MAY), Date::DAYS_IN_MAY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::JUNE), Date::DAYS_IN_JUNE - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::JULY), Date::DAYS_IN_JULY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::AUGUST), Date::DAYS_IN_AUGUST - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::SEPTEMBER), Date::DAYS_IN_SEPTEMBER - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::OCTOBER), Date::DAYS_IN_OCTOBER - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::NOVEMBER), Date::DAYS_IN_NOVEMBER - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::DECEMBER), Date::DAYS_IN_DECEMBER - 1U);

    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_JANUARY, Date::JANUARY), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_MARCH, Date::MARCH), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_APRIL, Date::APRIL), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_MAY, Date::MAY), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_JUNE, Date::JUNE), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_JULY, Date::JULY), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_AUGUST, Date::AUGUST), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_SEPTEMBER, Date::SEPTEMBER), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_OCTOBER, Date::OCTOBER), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_NOVEMBER, Date::NOVEMBER), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_DECEMBER, Date::DECEMBER), 0U);
}

TEST_MEMBER_FUNCTION(Date, GetDaysToEndOfMonth, day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type");

    Date::year_type year = 2007U;

    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::FEBRUARY, year), Date::DAYS_IN_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::FEBRUARY, year + 1U), Date::DAYS_IN_LEAP_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::MARCH, year), Date::DAYS_IN_MARCH - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::APRIL, year), Date::DAYS_IN_APRIL - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::MAY, year), Date::DAYS_IN_MAY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::JUNE, year), Date::DAYS_IN_JUNE - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::JULY, year), Date::DAYS_IN_JULY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::AUGUST, year), Date::DAYS_IN_AUGUST - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::SEPTEMBER, year), Date::DAYS_IN_SEPTEMBER - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::OCTOBER, year), Date::DAYS_IN_OCTOBER - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::NOVEMBER, year), Date::DAYS_IN_NOVEMBER - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(1U, Date::DECEMBER, year), Date::DAYS_IN_DECEMBER - 1U);

    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_JANUARY, Date::JANUARY, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_LEAP_FEBRUARY, Date::FEBRUARY, year + 1U), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_MARCH, Date::MARCH, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_APRIL, Date::APRIL, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_MAY, Date::MAY, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_JUNE, Date::JUNE, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_JULY, Date::JULY, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_AUGUST, Date::AUGUST, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_SEPTEMBER, Date::SEPTEMBER, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_OCTOBER, Date::OCTOBER, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_NOVEMBER, Date::NOVEMBER, year), 0U);
    CHECK_EQUAL(Date::GetDaysToEndOfMonth(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 0U);
}

TEST_MEMBER_FUNCTION(Date, GetDaysInYear, year_type)
{
    CHECK_EQUAL(Date::GetDaysInYear(1900U), Date::DAYS_PER_YEAR);
    CHECK_EQUAL(Date::GetDaysInYear(2000U), Date::DAYS_PER_LEAP_YEAR);
    CHECK_EQUAL(Date::GetDaysInYear(2007U), Date::DAYS_PER_YEAR);
    CHECK_EQUAL(Date::GetDaysInYear(2008U), Date::DAYS_PER_LEAP_YEAR);
}

TEST_MEMBER_FUNCTION(Date, GetDaysInYears, year_type_yeae_type)
{
    TEST_OVERRIDE_ARGS("year_type, year_type");

    CHECK_EQUAL(Date::GetDaysInYears(1900U, 1901U), Date::DAYS_PER_YEAR * 2U);
    CHECK_EQUAL(Date::GetDaysInYears(2000U, 2003U), Date::DAYS_PER_LEAP_YEAR + (Date::DAYS_PER_YEAR * 3U));
    CHECK_EQUAL(Date::GetDaysInYears(2006U, 2007U), Date::DAYS_PER_YEAR * 2U);
    CHECK_EQUAL(Date::GetDaysInYears(2008U, 2012U), (Date::DAYS_PER_LEAP_YEAR * 2U) + (Date::DAYS_PER_YEAR * 3U));
}

TEST_MEMBER_FUNCTION(Date, GetDaysInMonths, month_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, month_type, year_type");

    CHECK_EQUAL(Date::GetDaysInMonths(Date::JANUARY, Date::JANUARY, 2000U), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysInMonths(Date::JANUARY, Date::FEBRUARY, 2000U), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_LEAP_FEBRUARY);
    CHECK_EQUAL(Date::GetDaysInMonths(Date::JANUARY, Date::MARCH, 2000U), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_LEAP_FEBRUARY + Date::DAYS_IN_MARCH);
    CHECK_EQUAL(Date::GetDaysInMonths(Date::JANUARY, Date::DECEMBER, 2000U), Date::GetDaysInYear(2000U));
    CHECK_EQUAL(Date::GetDaysInMonths(Date::JANUARY, Date::FEBRUARY, 2001U), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_FEBRUARY);
    CHECK_EQUAL(Date::GetDaysInMonths(Date::JANUARY, Date::DECEMBER, 2001U), Date::GetDaysInYear(2001U));
}

TEST_MEMBER_FUNCTION(Date, GetDaysFromStartOfYear, day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type");

    // Check this works with 1900, which is not a leap year.
    Date::year_type year = 1900U;
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::JANUARY, year), 0U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(2U, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::FEBRUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::MARCH, year), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_FEBRUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), Date::DAYS_PER_YEAR - 1U);

    // Check this works with 2000, which is a leap year.
    year = 2000U;
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::JANUARY, year), 0U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(2U, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::FEBRUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::MARCH, year), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_LEAP_FEBRUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), Date::DAYS_PER_LEAP_YEAR - 1U);

    // Check this works with 2003, which is not a leap year.
    year = 2003U;
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::JANUARY, year), 0U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(2U, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::FEBRUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::MARCH, year), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_FEBRUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), Date::DAYS_PER_YEAR - 1U);

    // Check this works with 2004, which is a leap year.
    year = 2004U;
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::JANUARY, year), 0U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(2U, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::FEBRUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(1U, Date::MARCH, year), static_cast<Date::size_type>(Date::DAYS_IN_JANUARY) + Date::DAYS_IN_LEAP_FEBRUARY);
    CHECK_EQUAL(Date::GetDaysFromStartOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), Date::DAYS_PER_LEAP_YEAR - 1U);
}

TEST_MEMBER_FUNCTION(Date, GetDaysToEndOfYear, day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type");

    // Check this works with 1900, which is not a leap year.
    Date::year_type year = 1900U;
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::JANUARY, year), Date::DAYS_PER_YEAR - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(2U, Date::JANUARY, year), Date::DAYS_PER_YEAR - 2U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_PER_YEAR - Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::FEBRUARY, year), Date::DAYS_PER_YEAR - Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::MARCH, year), Date::DAYS_PER_YEAR - Date::DAYS_IN_JANUARY - Date::DAYS_IN_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 0U);

    // Check this works with 2000, which is a leap year.
    year = 2000U;
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::JANUARY, year), Date::DAYS_PER_LEAP_YEAR - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(2U, Date::JANUARY, year), Date::DAYS_PER_LEAP_YEAR - 2U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_PER_LEAP_YEAR - Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::FEBRUARY, year), Date::DAYS_PER_LEAP_YEAR - Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::MARCH, year), Date::DAYS_PER_LEAP_YEAR - Date::DAYS_IN_JANUARY - Date::DAYS_IN_LEAP_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 0U);

    // Check this works with 2003, which is not a leap year.
    year = 2003U;
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::JANUARY, year), Date::DAYS_PER_YEAR - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(2U, Date::JANUARY, year), Date::DAYS_PER_YEAR - 2U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_PER_YEAR - Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::FEBRUARY, year), Date::DAYS_PER_YEAR - Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::MARCH, year), Date::DAYS_PER_YEAR - Date::DAYS_IN_JANUARY - Date::DAYS_IN_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 0U);

    // Check this works with 2004, which is a leap year.
    year = 2004U;
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::JANUARY, year), Date::DAYS_PER_LEAP_YEAR - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(2U, Date::JANUARY, year), Date::DAYS_PER_LEAP_YEAR - 2U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_PER_LEAP_YEAR - Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::FEBRUARY, year), Date::DAYS_PER_LEAP_YEAR - Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(1U, Date::MARCH, year), Date::DAYS_PER_LEAP_YEAR - Date::DAYS_IN_JANUARY - Date::DAYS_IN_LEAP_FEBRUARY - 1U);
    CHECK_EQUAL(Date::GetDaysToEndOfYear(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 0U);
}

TEST_MEMBER_FUNCTION(Date, GetNextDay, day_type_month_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type");

    CHECK_EQUAL(Date::GetNextDay(1U, Date::JANUARY), 2U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JANUARY - 1U, Date::JANUARY), Date::DAYS_IN_JANUARY);

    // Test wrap around.
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JANUARY, Date::JANUARY), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_MARCH, Date::MARCH), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_APRIL, Date::APRIL), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_MAY, Date::MAY), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JUNE, Date::JUNE), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JULY, Date::JULY), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_AUGUST, Date::AUGUST), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_SEPTEMBER, Date::SEPTEMBER), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_OCTOBER, Date::OCTOBER), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_NOVEMBER, Date::NOVEMBER), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_DECEMBER, Date::DECEMBER), 1U);
}

TEST_MEMBER_FUNCTION(Date, GetNextDay, day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type");

    Date::year_type year = 2000U; // Is a leap year.

    CHECK_EQUAL(Date::GetNextDay(1U, Date::JANUARY, year), 2U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JANUARY - 1U, Date::JANUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY, year), Date::DAYS_IN_LEAP_FEBRUARY);

    // Test wrap around.
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JANUARY, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_LEAP_FEBRUARY, Date::FEBRUARY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_MARCH, Date::MARCH, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_APRIL, Date::APRIL, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_MAY, Date::MAY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JUNE, Date::JUNE, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JULY, Date::JULY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_AUGUST, Date::AUGUST, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_SEPTEMBER, Date::SEPTEMBER, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_OCTOBER, Date::OCTOBER, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_NOVEMBER, Date::NOVEMBER, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 1U);

    year = 2007U; // Is not a leap year.

    CHECK_EQUAL(Date::GetNextDay(1U, Date::JANUARY, year), 2U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JANUARY - 1U, Date::JANUARY, year), Date::DAYS_IN_JANUARY);

    // Test wrap around.
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JANUARY, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_MARCH, Date::MARCH, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_APRIL, Date::APRIL, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_MAY, Date::MAY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JUNE, Date::JUNE, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_JULY, Date::JULY, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_AUGUST, Date::AUGUST, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_SEPTEMBER, Date::SEPTEMBER, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_OCTOBER, Date::OCTOBER, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_NOVEMBER, Date::NOVEMBER, year), 1U);
    CHECK_EQUAL(Date::GetNextDay(Date::DAYS_IN_DECEMBER, Date::DECEMBER, year), 1U);
}

TEST_MEMBER_FUNCTION(Date, GetPreviousDay, day_type_month_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type");

    CHECK_EQUAL(Date::GetPreviousDay(Date::DAYS_IN_JANUARY, Date::JANUARY), Date::DAYS_IN_JANUARY - 1);
    CHECK_EQUAL(Date::GetPreviousDay(2U, Date::JANUARY), 1U);

    // Test wrap around.
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JANUARY), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::FEBRUARY), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::MARCH), Date::DAYS_IN_FEBRUARY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::APRIL), Date::DAYS_IN_MARCH);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::MAY), Date::DAYS_IN_APRIL);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JUNE), Date::DAYS_IN_MAY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JULY), Date::DAYS_IN_JUNE);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::AUGUST), Date::DAYS_IN_JULY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::SEPTEMBER), Date::DAYS_IN_AUGUST);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::OCTOBER), Date::DAYS_IN_SEPTEMBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::NOVEMBER), Date::DAYS_IN_OCTOBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::DECEMBER), Date::DAYS_IN_NOVEMBER);
}

TEST_MEMBER_FUNCTION(Date, AddDaysForYears, size_type_day_type_month_type_year_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type, day_type, month_type, year_type&");

    // Check that no days remaining will return 0 days for last day of year, and that
    // the year has not changed.
    Date::day_type day = Date::DAYS_IN_DECEMBER;
    Date::month_type month = Date::DECEMBER;
    Date::year_type year = 2000U;
    CHECK_EQUAL(Date::AddDaysForYears(0U, day, month, year), 0U);
    CHECK_EQUAL(day, Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(month, Date::DECEMBER);
    CHECK_EQUAL(year, 2000U);

    day = 1U;
    month = Date::JANUARY;
    year = 2000U;
    CHECK_EQUAL(Date::AddDaysForYears(366U, day, month, year), 366U);
    CHECK_EQUAL(day, 1U);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2001U);

    day = 1U;
    month = Date::JANUARY;
    year = 2001U;
    CHECK_EQUAL(Date::AddDaysForYears(365U, day, month, year), 365U);
    CHECK_EQUAL(day, 1U);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2002U);

    // Test wrap around from first day in last month to last day in last month for non-leap year into a leap year.
    for (Date::day_type curr_day = 1U; curr_day <= Date::DAYS_IN_DECEMBER; ++curr_day)
    {
        day = curr_day;
        month = Date::DECEMBER;
        year = 1999U;
        Date::size_type days_to_next_year = 1U + Date::DAYS_IN_DECEMBER - day;
        Date::size_type calculated_days_to_next_year = Date::AddDaysForYears(days_to_next_year, day, month, year);
        CHECK_EQUAL(calculated_days_to_next_year, days_to_next_year);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(month, Date::JANUARY);
        CHECK_EQUAL(year, 2000U);
    }

    // Test wrap around from first day in last month to last day in last month for leap year.
    for (Date::day_type curr_day = 1U; curr_day <= Date::DAYS_IN_DECEMBER; ++curr_day)
    {
        day = curr_day;
        month = Date::DECEMBER;
        year = 2000U;
        CHECK_EQUAL(Date::AddDaysForYears(365U, day, month, year), 1U + Date::DAYS_IN_DECEMBER - day);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(month, Date::JANUARY);
        CHECK_EQUAL(year, 2001U);
    }

    // Test wrap around from first day in last month to last day in last month for non-leap year.
    for (Date::day_type curr_day = 1U; curr_day <= Date::DAYS_IN_DECEMBER; ++curr_day)
    {
        day = curr_day;
        month = Date::DECEMBER;
        year = 2001U;
        CHECK_EQUAL(Date::AddDaysForYears(365U, day, month, year), 1U + Date::DAYS_IN_DECEMBER - day);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(month, Date::JANUARY);
        CHECK_EQUAL(year, 2002U);
    }
}

TEST_MEMBER_FUNCTION(Date, AddDaysForMonths, size_type_day_type_month_type_ref_year_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type, day_type, month_type&, year_type&");

    // Test that not enough days remaining will not wrap the count past the end of the month.
    Date::day_type day = Date::DAYS_IN_JANUARY;
    Date::month_type month = Date::JANUARY;
    Date::year_type year = 2000U;
    CHECK_EQUAL(Date::AddDaysForMonths(0U, day, month, year), 0U);
    CHECK_EQUAL(day, Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2000U);

    // Test that not enough days remaining will not wrap the count past the end of the month.
    day = Date::DAYS_IN_JANUARY - 1U;
    month = Date::JANUARY;
    year = 2000U;
    CHECK_EQUAL(Date::AddDaysForMonths(1U, day, month, year), 0U);
    CHECK_EQUAL(day, Date::DAYS_IN_JANUARY - 1U);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2000U);

    // Check that a whole year of days wraps around for a non-leap year.
    day = 1U;
    month = Date::JANUARY;
    year = 1999U;
    CHECK_EQUAL(Date::AddDaysForMonths(365U, day, month, year), 365U);
    CHECK_EQUAL(day, 1U);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2000U);

    // Check that a whole year of days wraps around for a leap year.
    day = 1U;
    month = Date::JANUARY;
    year = 2000U;
    CHECK_EQUAL(Date::AddDaysForMonths(366U, day, month, year), 366U);
    CHECK_EQUAL(day, 1U);
    CHECK_EQUAL(month, Date::JANUARY);
    CHECK_EQUAL(year, 2001U);

    // Test that with a minimum days remaining, the wrapping to the next month and
    // days to next month are correct.
    for (Date::day_type curr_day = 1U; curr_day <= Date::DAYS_IN_JANUARY; ++curr_day)
    {
        day = curr_day;
        month = Date::JANUARY;
        year = 2000U;
        Date::size_type days_to_next_month = 1U + Date::DAYS_IN_JANUARY - day;
        Date::size_type calculated_days_to_next_month = Date::AddDaysForMonths(days_to_next_month, day, month, year);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(days_to_next_month, calculated_days_to_next_month);
        CHECK_EQUAL(month, Date::FEBRUARY);
    }
}

TEST_MEMBER_FUNCTION(Date, SubtractDaysForYears, size_type_day_type_month_type_year_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type, day_type, month_type, year_type&");

    // Check that no days remaining will return 0 days for first day of year, and that
    // the year has not changed.

    Date::day_type day = 1U;
    Date::month_type month = Date::JANUARY;
    Date::year_type year = 2000U;
    CHECK_EQUAL(Date::SubtractDaysForYears(0U, day, month, year), 0U);
    CHECK_EQUAL(year, 2000U);
    CHECK_EQUAL(month, Date::JANUARY);

    day = Date::DAYS_IN_DECEMBER;
    month = Date::DECEMBER;
    year = 2000U;
    CHECK_EQUAL(Date::SubtractDaysForYears(366U, day, month, year), 366U);
    CHECK_EQUAL(year, 1999U);
    CHECK_EQUAL(month, Date::DECEMBER);

    day = Date::DAYS_IN_DECEMBER;
    month = Date::DECEMBER;
    year = 2001U;
    CHECK_EQUAL(Date::SubtractDaysForYears(365U, day, month, year), 365U);
    CHECK_EQUAL(year, 2000U);
    CHECK_EQUAL(month, Date::DECEMBER);

    // Test wrap around from first day in first month to last day in last month for non-leap year.
    for (Date::day_type curr_day = 1U; curr_day <= Date::DAYS_IN_JANUARY; ++curr_day)
    {
        day = curr_day;
        month = Date::JANUARY;
        year = 2000U;

        // With only day(s) remaining to wrap to previous year,
        // check SubtractDaysForYears calculates remaining day in current year for wrap around.
        Date::size_type calculated_days_to_prev_year = Date::SubtractDaysForYears(day, day, month, year);
        CHECK_EQUAL(calculated_days_to_prev_year, curr_day);
        CHECK_EQUAL(day, Date::DAYS_IN_DECEMBER);
        CHECK_EQUAL(month, Date::DECEMBER);
        CHECK_EQUAL(year, 1999U);
    }
}

TEST_MEMBER_FUNCTION(Date, SubtractDaysForMonths, size_type_day_type_month_type_ref_year_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type, day_type, month_type&, year_type&");

    // Test that not enough days remaining will not wrap the count past the end of the month.
    Date::day_type day = Date::DAYS_IN_JANUARY - 1U;
    Date::month_type month = Date::JANUARY;
    Date::year_type year = 2000U;
    CHECK_EQUAL(Date::SubtractDaysForMonths(1U, day, month, year), 0U);
    CHECK_EQUAL(month, Date::JANUARY);

    // Check that a whole year of days wraps around for a non-leap year.
    day = Date::DAYS_IN_DECEMBER;
    month = Date::DECEMBER;
    year = 2001U;
    CHECK_EQUAL(Date::SubtractDaysForMonths(365U, day, month, year), 365U);
    CHECK_EQUAL(month, Date::DECEMBER);
    CHECK_EQUAL(year, 2000U);

    Date::size_type days_in_year = Date::GetDaysInYear(year);
    // Check that a whole year of days wraps around for a leap year.
    day = Date::DAYS_IN_DECEMBER;
    month = Date::DECEMBER;
    year = 2000U;
    Date::size_type calculated_days_for_whole_months = Date::SubtractDaysForMonths(days_in_year, day, month, year);
    CHECK_EQUAL(calculated_days_for_whole_months, days_in_year);
    CHECK_EQUAL(month, Date::DECEMBER);
    CHECK_EQUAL(year, 1999U);

    // Test that with a minimum days remaining, the wrapping to the previous month and
    // days to previous month are correct.
    for (Date::day_type curr_day = 1U; curr_day <= Date::DAYS_IN_JANUARY; ++curr_day)
    {
        day = curr_day;
        month = Date::JANUARY;
        year = 2000U;
        Date::size_type calculated_days_to_prev_month = Date::SubtractDaysForMonths(curr_day, day, month, year);
        CHECK_EQUAL(day, Date::DAYS_IN_DECEMBER);
        CHECK_EQUAL(curr_day, calculated_days_to_prev_month);
        CHECK_EQUAL(month, Date::DECEMBER);
        CHECK_EQUAL(year, 1999U);
    }
}

TEST_MEMBER_FUNCTION(Date, GetDifferenceInDays, day_type_month_type_day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, day_type, month_type, year_type");

    // Check difference works for leap year.
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 1U, Date::JANUARY, 2000U), 0U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2U, Date::JANUARY, 2000U), 1U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U), Date::GetDaysInYear(2000U) - 1U);

    // Check difference works for non-leap year.
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 1U, Date::JANUARY, 2001U), 0U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2U, Date::JANUARY, 2001U), 1U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U), Date::GetDaysInYear(2001U) - 1U);
}

TEST_MEMBER_FUNCTION(Date, GetDifferenceInDays, day_type_month_type_year_type_day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type, day_type, month_type, year_type");

    // Check difference works for leap year for same year.
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2000U, 1U, Date::JANUARY, 2000U), 0U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2000U, 2U, Date::JANUARY, 2000U), 1U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2000U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U), Date::GetDaysInYear(2000U) - 1U);

    // Check difference works for non-leap year for same year.
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2001U, 1U, Date::JANUARY, 2001U), 0U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2001U, 2U, Date::JANUARY, 2001U), 1U);
    CHECK_EQUAL(Date::GetDifferenceInDays(1U, Date::JANUARY, 2001U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U), Date::GetDaysInYear(2001U) - 1U);

    // Check difference works over a single year boundary.
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U, 1U, Date::JANUARY, 2000U), 1U);
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U, 1U, Date::JANUARY, 2001U), 1U);
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U), Date::GetDaysInYear(2000U));
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U), Date::GetDaysInYear(2001U));
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U), Date::GetDaysInYears(2000U, 2001U));
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2002U), Date::GetDaysInYears(2001U, 2002U));
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2002U), Date::GetDaysInYears(2000U, 2002U));
    CHECK_EQUAL(Date::GetDifferenceInDays(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2003U), Date::GetDaysInYears(2001U, 2003U));
}

TEST_MEMBER_FUNCTION(Date, GetDifference, day_type_month_type_year_type_day_type_month_type_year_type_day_type_ref_month_type_ref_year_type_ref)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type, day_type, month_type, year_type, day_type&, month_type&, year_type&");

    Date::day_type diff_days = 99;
    Date::month_type diff_months = 99;
    Date::year_type diff_years = 10000;

    // Check minimum difference of 1 days over a year boundary.
    Date::GetDifference(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U, 1U, Date::JANUARY, 2000U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 0);
    CHECK_EQUAL(diff_years, 0);

    // Check minimum difference of 1 days over a month boundary.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(Date::DAYS_IN_MARCH, Date::MARCH, 1999U, 1U, Date::APRIL, 1999U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 0);
    CHECK_EQUAL(diff_years, 0);

    // Check minimum difference of 1 days over a non-leap month boundary.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY, 1999U, 1U, Date::MARCH, 1999U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 0);
    CHECK_EQUAL(diff_years, 0);

    // Check minimum difference of 1 days over a non-leap month boundary.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY, 2020U, 1U, Date::MARCH, 2020U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 2);
    CHECK_EQUAL(diff_months, 0);
    CHECK_EQUAL(diff_years, 0);

    // Check first and last day in the same year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2020U, Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2020U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, Date::DAYS_IN_DECEMBER - 1);
    CHECK_EQUAL(diff_months, 11);
    CHECK_EQUAL(diff_years, 0);

    // Check first and last day in the every month, including non-leap year and leap year.
    for (Date::year_type y = 2019U; y <= 2020U; ++y)
        for (Date::month_type m = Date::JANUARY; m <= Date::DECEMBER; ++m)
        {
            diff_days = 99;
            diff_months = 99;
            diff_years = 10000;
            Date::month_type days_in_month = Date::GetDaysInMonth(m, y);
            Date::GetDifference(1U, m, y, days_in_month, m, y, diff_days, diff_months, diff_years);
            CHECK_EQUAL(diff_days, days_in_month - 1);
            CHECK_EQUAL(diff_months, 0);
            CHECK_EQUAL(diff_years, 0);
        }

    // Check 1 day over a year difference for non-leap year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2019U, 2U, Date::JANUARY, 2020U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 0);
    CHECK_EQUAL(diff_years, 1);

    // Check 1 day over a year difference for leap year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2020U, 2U, Date::JANUARY, 2021U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 0);
    CHECK_EQUAL(diff_years, 1);

    // Check 1 day and 1 month over a year difference for non-leap year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2019U, 2U, Date::FEBRUARY, 2020U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 1);
    CHECK_EQUAL(diff_years, 1);

    // Check 1 day and 1 month over a year difference for leap year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2020U, 2U, Date::FEBRUARY, 2021U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 1);
    CHECK_EQUAL(diff_years, 1);

    // Check 1 day and 2 month over 3 years difference for non-leap year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2019U, 2U, Date::MARCH, 2022U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 2);
    CHECK_EQUAL(diff_years, 3);

    // Check 1 day and 2 month over 3 years difference for leap year.
    diff_days = 99;
    diff_months = 99;
    diff_years = 10000;
    Date::GetDifference(1U, Date::JANUARY, 2020U, 2U, Date::MARCH, 2023U, diff_days, diff_months, diff_years);
    CHECK_EQUAL(diff_days, 1);
    CHECK_EQUAL(diff_months, 2);
    CHECK_EQUAL(diff_years, 3);
}

TEST_MEMBER_FUNCTION(Date, GetPreviousDay, day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type");

    Date::year_type year = 2000U; // Is a leap year.

    CHECK_EQUAL(Date::GetPreviousDay(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1);
    CHECK_EQUAL(Date::GetPreviousDay(2U, Date::JANUARY, year), 1U);
    CHECK_EQUAL(Date::GetPreviousDay(Date::DAYS_IN_LEAP_FEBRUARY, Date::FEBRUARY, year), Date::DAYS_IN_FEBRUARY);

    // Test wrap around.
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JANUARY, year), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::FEBRUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::MARCH, year), Date::DAYS_IN_LEAP_FEBRUARY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::APRIL, year), Date::DAYS_IN_MARCH);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::MAY, year), Date::DAYS_IN_APRIL);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JUNE, year), Date::DAYS_IN_MAY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JULY, year), Date::DAYS_IN_JUNE);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::AUGUST, year), Date::DAYS_IN_JULY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::SEPTEMBER, year), Date::DAYS_IN_AUGUST);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::OCTOBER, year), Date::DAYS_IN_SEPTEMBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::NOVEMBER, year), Date::DAYS_IN_OCTOBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::DECEMBER, year), Date::DAYS_IN_NOVEMBER);

    year = 2007U; // Is not a leap year.

    CHECK_EQUAL(Date::GetPreviousDay(Date::DAYS_IN_JANUARY, Date::JANUARY, year), Date::DAYS_IN_JANUARY - 1);
    CHECK_EQUAL(Date::GetPreviousDay(2U, Date::JANUARY, year), 1U);

    // Test wrap around.
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JANUARY, year), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::FEBRUARY, year), Date::DAYS_IN_JANUARY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::MARCH, year), Date::DAYS_IN_FEBRUARY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::APRIL, year), Date::DAYS_IN_MARCH);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::MAY, year), Date::DAYS_IN_APRIL);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JUNE, year), Date::DAYS_IN_MAY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::JULY, year), Date::DAYS_IN_JUNE);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::AUGUST, year), Date::DAYS_IN_JULY);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::SEPTEMBER, year), Date::DAYS_IN_AUGUST);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::OCTOBER, year), Date::DAYS_IN_SEPTEMBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::NOVEMBER, year), Date::DAYS_IN_OCTOBER);
    CHECK_EQUAL(Date::GetPreviousDay(1U, Date::DECEMBER, year), Date::DAYS_IN_NOVEMBER);
}

TEST_MEMBER_FUNCTION(Date, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("Date");

    Date date;

    CHECK_EQUAL(date.GetDay(), Date::MIN_DAY);
    CHECK_EQUAL(date.GetMonth(), Date::MIN_MONTH);
    CHECK_EQUAL(date.GetYear(), Date::DEFAULT_YEAR);
}

TEST_MEMBER_FUNCTION(Date, constructor, day_type_month_type_year_type)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("Date", "day_type, month_type, year_type");

    Date date(2, Date::FEBRUARY, 1980);

    CHECK_EQUAL(date.GetDay(), 2U);
    CHECK_EQUAL(date.GetMonth(), Date::FEBRUARY);
    CHECK_EQUAL(date.GetYear(), 1980U);
}

TEST_MEMBER_FUNCTION(Date, copy_constructor, Date_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("Date", "Date const&");

    Date date1(2, Date::FEBRUARY, 1980);
    Date date2(date1);

    CHECK_EQUAL(date2.GetDay(), 2U);
    CHECK_EQUAL(date2.GetMonth(), Date::FEBRUARY);
    CHECK_EQUAL(date2.GetYear(), 1980U);
}

TEST_MEMBER_FUNCTION(Date, assignment_operator, Date_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "Date const&");

    Date date1(2, Date::FEBRUARY, 1980);
    Date date2;
    date2 = date1;

    CHECK_EQUAL(date2.GetDay(), 2U);
    CHECK_EQUAL(date2.GetMonth(), Date::FEBRUARY);
    CHECK_EQUAL(date2.GetYear(), 1980U);
}

TEST_CONST_MEMBER_FUNCTION(Date, GetDay, NA)
{
    Date date1(1U, 2U, 1980U);
    CHECK_EQUAL(date1.GetDay(), 1U);

    Date date2(31U, 1U, 1980U);
    CHECK_EQUAL(date2.GetDay(), 31U);
}

TEST_MEMBER_FUNCTION(Date, SetDay, day_type)
{
    Date date;
    date.SetDay(2U);
    CHECK_EQUAL(date.GetDay(), 2U);

    date.SetDay(31U);
    CHECK_EQUAL(date.GetDay(), 31U);
}

TEST_CONST_MEMBER_FUNCTION(Date, GetMonth, NA)
{
    Date date1(2U, 1U, 1980U);
    CHECK_EQUAL(date1.GetMonth(), 1U);

    Date date2(2U, 12U, 1980U);
    CHECK_EQUAL(date2.GetMonth(), 12U);
}

TEST_MEMBER_FUNCTION(Date, SetMonth, month_type)
{
    Date date;

    date.SetMonth(1U);
    CHECK_EQUAL(date.GetMonth(), 1U);

    date.SetMonth(12U);
    CHECK_EQUAL(date.GetMonth(), 12U);
}

TEST_CONST_MEMBER_FUNCTION(Date, GetYear, NA)
{
    Date date1(2U, 1U, 1980U);
    CHECK_EQUAL(date1.GetYear(), 1980U);

    Date date2(2U, 12U, 2000U);
    CHECK_EQUAL(date2.GetYear(), 2000U);
}

TEST_MEMBER_FUNCTION(Date, SetYear, year_type)
{
    Date date;

    date.SetYear(1980U);
    CHECK_EQUAL(date.GetYear(), 1980U);

    date.SetYear(2000U);
    CHECK_EQUAL(date.GetYear(), 2000U);
}

TEST_CONST_MEMBER_FUNCTION(Date, IsLeapYear, NA)
{
    Date date;

    date.SetYear(1800U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(1900U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(2000U);
    CHECK_TRUE(date.IsLeapYear());

    date.SetYear(2003U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(2004U);
    CHECK_TRUE(date.IsLeapYear());

    date.SetYear(2005U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(2006U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(2007U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(2008U);
    CHECK_TRUE(date.IsLeapYear());

    date.SetYear(2100U);
    CHECK_FALSE(date.IsLeapYear());

    date.SetYear(2200U);
    CHECK_FALSE(date.IsLeapYear());
}

TEST_MEMBER_FUNCTION(Date, GetDifferenceInDays, Date_const_ref)
{
    TEST_OVERRIDE_ARGS("date const&");

    // Check difference works for leap year for same year.
    Date date(1U, Date::JANUARY, 2000U);
    CHECK_EQUAL(date.GetDifferenceInDays(Date(1U, Date::JANUARY, 2000U)), 0U);
    CHECK_EQUAL(date.GetDifferenceInDays(Date(2U, Date::JANUARY, 2000U)), 1U);
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U)), Date::GetDaysInYear(2000U) - 1U);

    // Check difference works for non-leap year for same year.
    date.Copy(Date(1U, Date::JANUARY, 2001U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(1U, Date::JANUARY, 2001U)), 0U);
    CHECK_EQUAL(date.GetDifferenceInDays(Date(2U, Date::JANUARY, 2001U)), 1U);
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U)), Date::GetDaysInYear(2001U) - 1U);

    // Check difference works over a single year boundary.
    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(1U, Date::JANUARY, 2000U)), 1U);

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(1U, Date::JANUARY, 2001U)), 1U);

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U)), Date::GetDaysInYear(2000U));

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U)), Date::GetDaysInYear(2001U));

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2001U)), Date::GetDaysInYears(2000U, 2001U));

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2002U)), Date::GetDaysInYears(2001U, 2002U));

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1999U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2002U)), Date::GetDaysInYears(2000U, 2002U));

    date.Copy(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U));
    CHECK_EQUAL(date.GetDifferenceInDays(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2003U)), Date::GetDaysInYears(2001U, 2003U));
}

TEST_CONST_MEMBER_FUNCTION(Date, Serialize, NA)
{
    CHECK_EQUAL(Date().Serialize(), 0x07b20101U);
    CHECK_EQUAL(Date(1U, 2U, 2000U).Serialize(), 0x07d00201U);
}

TEST_MEMBER_FUNCTION(Date, Deserialize, uint32_t)
{
    Date date;

    date.Deserialize(0x07b20101U);
    CHECK_EQUAL(date.Serialize(), 0x07b20101U);
    CHECK_EQUAL(date.GetDay(), 1U);
    CHECK_EQUAL(date.GetMonth(), 1U);
    CHECK_EQUAL(date.GetYear(), 1970U);

    date.Deserialize(0x07d00201U);
    CHECK_EQUAL(date.Serialize(), 0x07d00201U);
    CHECK_EQUAL(date.GetDay(), 1U);
    CHECK_EQUAL(date.GetMonth(), 2U);
    CHECK_EQUAL(date.GetYear(), 2000U);
}

TEST_MEMBER_FUNCTION(Date, Copy, Date_const_ref)
{
    TEST_OVERRIDE_ARGS("Date const&");

    Date date;

    date.Copy(Date(1U, Date::JANUARY, 1970U));
    CHECK_EQUAL(date, Date(1U, Date::JANUARY, 1970U));
}

TEST_MEMBER_FUNCTION(Date, SetDate, day_type_month_type_year_type)
{
    TEST_OVERRIDE_ARGS("day_type, month_type, year_type");

    Date date;

    date.SetDate(1U, Date::JANUARY, 1970U);
    CHECK_EQUAL(date, Date(1U, Date::JANUARY, 1970U));
}

TEST_MEMBER_FUNCTION(Date, IncrementDay, NA)
{
    Date date(1U, Date::JANUARY, 2000U);

    date.IncrementDay();
    CHECK_EQUAL(date.GetDay(), 2U);

    date.SetDay(Date::DAYS_IN_JANUARY - 1);
    date.IncrementDay();
    CHECK_EQUAL(date.GetDay(), Date::DAYS_IN_JANUARY);

    date.IncrementDay();
    CHECK_EQUAL(date.GetDay(), 1U);
    CHECK_EQUAL(date.GetMonth(), Date::FEBRUARY);

    date.SetDay(Date::DAYS_IN_FEBRUARY);
    date.IncrementDay();
    CHECK_EQUAL(date.GetDay(), Date::DAYS_IN_LEAP_FEBRUARY);
    CHECK_EQUAL(date.GetMonth(), Date::FEBRUARY);

    date.IncrementDay();
    CHECK_EQUAL(date.GetDay(), 1U);
    CHECK_EQUAL(date.GetMonth(), Date::MARCH);

    date.SetDate(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U);
    date.IncrementDay();
    CHECK_EQUAL(date, Date(1U, Date::JANUARY, 2001U));

    date.SetDay(Date::DAYS_IN_FEBRUARY - 1U);
    date.SetMonth(Date::FEBRUARY);
    date.IncrementDay();
    CHECK_EQUAL(date, Date(Date::DAYS_IN_FEBRUARY, Date::FEBRUARY, 2001U));

    date.IncrementDay();
    CHECK_EQUAL(date, Date(1U, Date::MARCH, 2001U));
}

TEST_MEMBER_FUNCTION(Date, DecrementDay, NA)
{
    Date date(2U, Date::MARCH, 2000U);

    date.DecrementDay();
    CHECK_EQUAL(date.GetDay(), 1U);

    date.DecrementDay();
    CHECK_EQUAL(date.GetDay(), Date::DAYS_IN_LEAP_FEBRUARY);
    CHECK_EQUAL(date.GetMonth(), Date::FEBRUARY);

    date.DecrementDay();
    CHECK_EQUAL(date.GetDay(), Date::DAYS_IN_FEBRUARY);

    date.SetDate(1U, Date::JANUARY, 2001U);
    date.DecrementDay();
    CHECK_EQUAL(date, Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 2000U));

    date.SetDate(1U, Date::MARCH, 2001U);
    date.DecrementDay();
    CHECK_EQUAL(date, Date(Date::DAYS_IN_LEAP_FEBRUARY, Date::FEBRUARY, 2001U));
}

TEST_MEMBER_FUNCTION(Date, IncrementMonth, NA)
{
    Date date;

    // Test leap year and non-leap year max days per month.
    for (Date::year_type year = 2000U; year <= 2001; ++year)
    {
        for (Date::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            Date::day_type max_day = Date::GetDaysInMonth(month, year);
            Date::day_type max_next_day = Date::GetDaysInMonth(Date::GetNextMonth(month), year);

            date.SetDate(max_day, month, year);
            date.IncrementMonth();

            Date::day_type expected_day = max_next_day < max_day ? max_next_day : max_day;
            CHECK_EQUAL(date.GetDay(), expected_day);
        }
    }
}

TEST_MEMBER_FUNCTION(Date, DecrementMonth, NA)
{
    Date date;

    // Test leap year and non-leap year max days per month.
    for (Date::year_type year = 2000U; year <= 2001; ++year)
    {
        for (Date::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            Date::day_type max_day = Date::GetDaysInMonth(month, year);
            Date::day_type max_next_day = Date::GetDaysInMonth(Date::GetPreviousMonth(month), year);

            date.SetDate(max_day, month, year);
            date.DecrementMonth();

            Date::day_type expected_day = max_next_day < max_day ? max_next_day : max_day;
            CHECK_EQUAL(date.GetDay(), expected_day);
        }
    }
}

TEST_MEMBER_FUNCTION(Date, AddDays, size_type)
{
    Date date;

    Date::size_type days_in_leap_year = Date::GetDaysInYear(2000U);
    Date::size_type days_in_year = Date::GetDaysInYear(2001U);

    for (Date::year_type year = 2000U; year <= 2001U; ++year)
    {
        for (Date::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            Date::day_type days_in_month = Date::GetDaysInMonth(month, year);

            // Test adding 0 days to every day in the month has no effect.
            for (Date::day_type day = 1U; day < days_in_month; ++day)
            {
                date.SetDate(day, month, year);
                date.AddDays(0U);
                CHECK_EQUAL(date.GetDay(), day);
                CHECK_EQUAL(date.GetMonth(), month);
                CHECK_EQUAL(date.GetYear(), year);
            }

            // Test offsetting days for a complete year wraps correctly to next day, month and year.
            for (Date::day_type day = 1U; day < days_in_month; ++day)
            {
                date.SetDate(day, month, year);
                bool need_leap_days = (year == 2000U) && (month <= Date::FEBRUARY);
                Date::size_type days_to_next_year = need_leap_days ? days_in_leap_year : days_in_year;
                date.AddDays(days_to_next_year);
                CHECK_EQUAL(date, Date(day, month, year + 1U));
            }

            // Test adding a single day to every day except last day
            // sets correct day and doesn't wrap month.
            for (Date::day_type day = 1U; day < days_in_month; ++day)
            {
                date.SetDate(day, month, year);
                date.AddDays(1U);
                CHECK_EQUAL(date.GetDay(), day + 1U);
                CHECK_EQUAL(date.GetMonth(), month);
                CHECK_EQUAL(date.GetYear(), year);
            }

            // Test adding number of days to reach last day doesn't overflow the month,
            // and sets the day to the last day of the month.
            for (Date::day_type day = 1U; day < days_in_month; ++day)
            {
                date.SetDay(day);
                date.AddDays(days_in_month - day);
                CHECK_EQUAL(date.GetDay(), days_in_month);
                CHECK_EQUAL(date.GetMonth(), month);
                CHECK_EQUAL(date.GetYear(), year);
            }

            // Test adding days in the month wraps to the start of the following month.
            date.SetDate(1U, month, year);
            date.AddDays(days_in_month);
            CHECK_EQUAL(date.GetDay(), 1U);
            Date::month_type next_month = Date::GetNextMonth(month);
            CHECK_EQUAL(date.GetMonth(), next_month);
            Date::year_type expected_year = month < Date::DECEMBER ? year : year + 1U;
            CHECK_EQUAL(date.GetYear(), expected_year);
        }
    }
}

TEST_MEMBER_FUNCTION(Date, SubtractDays, size_type)
{
    Date date;

    Date::size_type days_in_leap_year = Date::GetDaysInYear(2000U);
    Date::size_type days_in_year = Date::GetDaysInYear(2001U);

    for (Date::year_type year = 2000U; year <= 2001U; ++year)
    {
        for (Date::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            // Test offsetting days for a complete year wraps correctly to previous day, month and year.
            Date::day_type days_in_month = Date::GetDaysInMonth(month, year);
            for (Date::day_type day = 1U; day < days_in_month; ++day)
            {
                date.SetDate(day, month, year);

                // Between March 2000 and February 2001 the subtraction
                // needs to be days in a leap year (366 days).
                bool need_leap_days = (year == 2000U && month > Date::FEBRUARY) ||
                                      (year == 2001U && month <= Date::FEBRUARY);

                Date::size_type days_to_prev_year = need_leap_days ? days_in_leap_year : days_in_year;
                date.SubtractDays(days_to_prev_year);
                Date cmp(day, month, year - 1U);
                CHECK_EQUAL(date, cmp);
            }

            // Test subtracting a single day to every day except first day
            // sets correct day and doesn't wrap month.
            for (Date::day_type day = 2U; day <= days_in_month; ++day)
            {
                date.SetDate(day, month, year);
                date.SubtractDays(1U);
                CHECK_EQUAL(date.GetDay(), day - 1U);
                CHECK_EQUAL(date.GetMonth(), month);
                CHECK_EQUAL(date.GetYear(), year);
            }

            // Test subtracting number of days to reach first day doesn't wrap the month,
            // and sets the day to the first day of the month.
            for (Date::day_type day = 1U; day < days_in_month; ++day)
            {
                date.SetDay(day);
                date.SubtractDays(day - 1U);
                CHECK_EQUAL(date.GetDay(), 1U);
                CHECK_EQUAL(date.GetMonth(), month);
                CHECK_EQUAL(date.GetYear(), year);
            }

            // Test subtracting days in the month wraps to the end of the previous month.
            date.SetDate(days_in_month, month, year);
            date.SubtractDays(days_in_month);
            Date::month_type prev_month = Date::GetPreviousMonth(month);
            Date::year_type expected_year = prev_month < Date::DECEMBER ? year : year - 1U;
            CHECK_EQUAL(date.GetDay(), Date::GetDaysInMonth(prev_month, expected_year));
            CHECK_EQUAL(date.GetMonth(), prev_month);
            CHECK_EQUAL(date.GetYear(), expected_year);
        }
    }
}

TEST_CONST_MEMBER_FUNCTION(Date, Swap, Date_ref)
{
    TEST_OVERRIDE_ARGS("Date&");

    Date date1(1U, Date::JANUARY, 1980U);
    Date date2(3U, Date::JULY, 2000U);
    date1.Swap(date2);
    CHECK_EQUAL(date1, Date(3U, Date::JULY, 2000U));
    CHECK_EQUAL(date2, Date(1U, Date::JANUARY, 1980U));
}

TEST_CONST_MEMBER_FUNCTION(Date, Compare, Date_const_ref)
{
    TEST_OVERRIDE_ARGS("Date const&");

    CHECK_EQUAL(Date().Compare(Date()), 0);
    CHECK_EQUAL(Date(1U, 2U, 1980U).Compare(Date(1U, 2U, 1980U)), 0);
    CHECK_EQUAL(Date(1U, 2U, 1980U).Compare(Date(2U, 2U, 1980U)), -1);
    CHECK_EQUAL(Date(2U, 1U, 1980U).Compare(Date(1U, 2U, 1980U)), -1);
    CHECK_EQUAL(Date(3U, 2U, 1979U).Compare(Date(1U, 2U, 1980U)), -1);
    CHECK_EQUAL(Date(2U, 2U, 1980U).Compare(Date(1U, 2U, 1980U)), 1);
    CHECK_EQUAL(Date(1U, 3U, 1980U).Compare(Date(1U, 2U, 1980U)), 1);
    CHECK_EQUAL(Date(1U, 2U, 1981U).Compare(Date(1U, 2U, 1980U)), 1);
}
