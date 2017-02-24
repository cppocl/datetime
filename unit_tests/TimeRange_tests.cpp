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
#include "../TimeRange.hpp"

using ocl::Time;
using ocl::TimeRange;

TEST_MEMBER_FUNCTION(TimeRange, constructor, NA)
{
    TimeRange time_range;
    CHECK_EQUAL(time_range.GetStart(), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(time_range.GetStop(), Time(0U, 0U, 0U, 0U));
}

TEST_MEMBER_FUNCTION(TimeRange, constructor, Time_const_ref_Time_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("TimeRange", "Time const&, Time const&");

    TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));
    CHECK_EQUAL(time_range.GetStart(), Time(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_range.GetStop(), Time(5U, 6U, 7U, 8U));
}

TEST_MEMBER_FUNCTION(TimeRange, constructor, TimeRange_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("TimeRange", "TimeRange const&");

    TimeRange time_range(TimeRange(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U)));
    CHECK_EQUAL(time_range.GetStart(), Time(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_range.GetStop(), Time(5U, 6U, 7U, 8U));
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, GetStart, NA)
{
    // NOTE: Also tests SetStart.

    {
        TimeRange time_range;
        CHECK_EQUAL(time_range.GetStart(), Time(0U, 0U, 0U, 0U));
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), Time(1U, 2U, 3U, 4U));
        time_range.SetStart(Time(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), Time(5U, 6U, 7U, 8U));
    }
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, GetStop, NA)
{
    // NOTE: Also tests SetStop.

    {
        TimeRange time_range;
        CHECK_EQUAL(time_range.GetStop(), Time(0U, 0U, 0U, 0U));
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStop(), Time(5U, 6U, 7U, 8U));
        time_range.SetStop(Time(1U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetStop(), Time(1U, 2U, 3U, 4U));
    }
}

TEST_MEMBER_FUNCTION(TimeRange, ResetToStart, NA)
{
    TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));
    CHECK_EQUAL(time_range.GetStart(), Time(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_range.GetStop(), Time(5U, 6U, 7U, 8U));
    time_range.ResetToStart();
    CHECK_EQUAL(time_range.GetStart(), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(time_range.GetStop(), Time(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, IsWithin, Time_const_ref)
{
    TEST_OVERRIDE_ARGS("Time const&");

    TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));

    // Test pass conditions.
    CHECK_TRUE(time_range.IsWithin(Time(1U, 2U, 3U, 4U)));
    CHECK_TRUE(time_range.IsWithin(Time(3U, 4U, 5U, 6U)));
    CHECK_TRUE(time_range.IsWithin(Time(5U, 6U, 7U, 8U)));

    // Test fail conditions.
    CHECK_FALSE(time_range.IsWithin(Time(1U, 2U, 3U, 3U)));
    CHECK_FALSE(time_range.IsWithin(Time(5U, 6U, 7U, 9U)));
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, IsOverlapped, TimeRange_const_ref)
{
    TEST_OVERRIDE_ARGS("TimeRange const&");

    TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));

    // Test overlap is detect when on edge of start time.
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 3U), Time(1U, 2U, 3U, 4U))));
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 4U), Time(1U, 2U, 3U, 4U))));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(5U, 6U, 7U, 8U), Time(5U, 6U, 7U, 8U))));
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(5U, 6U, 7U, 8U), Time(5U, 6U, 7U, 9U))));

    // Test overlap being completely consumed.
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 5U), Time(5U, 6U, 7U, 7U))));
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U))));
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 3U), Time(5U, 6U, 7U, 9U))));

    // Test partial overlap at start and stop.
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 3U), Time(1U, 2U, 3U, 5U))));
    CHECK_TRUE(time_range.IsOverlapped(TimeRange(Time(5U, 6U, 7U, 7U), Time(5U, 6U, 7U, 9U))));

    // Test no overlap before start.
    CHECK_FALSE(time_range.IsOverlapped(TimeRange(Time(1U, 2U, 3U, 2U), Time(1U, 2U, 3U, 3U))));

    // Test no overlap after stop.
    CHECK_FALSE(time_range.IsOverlapped(TimeRange(Time(5U, 6U, 7U, 9U), Time(5U, 6U, 7U, 10U))));
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, GetOverlap, TimeRange_const_ref_TimeRange_ref)
{
    TEST_OVERRIDE_ARGS("TimeRange const&, TimeRange&");

    TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U));
    TimeRange overlap;

    // Test overlap is detect when on edge of start time.
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(1U, 2U, 3U, 3U), Time(1U, 2U, 3U, 4U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(Time(1U, 2U, 3U, 4U)));
    CHECK_EQUAL(overlap.GetStop(), Time(Time(1U, 2U, 3U, 4U)));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(5U, 6U, 7U, 8U), Time(5U, 6U, 7U, 9U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(5U, 6U, 7U, 8U));
    CHECK_EQUAL(overlap.GetStop(), Time(5U, 6U, 7U, 8U));

    // Test overlap being completely consumed.
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(1U, 2U, 3U, 5U), Time(5U, 6U, 7U, 7U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(1U, 2U, 3U, 5U));
    CHECK_EQUAL(overlap.GetStop(), Time(5U, 6U, 7U, 7U));
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(1U, 2U, 3U, 4U), Time(5U, 6U, 7U, 8U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(1U, 2U, 3U, 4U));
    CHECK_EQUAL(overlap.GetStop(), Time(5U, 6U, 7U, 8U));
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(1U, 2U, 3U, 3U), Time(5U, 6U, 7U, 9U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(1U, 2U, 3U, 4U));
    CHECK_EQUAL(overlap.GetStop(), Time(5U, 6U, 7U, 8U));

    // Test partial overlap at start and stop.
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(1U, 2U, 3U, 3U), Time(1U, 2U, 3U, 5U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(1U, 2U, 3U, 4U));
    CHECK_EQUAL(overlap.GetStop(), Time(1U, 2U, 3U, 5U));
    CHECK_TRUE(time_range.GetOverlap(TimeRange(Time(5U, 6U, 7U, 7U), Time(5U, 6U, 7U, 9U)), overlap));
    CHECK_EQUAL(overlap.GetStart(), Time(5U, 6U, 7U, 7U));
    CHECK_EQUAL(overlap.GetStop(), Time(5U, 6U, 7U, 8U));

    // Test no overlap before start.
    CHECK_FALSE(time_range.GetOverlap(TimeRange(Time(1U, 2U, 3U, 2U), Time(1U, 2U, 3U, 3U)), overlap));

    // Test no overlap after stop.
    CHECK_FALSE(time_range.GetOverlap(TimeRange(Time(5U, 6U, 7U, 9U), Time(5U, 6U, 7U, 10U)), overlap));
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, GetRangeInMilliseconds, NA)
{
    {
        TimeRange time_range;
        CHECK_EQUAL(time_range.GetRangeInMilliseconds(), 0U);
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(1U, 2U, 3U, 5U));
        CHECK_EQUAL(time_range.GetRangeInMilliseconds(), 1U);
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(1U, 2U, 4U, 4U));
        CHECK_EQUAL(time_range.GetRangeInMilliseconds(), Time::MILLISECONDS_PER_SECOND);
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(1U, 3U, 3U, 4U));
        CHECK_EQUAL(time_range.GetRangeInMilliseconds(), Time::MILLISECONDS_PER_MINUTE);
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(2U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetRangeInMilliseconds(), Time::MILLISECONDS_PER_HOUR);
    }
}

TEST_CONST_MEMBER_FUNCTION(TimeRange, IsValid, NA)
{
    {
        TimeRange time_range;
        CHECK_TRUE(time_range.IsValid());
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(1U, 2U, 3U, 4U));
        CHECK_TRUE(time_range.IsValid());
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(1U, 2U, 3U, 5U));
        CHECK_TRUE(time_range.IsValid());
    }

    {
        TimeRange time_range(Time(1U, 2U, 3U, 4U), Time(1U, 2U, 3U, 3U));
        CHECK_FALSE(time_range.IsValid());
    }
}
