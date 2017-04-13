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
typedef Time<ocl::Milliseconds> time_ms_type;
typedef Time<ocl::Nanoseconds>  time_ns_type;
typedef TimeRange<ocl::Milliseconds> time_range_ms_type;
typedef TimeRange<ocl::Nanoseconds>  time_range_ns_type;

TEST_MEMBER_FUNCTION(time_range, constructor, NA)
{
    time_range_ms_type time_ms_range;
    CHECK_EQUAL(time_ms_range.GetStart(), time_ms_type(0U, 0U, 0U, 0U));
    CHECK_EQUAL(time_ms_range.GetStop(), time_ms_type(0U, 0U, 0U, 0U));

    time_range_ns_type time_ns_range;
    CHECK_EQUAL(time_ns_range.GetStart(), time_ns_type(0U, 0U, 0U, 0U));
    CHECK_EQUAL(time_ns_range.GetStop(), time_ns_type(0U, 0U, 0U, 0U));
}

TEST_MEMBER_FUNCTION(time_range, constructor, Time_const_ref_Time_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("time_range", "time_ms_type const&, time_ms_type const&");

    time_range_ms_type time_ms_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));
    CHECK_EQUAL(time_ms_range.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_ms_range.GetStop(), time_ms_type(5U, 6U, 7U, 8U));

    time_range_ns_type time_ns_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));
    CHECK_EQUAL(time_ns_range.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_ns_range.GetStop(), time_ns_type(5U, 6U, 7U, 8U));
}

TEST_MEMBER_FUNCTION(time_range, constructor, TimeRange_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("time_range", "time_range const&");

    time_range_ms_type time_ms_range(time_range_ms_type(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U)));
    CHECK_EQUAL(time_ms_range.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_ms_range.GetStop(), time_ms_type(5U, 6U, 7U, 8U));

    time_range_ns_type time_ns_range(time_range_ns_type(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U)));
    CHECK_EQUAL(time_ns_range.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
    CHECK_EQUAL(time_ns_range.GetStop(), time_ns_type(5U, 6U, 7U, 8U));
}

TEST_CONST_MEMBER_FUNCTION(time_range, GetStart, NA)
{
    // NOTE: Also tests SetStart.

    {
        time_range_ms_type time_range;
        CHECK_EQUAL(time_range.GetStart(), time_ms_type(0U, 0U, 0U, 0U));
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
        time_range.SetStart(time_ms_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), time_ms_type(5U, 6U, 7U, 8U));
    }

    {
        time_range_ns_type time_range;
        CHECK_EQUAL(time_range.GetStart(), time_ns_type(0U, 0U, 0U, 0U));
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
        time_range.SetStart(time_ns_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), time_ns_type(5U, 6U, 7U, 8U));
    }
}

TEST_CONST_MEMBER_FUNCTION(time_range, GetStop, NA)
{
    // NOTE: Also tests SetStop.

    {
        time_range_ms_type time_range;
        CHECK_EQUAL(time_range.GetStop(), time_ms_type(0U, 0U, 0U, 0U));
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStop(), time_ms_type(5U, 6U, 7U, 8U));
        time_range.SetStop(time_ms_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetStop(), time_ms_type(1U, 2U, 3U, 4U));
    }

    {
        time_range_ns_type time_range;
        CHECK_EQUAL(time_range.GetStop(), time_ns_type(0U, 0U, 0U, 0U));
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStop(), time_ns_type(5U, 6U, 7U, 8U));
        time_range.SetStop(time_ns_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetStop(), time_ns_type(1U, 2U, 3U, 4U));
    }
}

TEST_MEMBER_FUNCTION(time_range, ResetToStart, NA)
{
    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetStop(), time_ms_type(5U, 6U, 7U, 8U));
        time_range.ResetToStart();
        CHECK_EQUAL(time_range.GetStart(), time_ms_type(0U, 0U, 0U, 0U));
        CHECK_EQUAL(time_range.GetStop(), time_ms_type(0U, 0U, 0U, 0U));
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time_range.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetStop(), time_ns_type(5U, 6U, 7U, 8U));
        time_range.ResetToStart();
        CHECK_EQUAL(time_range.GetStart(), time_ns_type(0U, 0U, 0U, 0U));
        CHECK_EQUAL(time_range.GetStop(), time_ns_type(0U, 0U, 0U, 0U));
    }
}

TEST_CONST_MEMBER_FUNCTION(time_range, IsWithin, Time_const_ref)
{
    TEST_OVERRIDE_ARGS("time_ms_type const&");

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));

        // Test pass conditions.
        CHECK_TRUE(time_range.IsWithin(time_ms_type(1U, 2U, 3U, 4U)));
        CHECK_TRUE(time_range.IsWithin(time_ms_type(3U, 4U, 5U, 6U)));
        CHECK_TRUE(time_range.IsWithin(time_ms_type(5U, 6U, 7U, 8U)));

        // Test fail conditions.
        CHECK_FALSE(time_range.IsWithin(time_ms_type(1U, 2U, 3U, 3U)));
        CHECK_FALSE(time_range.IsWithin(time_ms_type(5U, 6U, 7U, 9U)));
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));

        // Test pass conditions.
        CHECK_TRUE(time_range.IsWithin(time_ns_type(1U, 2U, 3U, 4U)));
        CHECK_TRUE(time_range.IsWithin(time_ns_type(3U, 4U, 5U, 6U)));
        CHECK_TRUE(time_range.IsWithin(time_ns_type(5U, 6U, 7U, 8U)));

        // Test fail conditions.
        CHECK_FALSE(time_range.IsWithin(time_ns_type(1U, 2U, 3U, 3U)));
        CHECK_FALSE(time_range.IsWithin(time_ns_type(5U, 6U, 7U, 9U)));
    }
}

TEST_CONST_MEMBER_FUNCTION(time_range, IsOverlapped, TimeRange_const_ref)
{
    TEST_OVERRIDE_ARGS("time_range const&");

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));

        // Test overlap is detected when on edge of start time.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 3U), time_ms_type(1U, 2U, 3U, 4U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 2U, 3U, 4U))));

        // Test overlap is detected when on edge of stop time.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(5U, 6U, 7U, 8U), time_ms_type(5U, 6U, 7U, 8U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(5U, 6U, 7U, 8U), time_ms_type(5U, 6U, 7U, 9U))));

        // Test overlap being completely consumed.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 5U), time_ms_type(5U, 6U, 7U, 7U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 3U), time_ms_type(5U, 6U, 7U, 9U))));

        // Test partial overlap at start and stop.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 3U), time_ms_type(1U, 2U, 3U, 5U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(5U, 6U, 7U, 7U), time_ms_type(5U, 6U, 7U, 9U))));

        // Test no overlap before start.
        CHECK_FALSE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(1U, 2U, 3U, 2U), time_ms_type(1U, 2U, 3U, 3U))));

        // Test no overlap after stop.
        CHECK_FALSE(time_range.IsOverlapped(time_range_ms_type(time_ms_type(5U, 6U, 7U, 9U), time_ms_type(5U, 6U, 7U, 10U))));
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));

        // Test overlap is detected when on edge of start time.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 3U), time_ns_type(1U, 2U, 3U, 4U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 2U, 3U, 4U))));

        // Test overlap is detected when on edge of stop time.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(5U, 6U, 7U, 8U), time_ns_type(5U, 6U, 7U, 8U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(5U, 6U, 7U, 8U), time_ns_type(5U, 6U, 7U, 9U))));

        // Test overlap being completely consumed.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 5U), time_ns_type(5U, 6U, 7U, 7U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 3U), time_ns_type(5U, 6U, 7U, 9U))));

        // Test partial overlap at start and stop.
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 3U), time_ns_type(1U, 2U, 3U, 5U))));
        CHECK_TRUE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(5U, 6U, 7U, 7U), time_ns_type(5U, 6U, 7U, 9U))));

        // Test no overlap before start.
        CHECK_FALSE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(1U, 2U, 3U, 2U), time_ns_type(1U, 2U, 3U, 3U))));

        // Test no overlap after stop.
        CHECK_FALSE(time_range.IsOverlapped(time_range_ns_type(time_ns_type(5U, 6U, 7U, 9U), time_ns_type(5U, 6U, 7U, 10U))));
    }
}

TEST_CONST_MEMBER_FUNCTION(time_range, GetOverlap, TimeRange_const_ref_TimeRange_ref)
{
    TEST_OVERRIDE_ARGS("time_range const&, time_range&");

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U));
        time_range_ms_type overlap;

        // Test overlap is detect when on edge of start time.
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(1U, 2U, 3U, 3U), time_ms_type(1U, 2U, 3U, 4U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(time_ms_type(1U, 2U, 3U, 4U)));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(time_ms_type(1U, 2U, 3U, 4U)));

        // Test overlap is detect when on edge of stop time.
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(5U, 6U, 7U, 8U), time_ms_type(5U, 6U, 7U, 9U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(5U, 6U, 7U, 8U));

        // Test overlap being completely consumed.
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(1U, 2U, 3U, 5U), time_ms_type(5U, 6U, 7U, 7U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(1U, 2U, 3U, 5U));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(5U, 6U, 7U, 7U));
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(5U, 6U, 7U, 8U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(5U, 6U, 7U, 8U));
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(1U, 2U, 3U, 3U), time_ms_type(5U, 6U, 7U, 9U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(5U, 6U, 7U, 8U));

        // Test partial overlap at start and stop.
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(1U, 2U, 3U, 3U), time_ms_type(1U, 2U, 3U, 5U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(1U, 2U, 3U, 5U));
        CHECK_TRUE(time_range.GetOverlap(time_range_ms_type(time_ms_type(5U, 6U, 7U, 7U), time_ms_type(5U, 6U, 7U, 9U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ms_type(5U, 6U, 7U, 7U));
        CHECK_EQUAL(overlap.GetStop(), time_ms_type(5U, 6U, 7U, 8U));

        // Test no overlap before start.
        CHECK_FALSE(time_range.GetOverlap(time_range_ms_type(time_ms_type(1U, 2U, 3U, 2U), time_ms_type(1U, 2U, 3U, 3U)), overlap));

        // Test no overlap after stop.
        CHECK_FALSE(time_range.GetOverlap(time_range_ms_type(time_ms_type(5U, 6U, 7U, 9U), time_ms_type(5U, 6U, 7U, 10U)), overlap));
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U));
        time_range_ns_type overlap;

        // Test overlap is detect when on edge of start time.
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(1U, 2U, 3U, 3U), time_ns_type(1U, 2U, 3U, 4U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(time_ns_type(1U, 2U, 3U, 4U)));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(time_ns_type(1U, 2U, 3U, 4U)));

        // Test overlap is detect when on edge of stop time.
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(5U, 6U, 7U, 8U), time_ns_type(5U, 6U, 7U, 9U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(5U, 6U, 7U, 8U));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(5U, 6U, 7U, 8U));

        // Test overlap being completely consumed.
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(1U, 2U, 3U, 5U), time_ns_type(5U, 6U, 7U, 7U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(1U, 2U, 3U, 5U));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(5U, 6U, 7U, 7U));
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(5U, 6U, 7U, 8U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(5U, 6U, 7U, 8U));
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(1U, 2U, 3U, 3U), time_ns_type(5U, 6U, 7U, 9U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(5U, 6U, 7U, 8U));

        // Test partial overlap at start and stop.
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(1U, 2U, 3U, 3U), time_ns_type(1U, 2U, 3U, 5U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(1U, 2U, 3U, 4U));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(1U, 2U, 3U, 5U));
        CHECK_TRUE(time_range.GetOverlap(time_range_ns_type(time_ns_type(5U, 6U, 7U, 7U), time_ns_type(5U, 6U, 7U, 9U)), overlap));
        CHECK_EQUAL(overlap.GetStart(), time_ns_type(5U, 6U, 7U, 7U));
        CHECK_EQUAL(overlap.GetStop(), time_ns_type(5U, 6U, 7U, 8U));

        // Test no overlap before start.
        CHECK_FALSE(time_range.GetOverlap(time_range_ns_type(time_ns_type(1U, 2U, 3U, 2U), time_ns_type(1U, 2U, 3U, 3U)), overlap));

        // Test no overlap after stop.
        CHECK_FALSE(time_range.GetOverlap(time_range_ns_type(time_ns_type(5U, 6U, 7U, 9U), time_ns_type(5U, 6U, 7U, 10U)), overlap));
    }
}

TEST_CONST_MEMBER_FUNCTION(time_range, GetRange, NA)
{
    {
        time_range_ms_type time_range;
        CHECK_EQUAL(time_range.GetRange(), 0U);
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 2U, 3U, 5U));
        CHECK_EQUAL(time_range.GetRange(), 1U);
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 2U, 4U, 4U));
        CHECK_EQUAL(time_range.GetRange(), time_ms_type::MILLISECONDS_PER_SECOND);
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 3U, 3U, 4U));
        CHECK_EQUAL(time_range.GetRange(), time_ms_type::MILLISECONDS_PER_MINUTE);
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(2U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetRange(), time_ms_type::MILLISECONDS_PER_HOUR);
    }

    {
        time_range_ns_type time_range;
        CHECK_EQUAL(time_range.GetRange(), 0U);
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 2U, 3U, 5U));
        CHECK_EQUAL(time_range.GetRange(), 1U);
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 2U, 4U, 4U));
        CHECK_EQUAL(time_range.GetRange(), time_ns_type::NANOSECONDS_PER_SECOND);
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 3U, 3U, 4U));
        CHECK_EQUAL(time_range.GetRange(), time_ns_type::NANOSECONDS_PER_MINUTE);
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(2U, 2U, 3U, 4U));
        CHECK_EQUAL(time_range.GetRange(), time_ns_type::NANOSECONDS_PER_HOUR);
    }
}

TEST_CONST_MEMBER_FUNCTION(time_range, IsValid, NA)
{
    {
        time_range_ms_type time_range;
        CHECK_TRUE(time_range.IsValid());
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 2U, 3U, 4U));
        CHECK_TRUE(time_range.IsValid());
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 2U, 3U, 5U));
        CHECK_TRUE(time_range.IsValid());
    }

    {
        time_range_ms_type time_range(time_ms_type(1U, 2U, 3U, 4U), time_ms_type(1U, 2U, 3U, 3U));
        CHECK_FALSE(time_range.IsValid());
    }

    //
    {
        time_range_ns_type time_range;
        CHECK_TRUE(time_range.IsValid());
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 2U, 3U, 4U));
        CHECK_TRUE(time_range.IsValid());
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 2U, 3U, 5U));
        CHECK_TRUE(time_range.IsValid());
    }

    {
        time_range_ns_type time_range(time_ns_type(1U, 2U, 3U, 4U), time_ns_type(1U, 2U, 3U, 3U));
        CHECK_FALSE(time_range.IsValid());
    }
}
