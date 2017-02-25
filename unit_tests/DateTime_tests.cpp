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
#include "../DateTime.hpp"

using ocl::Date;
using ocl::Time;
using ocl::DateTime;

TEST_MEMBER_FUNCTION(DateTime, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("DateTime");

    DateTime dt;

    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);
    CHECK_EQUAL(dt.GetYear(), DateTime::DEFAULT_YEAR);
    CHECK_EQUAL(dt.GetMonth(), DateTime::MIN_MONTH);
    CHECK_EQUAL(dt.GetDay(), DateTime::MIN_DAY);
}

TEST_MEMBER_FUNCTION(DateTime, constructor, Date_const_ref_Time_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTime", "Date const&, Time const&");

    {
        Date date;
        Time time;
        DateTime dt(date, time);

        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 0U);
        CHECK_EQUAL(dt.GetMinutes(), 0U);
        CHECK_EQUAL(dt.GetHours(), 0U);
        CHECK_EQUAL(dt.GetYear(), DateTime::DEFAULT_YEAR);
        CHECK_EQUAL(dt.GetMonth(), DateTime::MIN_MONTH);
        CHECK_EQUAL(dt.GetDay(), DateTime::MIN_DAY);
    }

    {
        DateTime dt(Date(1U, 2U, 2000U), Time(1U, 2U, 3U, 4U));

        CHECK_EQUAL(dt.GetMilliseconds(), 4U);
        CHECK_EQUAL(dt.GetSeconds(), 3U);
        CHECK_EQUAL(dt.GetMinutes(), 2U);
        CHECK_EQUAL(dt.GetHours(), 1U);
        CHECK_EQUAL(dt.GetYear(), 2000U);
        CHECK_EQUAL(dt.GetMonth(), 2U);
        CHECK_EQUAL(dt.GetDay(), 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTime, constructor, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTime", "DateTime const&");

    {
        DateTime dt_src;
        DateTime dt(dt_src);

        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 0U);
        CHECK_EQUAL(dt.GetMinutes(), 0U);
        CHECK_EQUAL(dt.GetHours(), 0U);
        CHECK_EQUAL(dt.GetYear(), DateTime::DEFAULT_YEAR);
        CHECK_EQUAL(dt.GetMonth(), DateTime::MIN_MONTH);
        CHECK_EQUAL(dt.GetDay(), DateTime::MIN_DAY);
    }

    {
        DateTime dt_src(Date(1U, 2U, 2000U), Time(1U, 2U, 3U, 4U));
        DateTime dt(dt_src);

        CHECK_EQUAL(dt.GetMilliseconds(), 4U);
        CHECK_EQUAL(dt.GetSeconds(), 3U);
        CHECK_EQUAL(dt.GetMinutes(), 2U);
        CHECK_EQUAL(dt.GetHours(), 1U);
        CHECK_EQUAL(dt.GetYear(), 2000U);
        CHECK_EQUAL(dt.GetMonth(), 2U);
        CHECK_EQUAL(dt.GetDay(), 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTime, assignment_operator, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "DateTime const&");

    DateTime dt1;
    DateTime dt2(Date(1U, 2U, 2000U), Time(1U, 2U, 3U, 4U));
    DateTime dt;

    dt = dt1;
    CHECK_TRUE(dt == dt1);

    dt = dt2;
    CHECK_TRUE(dt == dt2);
}

TEST_MEMBER_FUNCTION(DateTime, operator_less, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <", "DateTime const&");

    DateTime dt(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt < DateTime(Date(3U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt < DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 6U)));
    CHECK_TRUE(dt < DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 5U, 5U)));
    CHECK_TRUE(dt < DateTime(Date(2U, 3U, 2000U), Time(2U, 4U, 4U, 5U)));
    CHECK_TRUE(dt < DateTime(Date(2U, 3U, 2000U), Time(3U, 3U, 4U, 5U)));

    CHECK_FALSE(dt < DateTime(Date(1U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt < DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 4U)));
    CHECK_FALSE(dt < DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt < DateTime(Date(2U, 3U, 2000U), Time(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt < DateTime(Date(2U, 3U, 2000U), Time(1U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTime, operator_less_eq, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <=", "DateTime const&");

    DateTime dt(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt <= DateTime(Date(3U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 6U)));
    CHECK_TRUE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 5U, 5U)));
    CHECK_TRUE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 4U, 4U, 5U)));
    CHECK_TRUE(dt <= DateTime(Date(2U, 3U, 2000U), Time(3U, 3U, 4U, 5U)));
    CHECK_TRUE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt <= DateTime(Date(1U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 4U)));
    CHECK_FALSE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt <= DateTime(Date(2U, 3U, 2000U), Time(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt <= DateTime(Date(2U, 3U, 2000U), Time(1U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTime, operator_greater, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >", "DateTime const&");

    DateTime dt(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt > DateTime(Date(1U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt > DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 4U)));
    CHECK_TRUE(dt > DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt > DateTime(Date(2U, 3U, 2000U), Time(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt > DateTime(Date(2U, 3U, 2000U), Time(1U, 3U, 4U, 5U)));

    CHECK_FALSE(dt > DateTime(Date(3U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt > DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 6U)));
    CHECK_FALSE(dt > DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 5U, 5U)));
    CHECK_FALSE(dt > DateTime(Date(2U, 3U, 2000U), Time(2U, 4U, 4U, 5U)));
    CHECK_FALSE(dt > DateTime(Date(2U, 3U, 2000U), Time(3U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTime, operator_greater_eq, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >=", "DateTime const&");

    DateTime dt(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt >= DateTime(Date(1U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 4U)));
    CHECK_TRUE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt >= DateTime(Date(2U, 3U, 2000U), Time(1U, 3U, 4U, 5U)));
    CHECK_TRUE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt >= DateTime(Date(3U, 3U, 2000U), Time(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 6U)));
    CHECK_FALSE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 5U, 5U)));
    CHECK_FALSE(dt >= DateTime(Date(2U, 3U, 2000U), Time(2U, 4U, 4U, 5U)));
    CHECK_FALSE(dt >= DateTime(Date(2U, 3U, 2000U), Time(3U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTime, operator_eq, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator ==", "DateTime const&");

    DateTime dt(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt == DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt == DateTime(Date(1U, 3U, 2000U), Time(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTime(Date(2U, 2U, 2000U), Time(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTime(Date(2U, 3U, 2001U), Time(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTime(Date(2U, 3U, 2000U), Time(1U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTime(Date(2U, 3U, 2000U), Time(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt == DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt == DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 4U)));
}

TEST_MEMBER_FUNCTION(DateTime, operator_not_eq, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator !=", "DateTime const&");

    DateTime dt(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt != DateTime(Date(1U, 3U, 2000U), Time(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTime(Date(2U, 2U, 2000U), Time(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTime(Date(2U, 3U, 2001U), Time(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTime(Date(2U, 3U, 2000U), Time(1U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTime(Date(2U, 3U, 2000U), Time(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt != DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt != DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 4U)));

    CHECK_FALSE(dt != DateTime(Date(2U, 3U, 2000U), Time(2U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTime, GetDaysInMonth, month_type)
{
    Date::day_type days_in_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    for (DateTime::month_type month = DateTime::JANUARY; month <= DateTime::DECEMBER; ++month)
        CHECK_EQUAL(days_in_month[month - Date::JANUARY], DateTime::GetDaysInMonth(month));
}

TEST_MEMBER_FUNCTION(DateTime, IsLeapYear, year_type)
{
    CHECK_FALSE(DateTime::IsLeapYear(1800U));
    CHECK_FALSE(DateTime::IsLeapYear(1900U));
    CHECK_TRUE(DateTime::IsLeapYear(2000U));
    CHECK_FALSE(DateTime::IsLeapYear(2003U));
    CHECK_TRUE(DateTime::IsLeapYear(2004U));
    CHECK_FALSE(DateTime::IsLeapYear(2005U));
    CHECK_FALSE(DateTime::IsLeapYear(2006U));
    CHECK_FALSE(DateTime::IsLeapYear(2007U));
    CHECK_TRUE(DateTime::IsLeapYear(2008U));
    CHECK_FALSE(DateTime::IsLeapYear(2100U));
    CHECK_FALSE(DateTime::IsLeapYear(2200U));
}

TEST_MEMBER_FUNCTION(DateTime, IsLeapMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 1800U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 1900U));
    CHECK_TRUE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2000U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2003U));
    CHECK_TRUE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2004U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2005U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2006U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2007U));
    CHECK_TRUE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2008U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2100U));
    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::FEBRUARY, 2200U));

    CHECK_FALSE(DateTime::IsLeapMonth(DateTime::JANUARY, 1800U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 1900U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2000U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2003U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2004U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2005U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2006U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2007U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2008U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2100U));
    CHECK_FALSE(Date::IsLeapMonth(DateTime::JANUARY, 2200U));
}

TEST_MEMBER_FUNCTION(DateTime, GetDifference, DateTime_const_ref_DateTime_const_ref_size_type_ref_size_type_ref)
{
    TEST_OVERRIDE_ARGS("DateTime const&, DateTime const&, size_type&, size_type&");

    DateTime::size_type day;
    DateTime::size_type milliseconds;

    {
        day = milliseconds = 1U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 0U);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        day = milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 0U);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        day = milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(2U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        day = milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(2U, 1U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        day = milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(1U, 2U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, Date::DAYS_IN_JANUARY);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        day = milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime date_time2(Date(1U, 2U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, Date::DAYS_IN_JANUARY - 1U);
        CHECK_EQUAL(milliseconds, Time::MILLISECONDS_PER_DAY - 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTime, GetDifference, DateTime_const_ref_DateTime_const_ref_size_type_ref)
{
    TEST_OVERRIDE_ARGS("DateTime const&, DateTime const&, size_type&");

    DateTime::size_type milliseconds;

    {
        milliseconds = 1U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(2U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, Time::MILLISECONDS_PER_DAY);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(2U, 1U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, Time::MILLISECONDS_PER_DAY + 1U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime date_time2(Date(1U, 2U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, (Time::MILLISECONDS_PER_DAY * Date::DAYS_IN_JANUARY) + 1U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTime date_time1(Date(1U, 1U, 1980U), Time(0U, 0U, 0U, 1U));
        DateTime date_time2(Date(1U, 2U, 1980U), Time(0U, 0U, 0U, 0U));
        DateTime::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, (Time::MILLISECONDS_PER_DAY * Date::DAYS_IN_JANUARY) - 1U);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTime, GetDay, NA)
{
    DateTime dt1(Date(1U, 2U, 1980U), Time());
    CHECK_EQUAL(dt1.GetDay(), 1U);

    DateTime dt2(Date(31U, 1U, 1980U), Time());
    CHECK_EQUAL(dt2.GetDay(), 31U);
}

TEST_MEMBER_FUNCTION(DateTime, SetDay, day_type)
{
    DateTime dt;
    dt.SetDay(2U);
    CHECK_EQUAL(dt.GetDay(), 2U);

    dt.SetDay(31U);
    CHECK_EQUAL(dt.GetDay(), 31U);
}

TEST_CONST_MEMBER_FUNCTION(DateTime, GetMonth, NA)
{
    DateTime dt1(Date(2U, 1U, 1980U), Time());
    CHECK_EQUAL(dt1.GetMonth(), 1U);

    DateTime dt2(Date(2U, 12U, 1980U), Time());
    CHECK_EQUAL(dt2.GetMonth(), 12U);
}

TEST_MEMBER_FUNCTION(DateTime, SetMonth, month_type)
{
    DateTime dt;

    dt.SetMonth(1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);

    dt.SetMonth(12U);
    CHECK_EQUAL(dt.GetMonth(), 12U);
}

TEST_CONST_MEMBER_FUNCTION(DateTime, GetYear, NA)
{
    DateTime dt1(Date(2U, 1U, 1980U), Time());
    CHECK_EQUAL(dt1.GetYear(), 1980U);

    DateTime dt2(Date(2U, 12U, 2000U), Time());
    CHECK_EQUAL(dt2.GetYear(), 2000U);
}

TEST_MEMBER_FUNCTION(DateTime, SetYear, year_type)
{
    DateTime dt;

    dt.SetYear(1980U);
    CHECK_EQUAL(dt.GetYear(), 1980U);

    dt.SetYear(2000U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
}

TEST_CONST_MEMBER_FUNCTION(DateTime, IsLeapYear, NA)
{
    DateTime dt;

    dt.SetYear(1800U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(1900U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2000U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2003U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2004U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2005U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2006U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2007U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2008U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2100U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2200U);
    CHECK_FALSE(dt.IsLeapYear());
}

TEST_MEMBER_FUNCTION(DateTime, GetMilliseconds, NA)
{
    for (DateTime::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        DateTime dt(Date(), Time(0U, 1U, 2U, ms));
        CHECK_EQUAL(dt.GetMilliseconds(), ms);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTime, SetMilliseconds, millisecond_type)
{
    DateTime dt;
    for (DateTime::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        dt.SetMilliseconds(ms);
        CHECK_EQUAL(dt.GetMilliseconds(), ms);
    }
}

TEST_MEMBER_FUNCTION(DateTime, GetSeconds, NA)
{
    for (DateTime::second_type s = 0; s <= 59U; ++s)
    {
        DateTime dt(Date(), Time(0U, 1U, s, 3U));
        CHECK_EQUAL(dt.GetSeconds(), s);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTime, SetSeconds, second_type)
{
    DateTime dt;
    for (DateTime::second_type s = 0; s <= 59U; ++s)
    {
        dt.SetSeconds(s);
        CHECK_EQUAL(dt.GetSeconds(), s);
    }
}

TEST_MEMBER_FUNCTION(DateTime, GetMinutes, NA)
{
    for (DateTime::minute_type m = 0; m <= 59U; ++m)
    {
        DateTime dt(Date(), Time(0U, m, 2U, 3U));
        CHECK_EQUAL(dt.GetMinutes(), m);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTime, SetMinutes, minute_type)
{
    DateTime dt;
    for (DateTime::minute_type m = 0; m <= 59U; ++m)
    {
        dt.SetMinutes(m);
        CHECK_EQUAL(dt.GetMinutes(), m);
    }
}

TEST_MEMBER_FUNCTION(DateTime, GetHours, NA)
{
    for (DateTime::hour_type h = 0; h <= 23U; ++h)
    {
        DateTime dt(Date(), Time(h, 1U, 2U, 3U));
        CHECK_EQUAL(dt.GetHours(), h);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTime, SetHours, hour_type)
{
    DateTime dt;
    for (DateTime::hour_type h = 0; h <= 23U; ++h)
    {
        dt.SetHours(h);
        CHECK_EQUAL(dt.GetHours(), h);
    }
}

TEST_MEMBER_FUNCTION(DateTime, GetDate, NA)
{
    CHECK_EQUAL(DateTime().GetDate(), 0x07b20101U);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 2000U), Time()).GetDate(), 0x07d00201U);
}

TEST_CONST_MEMBER_FUNCTION(DateTime, SetDate, uint32_t)
{
    DateTime dt;

    dt.SetDate(0x07b20101U);
    CHECK_EQUAL(dt.GetDate(), 0x07b20101U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);
    CHECK_EQUAL(dt.GetYear(), 1970U);

    dt.SetDate(0x07d00201U);
    CHECK_EQUAL(dt.GetDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
}

TEST_MEMBER_FUNCTION(DateTime, GetTime, NA)
{
    DateTime dt1(Date(), Time(0U, 0U, 0U, 0U));
    DateTime dt2(Date(), Time(1U, 2U, 3U, 4U));
    DateTime dt3(Date(), Time(23U, 59U, 59U, 999U));

    CHECK_EQUAL(dt1.GetTime(), 0U);
    CHECK_EQUAL(dt2.GetTime(), 0x01020c04u);
    CHECK_EQUAL(dt3.GetTime(), 0x173befe7u);
}

TEST_CONST_MEMBER_FUNCTION(DateTime, SetTime, uint32_t)
{
    DateTime dt;

    dt.SetTime(0U);
    CHECK_EQUAL(dt.GetTime(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);

    dt.SetTime(0x01020c04u);
    CHECK_EQUAL(dt.GetTime(), 0x01020c04u);
    CHECK_EQUAL(dt.GetMilliseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);

    dt.SetTime(0x173befe7u);
    CHECK_EQUAL(dt.GetTime(), 0x173befe7u);
    CHECK_EQUAL(dt.GetMilliseconds(), 999U);
    CHECK_EQUAL(dt.GetSeconds(), 59U);
    CHECK_EQUAL(dt.GetMinutes(), 59U);
    CHECK_EQUAL(dt.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(DateTime, SetDateTime, uint32_t_uint32_t)
{
    TEST_OVERRIDE_ARGS("uint32_t, uint32_t");

    DateTime dt;

    dt.SetDateTime(0x07b20101U, 0U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);
    CHECK_EQUAL(dt.GetYear(), 1970U);
    CHECK_EQUAL(dt.GetTime(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);

    dt.SetDateTime(0x07d00201U, 0x01020c04u);
    CHECK_EQUAL(dt.GetDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
    CHECK_EQUAL(dt.GetTime(), 0x01020c04u);
    CHECK_EQUAL(dt.GetMilliseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);

    dt.SetDateTime(0x07d00201U, 0x01020c04u);
    CHECK_EQUAL(dt.GetDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
    CHECK_EQUAL(dt.GetTime(), 0x01020c04u);
    CHECK_EQUAL(dt.GetMilliseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);
}

TEST_MEMBER_FUNCTION(DateTime, AddDays, size_type)
{
    DateTime date_time;

    Date::size_type days_in_leap_year = Date::GetDaysInYear(2000U);
    Date::size_type days_in_year = Date::GetDaysInYear(2001U);

    for (DateTime::year_type year = 2000U; year <= 2001U; ++year)
    {
        for (DateTime::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            DateTime::day_type days_in_month = Date::GetDaysInMonth(month, year);

            // Test adding 0 days to every day in the month has no effect.
            for (DateTime::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                date_time.AddDays(0U);
                CHECK_EQUAL(date_time.GetDay(), day);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test offsetting days for a complete year wraps correctly to next day, month and year.
            for (DateTime::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                bool need_leap_days = (year == 2000U) && (month <= Date::FEBRUARY);
                DateTime::size_type days_to_next_year = need_leap_days ? days_in_leap_year : days_in_year;
                date_time.AddDays(days_to_next_year);
                CHECK_EQUAL(date_time, DateTime(day, month, year + 1U, 0U, 0U, 0U, 0U));
            }

            // Test adding a single day to every day except last day
            // sets correct day and doesn't wrap month.
            for (DateTime::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                date_time.AddDays(1U);
                CHECK_EQUAL(date_time.GetDay(), day + 1U);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test adding number of days to reach last day doesn't overflow the month,
            // and sets the day to the last day of the month.
            for (DateTime::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDay(day);
                date_time.AddDays(days_in_month - day);
                CHECK_EQUAL(date_time.GetDay(), days_in_month);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test adding days in the month wraps to the start of the following month.
            date_time.SetDate(1U, month, year);
            date_time.AddDays(days_in_month);
            CHECK_EQUAL(date_time.GetDay(), 1U);
            Date::month_type next_month = Date::GetNextMonth(month);
            CHECK_EQUAL(date_time.GetMonth(), next_month);
            Date::year_type expected_year = month < Date::DECEMBER ? year : year + 1U;
            CHECK_EQUAL(date_time.GetYear(), expected_year);
        }
    }
}

TEST_MEMBER_FUNCTION(DateTime, AddMiilseconds, size_type)
{
    DateTime date_time;
    date_time.SetDate(1U, Date::JANUARY, 1980U);

    // Test 0 millisecond to 1 millisecond.
    date_time.AddMiilseconds(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 1U);

    // Test 0 millisecond to 999 millisecond.
    date_time.SetStartTime();
    date_time.AddMiilseconds(999U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 999U);

    // Test 0 millisecond to 1 second.
    date_time.SetStartTime();
    date_time.AddMiilseconds(1000U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 1U);

    // Test 0 millisecond to 1 minute.
    date_time.SetStartTime();
    date_time.AddMiilseconds(Time::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 1U);

    // Test 0 millisecond to 1 hour.
    date_time.SetStartTime();
    date_time.AddMiilseconds(Time::MILLISECONDS_PER_HOUR);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 1U);

    // Test 0 millisecond to 1 day.
    date_time.SetStartTime();
    date_time.AddMiilseconds(Time::MILLISECONDS_PER_DAY);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 2U);

    // Test 0 millisecond to 1 day, 23 hours, 59 minutes, 59 seconds, 999 milliseconds.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.AddMiilseconds((Time::MILLISECONDS_PER_DAY * 2) - 1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 999U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), 2U);

    // Test 0 millisecond to 2 days.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.AddMiilseconds(Time::MILLISECONDS_PER_DAY * 2);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 3U);

    // Test 0 millisecond to 2 days and 1 millisecond.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.AddMiilseconds((Time::MILLISECONDS_PER_DAY * 2) + 1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 1U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 3U);
}

TEST_MEMBER_FUNCTION(DateTime, SubtractMiilseconds, size_type)
{
    DateTime date_time;
    date_time.SetDate(1U, Date::JANUARY, 1980U);

    // Test 999 milliseconds to 998 milliseconds.
    date_time.SetEndTime();
    date_time.SubtractMiilseconds(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 998U);

    // Test 999 milliseconds to 0 milliseconds.
    date_time.SetEndTime();
    date_time.SubtractMiilseconds(999U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);

    // Test 1 milliseconds to 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SetMilliseconds(1U);
    date_time.SubtractMiilseconds(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 1U);
    CHECK_EQUAL(date_time.GetMonth(), Date::JANUARY);
    CHECK_EQUAL(date_time.GetYear(), 1980U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 59 seconds and 999 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SubtractMiilseconds(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 999U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 59 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SubtractMiilseconds(Time::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 0 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SubtractMiilseconds(Time::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 23 hours, 0 minutes, 0 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SubtractMiilseconds(Time::MILLISECONDS_PER_HOUR);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 0 hours, 0 minutes, 0 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SubtractMiilseconds(Time::MILLISECONDS_PER_DAY);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);
}

TEST_MEMBER_FUNCTION(DateTime, Swap, DateTime_ref)
{
    TEST_OVERRIDE_ARGS("DateTime&");

    DateTime date_time1(Date(1U, Date::FEBRUARY, 1980U), Time(1U, 2U, 3U, 4U));
    DateTime date_time2(Date(3U, Date::APRIL, 2000U), Time(5U, 6U, 7U, 8U));

    date_time1.Swap(date_time2);
    CHECK_EQUAL(date_time1, DateTime(Date(3U, Date::APRIL, 2000U), Time(5U, 6U, 7U, 8U)));
    CHECK_EQUAL(date_time2, DateTime(Date(1U, Date::FEBRUARY, 1980U), Time(1U, 2U, 3U, 4U)));
}

TEST_MEMBER_FUNCTION(DateTime, Compare, DateTime_const_ref)
{
    TEST_OVERRIDE_ARGS("DateTime const&");

    // Compare date and time differences.
    CHECK_EQUAL(DateTime().Compare(DateTime()), 0);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 0);
    CHECK_EQUAL(DateTime(Date(1U, 1U, 1980U), Time(1U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1979U), Time(1U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(0U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 1U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 2U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 3U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTime(Date(2U, 2U, 1980U), Time(1U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTime(Date(1U, 3U, 1980U), Time(1U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1981U), Time(1U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(2U, 2U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 3U, 3U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 4U, 4U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 5U)).Compare(DateTime(Date(1U, 2U, 1980U), Time(1U, 2U, 3U, 4U))), 1);

    // Compare only date differences.
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time()).Compare(DateTime(Date(1U, 2U, 1980U), Time())), 0);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1980U), Time()).Compare(DateTime(Date(2U, 2U, 1980U), Time())), -1);
    CHECK_EQUAL(DateTime(Date(2U, 1U, 1980U), Time()).Compare(DateTime(Date(1U, 2U, 1980U), Time())), -1);
    CHECK_EQUAL(DateTime(Date(3U, 2U, 1979U), Time()).Compare(DateTime(Date(1U, 2U, 1980U), Time())), -1);
    CHECK_EQUAL(DateTime(Date(2U, 2U, 1980U), Time()).Compare(DateTime(Date(1U, 2U, 1980U), Time())), 1);
    CHECK_EQUAL(DateTime(Date(1U, 3U, 1980U), Time()).Compare(DateTime(Date(1U, 2U, 1980U), Time())), 1);
    CHECK_EQUAL(DateTime(Date(1U, 2U, 1981U), Time()).Compare(DateTime(Date(1U, 2U, 1980U), Time())), 1);

    // Compare only time differences.
    CHECK_EQUAL(DateTime(Date(), Time(0U, 0U, 0U, 0U)).Compare(DateTime(Date(), Time(0U, 0U, 0U, 0U))), 0);
    CHECK_EQUAL(DateTime(Date(), Time(1U, 0U, 0U, 0U)).Compare(DateTime(Date(), Time(2U, 0U, 0U, 0U))), -1);
    CHECK_EQUAL(DateTime(Date(), Time(0U, 1U, 0U, 0U)).Compare(DateTime(Date(), Time(0U, 2U, 0U, 0U))), -1);
    CHECK_EQUAL(DateTime(Date(), Time(0U, 0U, 1U, 0U)).Compare(DateTime(Date(), Time(0U, 0U, 2U, 0U))), -1);
    CHECK_EQUAL(DateTime(Date(), Time(0U, 0U, 0U, 1U)).Compare(DateTime(Date(), Time(0U, 0U, 0U, 2U))), -1);
    CHECK_EQUAL(DateTime(Date(), Time(2U, 0U, 0U, 0U)).Compare(DateTime(Date(), Time(1U, 0U, 0U, 0U))), 1);
    CHECK_EQUAL(DateTime(Date(), Time(0U, 2U, 0U, 0U)).Compare(DateTime(Date(), Time(0U, 1U, 0U, 0U))), 1);
    CHECK_EQUAL(DateTime(Date(), Time(0U, 0U, 2U, 0U)).Compare(DateTime(Date(), Time(0U, 0U, 1U, 0U))), 1);
    CHECK_EQUAL(DateTime(Date(), Time(0U, 0U, 0U, 2U)).Compare(DateTime(Date(), Time(0U, 0U, 0U, 1U))), 1);
}
