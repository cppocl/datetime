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
#include "../DateTimeRange.hpp"

using ocl::Date;
using ocl::Time;
using ocl::DateTime;
using ocl::DateTimeRange;

TEST_MEMBER_FUNCTION(DateTimeRange, constructor, NA)
{
    DateTimeRange date_time_range;
    CHECK_EQUAL(date_time_range.GetStart(), DateTime(Date(1U, 1U, Date::DEFAULT_YEAR), Time(0U, 0U, 0U, 0U)));
    CHECK_EQUAL(date_time_range.GetStop(), DateTime(Date(1U, 1U, Date::DEFAULT_YEAR), Time(0U, 0U, 0U, 0U)));
}

TEST_MEMBER_FUNCTION(DateTimeRange, constructor, Date_const_ref_Date_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTimeRange", "Date const&, Date const&");

    DateTimeRange date_time_range(DateTime(Date(1U, 1U, 1998U), Time(0U, 0U, 0U, 0U)),
                                           DateTime(Date(1U, 1U, 1999U), Time(0U, 0U, 0U, 0U)));
    CHECK_EQUAL(date_time_range.GetStart(), DateTime(Date(1U, 1U, 1998U), Time(0U, 0U, 0U, 0U)));
    CHECK_EQUAL(date_time_range.GetStop(), DateTime(Date(1U, 1U, 1999U), Time(0U, 0U, 0U, 0U)));
}

TEST_MEMBER_FUNCTION(DateTimeRange, constructor, DateRange_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTimeRange", "DateTimeRange const&");

    DateTimeRange date_time_range(DateTimeRange(DateTime(Date(1U, 1U, 1998U), Time(0U, 0U, 0U, 0U)),
                                                DateTime(Date(1U, 1U, 1999U), Time(0U, 0U, 0U, 0U))));
    CHECK_EQUAL(date_time_range.GetStart(), DateTime(Date(1U, 1U, 1998U), Time(0U, 0U, 0U, 0U)));
    CHECK_EQUAL(date_time_range.GetStop(), DateTime(Date(1U, 1U, 1999U), Time(0U, 0U, 0U, 0U)));
}

#if 0
TEST_CONST_MEMBER_FUNCTION(DateTimeRange, GetStart, NA)
{
    // NOTE: Also tests SetStart.

    {
        DateTimeRange date_time_range;
        CHECK_EQUAL(date_time_range.GetStart(), Date(1U, 1U, Date::DEFAULT_YEAR));
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_time_range.GetStart(), Date(1U, 1U, 1998U));
        date_time_range.SetStart(Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_time_range.GetStart(), Date(1U, 1U, 1999U));
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeRange, GetStop, NA)
{
    // NOTE: Also tests SetStop.

    {
        DateTimeRange date_time_range;
        CHECK_EQUAL(date_time_range.GetStop(), Date(1U, 1U, Date::DEFAULT_YEAR));
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_time_range.GetStop(), Date(1U, 1U, 1999U));
        date_time_range.SetStop(Date(1U, 1U, 1998U));
        CHECK_EQUAL(date_time_range.GetStop(), Date(1U, 1U, 1998U));
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeRange, IsWithin, Date_const_ref)
{
    TEST_OVERRIDE_ARGS("Date const&");

    DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));

    // Test pass conditions.
    CHECK_TRUE(date_time_range.IsWithin(Date(1U, 1U, 1998U)));
    CHECK_TRUE(date_time_range.IsWithin(Date(2U, 1U, 1998U)));
    CHECK_TRUE(date_time_range.IsWithin(Date(1U, 2U, 1998U)));
    CHECK_TRUE(date_time_range.IsWithin(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)));
    CHECK_TRUE(date_time_range.IsWithin(Date(1U, 1U, 1999U)));

    // Test fail conditions.
    CHECK_FALSE(date_time_range.IsWithin(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)));
    CHECK_FALSE(date_time_range.IsWithin(Date(2U, 1U, 1999U)));
}

TEST_CONST_MEMBER_FUNCTION(DateTimeRange, IsOverlapped, DateRange_const_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeRange const&");

    DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));

    // Test overlap is detect when on edge of start time.
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(1U, 1U, 1998U))));
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1998U))));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U))));
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U))));

    // Test overlap being completely consumed.
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(2U, 1U, 1998U), Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U))));
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U))));
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U))));

    // Test partial overlap at start and stop.
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U))));
    CHECK_TRUE(date_time_range.IsOverlapped(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U), Date(2U, 1U, 1999U))));

    // Test no overlap before start.
    CHECK_FALSE(date_time_range.IsOverlapped(DateTimeRange(Date(Date::DAYS_IN_DECEMBER - 1U, Date::DECEMBER, 1997U),
                                                  Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U))));

    // Test no overlap after stop.
    CHECK_FALSE(date_time_range.IsOverlapped(DateTimeRange(Date(2U, 1U, 1999U), Date(3U, 1U, 1999U))));
}

TEST_CONST_MEMBER_FUNCTION(DateTimeRange, GetOverlap, DateRange_const_ref_DateRange_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeRange const&, DateTimeRange&");

    DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));

    // Test overlap is detect when on edge of start time.
    DateTimeRange overlap;

    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(1U, 1U, 1998U)), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1998U)), overlap));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U)), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U)), overlap));

    // Test overlap being completely consumed.
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(2U, 1U, 1998U), Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)),overlap));
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U)), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U)), overlap));

    // Test partial overlap at start and stop.
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U)), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(DateTimeRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U), Date(2U, 1U, 1999U)), overlap));

    // Test no overlap before start.
    CHECK_FALSE(date_time_range.GetOverlap(DateTimeRange(Date(Date::DAYS_IN_DECEMBER - 1U, Date::DECEMBER, 1997U),
                                                Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)), overlap));

    // Test no overlap after stop.
    CHECK_FALSE(date_time_range.GetOverlap(DateTimeRange(Date(2U, 1U, 1999U), Date(3U, 1U, 1999U)), overlap));
}

TEST_CONST_MEMBER_FUNCTION(DateTimeRange, GetRangeInDays, NA)
{
    {
        DateTimeRange date_time_range;
        CHECK_EQUAL(date_time_range.GetRangeInDays(), 0U);
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(2U, 1U, 1998U));
        CHECK_EQUAL(date_time_range.GetRangeInDays(), 1U);
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 2U, 1998U));
        CHECK_EQUAL(date_time_range.GetRangeInDays(), Date::DAYS_IN_JANUARY);
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_time_range.GetRangeInDays(), Date::DAYS_PER_YEAR);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeRange, IsValid, NA)
{
    {
        DateTimeRange date_time_range;
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1998U));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(2U, 1U, 1998U));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 2U, 1998U));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        DateTimeRange date_time_range(Date(1U, 1U, 1998U), Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U));
        CHECK_FALSE(date_time_range.IsValid());
    }
}
#endif // #if 0
