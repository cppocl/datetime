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
#include "../DateTime.hpp"
#include "../Date.hpp"
#include "../Time.hpp"

typedef ocl::Time<ocl::Milliseconds>::size_type time_size_type;

using ocl::Date;
using ocl::Time;
typedef typename Time<ocl::Milliseconds> time_ms_type;
typedef typename ocl::DateTime<ocl::Milliseconds> date_time_ms_type;
typedef typename ocl::DateTimeRange<ocl::Milliseconds> date_time_range_ms_type;

TEST_MEMBER_FUNCTION(date_time_range_ms_type, constructor, NA)
{
    Date const default_date(1U, 1U, Date::DEFAULT_YEAR);

    date_time_range_ms_type date_time_range;

    CHECK_EQUAL(date_time_range.GetStart(), date_time_ms_type(default_date));
    CHECK_EQUAL(date_time_range.GetStop(), date_time_ms_type(default_date));
}

TEST_MEMBER_FUNCTION(date_time_range_ms_type, constructor, Date_const_ref_Date_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("date_time_range_ms_type", "Date const&, Date const&");

    date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)),
                                            date_time_ms_type(Date(1U, 1U, 1999U)));

    CHECK_EQUAL(date_time_range.GetStart(), date_time_ms_type(Date(1U, 1U, 1998U)));
    CHECK_EQUAL(date_time_range.GetStop(), date_time_ms_type(Date(1U, 1U, 1999U)));
}

TEST_MEMBER_FUNCTION(date_time_range_ms_type, constructor, DateRange_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("date_time_range_ms_type", "date_time_range_ms_type const&");

    date_time_range_ms_type date_time_range(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1998U)),
                                            date_time_ms_type(Date(1U, 1U, 1999U))));
    CHECK_EQUAL(date_time_range.GetStart(), date_time_ms_type(Date(1U, 1U, 1998U)));
    CHECK_EQUAL(date_time_range.GetStop(), date_time_ms_type(Date(1U, 1U, 1999U)));
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, GetStart, NA)
{
    // NOTE: Also tests SetStart.

    Date const default_date(1U, 1U, Date::DEFAULT_YEAR);

    {
        date_time_range_ms_type date_time_range;
        CHECK_EQUAL(date_time_range.GetStart(), date_time_ms_type(default_date));
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)),
                                                date_time_ms_type(Date(1U, 1U, 1999U)));

        CHECK_EQUAL(date_time_range.GetStart(), date_time_ms_type(Date(1U, 1U, 1998U)));

        Date start_date(1U, 1U, 1999U);
        //time_ms_type start_time(1U, 2U, 3U, 4U);
        //date_time_ms_type start_date_time(start_date, start_time);
        //date_time_range.SetStart(start_date_time);
        //CHECK_EQUAL(date_time_range.GetStart(), date_time_ms_type(Date(1U, 1U, 1999U), time_ms_type(1U, 2U, 3U, 4U)));
    }
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, GetStop, NA)
{
    // NOTE: Also tests SetStop.

    Date const default_date(1U, 1U, Date::DEFAULT_YEAR);

    {
        date_time_range_ms_type date_time_range;
        CHECK_EQUAL(date_time_range.GetStop(), date_time_ms_type(Date(1U, 1U, Date::DEFAULT_YEAR)));
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)),
                                                date_time_ms_type(Date(1U, 1U, 1999U)));

        CHECK_EQUAL(date_time_range.GetStop(), date_time_ms_type(Date(1U, 1U, 1999U)));
        date_time_range.SetStop(date_time_ms_type(Date(1U, 1U, 1998U), time_ms_type(1U, 2U, 3U, 4U)));
        CHECK_EQUAL(date_time_range.GetStop(), date_time_ms_type(Date(1U, 1U, 1998U), time_ms_type(1U, 2U, 3U, 4U)));
    }
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, IsWithin, Date_const_ref)
{
    TEST_OVERRIDE_ARGS("Date const&");

    date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)),
                                  date_time_ms_type(Date(1U, 1U, 1999U)));

    // Test pass conditions.
    CHECK_TRUE(date_time_range.IsWithin(date_time_ms_type(Date(1U, 1U, 1998U))));
    CHECK_TRUE(date_time_range.IsWithin(date_time_ms_type(Date(2U, 1U, 1998U))));
    CHECK_TRUE(date_time_range.IsWithin(date_time_ms_type(Date(1U, 2U, 1998U))));
    CHECK_TRUE(date_time_range.IsWithin(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U))));
    CHECK_TRUE(date_time_range.IsWithin(date_time_ms_type(Date(1U, 1U, 1999U))));

    // Test fail conditions.
    CHECK_FALSE(date_time_range.IsWithin(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U))));
    CHECK_FALSE(date_time_range.IsWithin(date_time_ms_type(Date(2U, 1U, 1999U))));
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, IsOverlapped, DateRange_const_ref)
{
    TEST_OVERRIDE_ARGS("date_time_range_ms_type const&");

    date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)),
                                  date_time_ms_type(Date(1U, 1U, 1999U)));

    // Test overlap is detect when on edge of start time.
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)),
                                                                    date_time_ms_type(Date(1U, 1U, 1998U)))));
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1998U)),
                                                                    date_time_ms_type(Date(1U, 1U, 1998U)))));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1999U)),
                                                                    date_time_ms_type(Date(2U, 1U, 1999U)))));
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1999U)),
                                                                    date_time_ms_type(Date(2U, 1U, 1999U)))));

    // Test overlap being completely consumed.
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(2U, 1U, 1998U)),
                                                                    date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)))));
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1998U)),
                                                                    date_time_ms_type(Date(1U, 1U, 1999U)))));
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)),
                                                                    date_time_ms_type(Date(2U, 1U, 1999U)))));

    // Test partial overlap at start and stop.
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)),
                                                          date_time_ms_type(Date(2U, 1U, 1999U)))));
    CHECK_TRUE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)),
                                                          date_time_ms_type(Date(2U, 1U, 1999U)))));

    // Test no overlap before start.
    CHECK_FALSE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER - 1U, Date::DECEMBER, 1997U)),
                                                           date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)))));

    // Test no overlap after stop.
    CHECK_FALSE(date_time_range.IsOverlapped(date_time_range_ms_type(date_time_ms_type(Date(2U, 1U, 1999U)),
                                                           date_time_ms_type(Date(3U, 1U, 1999U)))));
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, GetOverlap, DateRange_const_ref_DateRange_ref)
{
    TEST_OVERRIDE_ARGS("date_time_range_ms_type const&, date_time_range_ms_type&");

    date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)),
                                            date_time_ms_type(Date(1U, 1U, 1999U)));

    // Test overlap is detect when on edge of start time.
    date_time_range_ms_type overlap;

    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)),
                                                                  date_time_ms_type(Date(1U, 1U, 1998U))), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1998U)),
                                                                  date_time_ms_type(Date(1U, 1U, 1998U))), overlap));

    // Test overlap is detect when on edge of stop time.
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1999U)),
                                                                  date_time_ms_type(Date(2U, 1U, 1999U))), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1999U)),
                                                                  date_time_ms_type(Date(2U, 1U, 1999U))), overlap));

    // Test overlap being completely consumed.
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(2U, 1U, 1998U)),
                                                                  date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U))), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(1U, 1U, 1998U)),
                                                                  date_time_ms_type(Date(1U, 1U, 1999U))), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)),
                                                                  date_time_ms_type(Date(2U, 1U, 1999U))), overlap));

    // Test partial overlap at start and stop.
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)),
                                                                  date_time_ms_type(Date(2U, 1U, 1999U))), overlap));
    CHECK_TRUE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1998U)),
                                                                  date_time_ms_type(Date(2U, 1U, 1999U))), overlap));

    // Test no overlap before start.
    CHECK_FALSE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(Date::DAYS_IN_DECEMBER - 1U, Date::DECEMBER, 1997U)),
                                                                   date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U))), overlap));

    // Test no overlap after stop.
    CHECK_FALSE(date_time_range.GetOverlap(date_time_range_ms_type(date_time_ms_type(Date(2U, 1U, 1999U)),
                                                                   date_time_ms_type(Date(3U, 1U, 1999U))), overlap));
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, GetDifference, NA)
{
    date_time_ms_type::date_size_type days = 1U;         // Default both to unexpected result.
    time_size_type milliseconds = 1U;

    {
        date_time_range_ms_type date_time_range;
        date_time_range.GetDifference(days, milliseconds);
        CHECK_EQUAL(days, 0U);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(2U, 1U, 1998U)));
        date_time_range.GetDifference(days, milliseconds);
        CHECK_EQUAL(days, 1U);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(1U, 2U, 1998U)));
        date_time_range.GetDifference(days, milliseconds);
        CHECK_EQUAL(days, Date::DAYS_IN_JANUARY);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(1U, 1U, 1999U)));
        date_time_range.GetDifference(days, milliseconds);
        CHECK_EQUAL(days, Date::DAYS_PER_YEAR);
        CHECK_EQUAL(milliseconds, 0U);
    }
}

TEST_CONST_MEMBER_FUNCTION(date_time_range_ms_type, IsValid, NA)
{
    {
        date_time_range_ms_type date_time_range;
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(1U, 1U, 1998U)));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(2U, 1U, 1998U)));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(1U, 2U, 1998U)));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(1U, 1U, 1999U)));
        CHECK_TRUE(date_time_range.IsValid());
    }

    {
        date_time_range_ms_type date_time_range(date_time_ms_type(Date(1U, 1U, 1998U)), date_time_ms_type(Date(Date::DAYS_IN_DECEMBER, Date::DECEMBER, 1997U)));
        CHECK_FALSE(date_time_range.IsValid());
    }
}
