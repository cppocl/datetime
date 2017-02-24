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
#include "../DateRange.hpp"

using ocl::Date;
using ocl::DateRange;

TEST_MEMBER_FUNCTION(DateRange, constructor, NA)
{
    DateRange date_range;
    CHECK_EQUAL(date_range.GetStart(), Date(1U, 1U, Date::DEFAULT_YEAR));
    CHECK_EQUAL(date_range.GetStop(), Date(1U, 1U, Date::DEFAULT_YEAR));
}

TEST_MEMBER_FUNCTION(DateRange, constructor, Date_const_ref_Date_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateRange", "Date const&, Date const&");

    DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
    CHECK_EQUAL(date_range.GetStart(), Date(1U, 1U, 1998U));
    CHECK_EQUAL(date_range.GetStop(), Date(1U, 1U, 1999U));
}

TEST_MEMBER_FUNCTION(DateRange, constructor, DateRange_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateRange", "DateRange const&");

    DateRange date_range(DateRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U)));
    CHECK_EQUAL(date_range.GetStart(), Date(1U, 1U, 1998U));
    CHECK_EQUAL(date_range.GetStop(), Date(1U, 1U, 1999U));
}

TEST_CONST_MEMBER_FUNCTION(DateRange, GetStart, NA)
{
    // NOTE: Also tests SetStart.

    {
        DateRange date_range;
        CHECK_EQUAL(date_range.GetStart(), Date(1U, 1U, Date::DEFAULT_YEAR));
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_range.GetStart(), Date(1U, 1U, 1998U));
        date_range.SetStart(Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_range.GetStart(), Date(1U, 1U, 1999U));
    }
}

TEST_CONST_MEMBER_FUNCTION(DateRange, GetStop, NA)
{
    // NOTE: Also tests SetStop.

    {
        DateRange date_range;
        CHECK_EQUAL(date_range.GetStop(), Date(1U, 1U, Date::DEFAULT_YEAR));
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_range.GetStop(), Date(1U, 1U, 1999U));
        date_range.SetStop(Date(1U, 1U, 1998U));
        CHECK_EQUAL(date_range.GetStop(), Date(1U, 1U, 1998U));
    }
}

TEST_CONST_MEMBER_FUNCTION(DateRange, IsWithin, Date_const_ref)
{
    TEST_OVERRIDE_ARGS("Date const&");

    DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));

    // Test pass conditions.
    CHECK_TRUE(date_range.IsWithin(Date(1U, 1U, 1998U)));
    CHECK_TRUE(date_range.IsWithin(Date(2U, 1U, 1998U)));
    CHECK_TRUE(date_range.IsWithin(Date(1U, 2U, 1998U)));
    CHECK_TRUE(date_range.IsWithin(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)));
    CHECK_TRUE(date_range.IsWithin(Date(1U, 1U, 1999U)));

    // Test fail conditions.
    CHECK_FALSE(date_range.IsWithin(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)));
    CHECK_FALSE(date_range.IsWithin(Date(2U, 1U, 1999U)));
}

TEST_CONST_MEMBER_FUNCTION(DateRange, IsOverlapped, DateRange_const_ref)
{
    TEST_OVERRIDE_ARGS("DateRange const&");

    DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));

    // Test overlap is detect when on edge of start time.
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(1U, 1U, 1998U))));
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1998U))));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U))));
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U))));

    // Test overlap being completely consumed.
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(2U, 1U, 1998U), Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U))));
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U))));
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U))));

    // Test partial overlap at start and stop.
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U))));
    CHECK_TRUE(date_range.IsOverlapped(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U), Date(2U, 1U, 1999U))));

    // Test no overlap before start.
    CHECK_FALSE(date_range.IsOverlapped(DateRange(Date(Date::DAYS_IN_DECEMBER - 1U, Date::DECEMBER, 1997U),
                                                  Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U))));

    // Test no overlap after stop.
    CHECK_FALSE(date_range.IsOverlapped(DateRange(Date(2U, 1U, 1999U), Date(3U, 1U, 1999U))));
}

TEST_CONST_MEMBER_FUNCTION(DateRange, GetOverlap, DateRange_const_ref_DateRange_ref)
{
    TEST_OVERRIDE_ARGS("DateRange const&, DateRange&");

    DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));

    // Test overlap is detect when on edge of start time.
    DateRange overlap;

    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(1U, 1U, 1998U)), overlap));
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1998U)), overlap));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U)), overlap));
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(1U, 1U, 1999U), Date(2U, 1U, 1999U)), overlap));

    // Test overlap being completely consumed.
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(2U, 1U, 1998U), Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)),overlap));
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U)), overlap));
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U)), overlap));

    // Test partial overlap at start and stop.
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U), Date(2U, 1U, 1999U)), overlap));
    CHECK_TRUE(date_range.GetOverlap(DateRange(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U), Date(2U, 1U, 1999U)), overlap));

    // Test no overlap before start.
    CHECK_FALSE(date_range.GetOverlap(DateRange(Date(Date::DAYS_IN_DECEMBER - 1U, Date::DECEMBER, 1997U),
                                                Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)), overlap));

    // Test no overlap after stop.
    CHECK_FALSE(date_range.GetOverlap(DateRange(Date(2U, 1U, 1999U), Date(3U, 1U, 1999U)), overlap));
}

TEST_CONST_MEMBER_FUNCTION(DateRange, GetRangeInDays, NA)
{
    {
        DateRange date_range;
        CHECK_EQUAL(date_range.GetRangeInDays(), 0U);
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(2U, 1U, 1998U));
        CHECK_EQUAL(date_range.GetRangeInDays(), 1U);
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 2U, 1998U));
        CHECK_EQUAL(date_range.GetRangeInDays(), Date::DAYS_IN_JANUARY);
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_EQUAL(date_range.GetRangeInDays(), Date::DAYS_PER_YEAR);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateRange, IsValid, NA)
{
    {
        DateRange date_range;
        CHECK_TRUE(date_range.IsValid());
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1998U));
        CHECK_TRUE(date_range.IsValid());
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(2U, 1U, 1998U));
        CHECK_TRUE(date_range.IsValid());
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 2U, 1998U));
        CHECK_TRUE(date_range.IsValid());
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(1U, 1U, 1999U));
        CHECK_TRUE(date_range.IsValid());
    }

    {
        DateRange date_range(Date(1U, 1U, 1998U), Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U));
        CHECK_FALSE(date_range.IsValid());
    }
}
