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

TEST_MEMBER_FUNCTION(Date, DaysInMonth, month_type)
{
    Date::day_type days_in_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    for (Date::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        CHECK_EQUAL(days_in_month[month - Date::JANUARY], Date::DaysInMonth(month));
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

TEST_CONST_MEMBER_FUNCTION(Date, GetDay, NA)
{
    Date date1(1U, 2U, 1980U);
    CHECK_EQUAL(date1.GetDay(), 1U);

    Date date3(31U, 1U, 1980U);
    CHECK_EQUAL(date3.GetDay(), 31U);
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
