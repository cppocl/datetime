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
#include "../TimeAlgorithms.hpp"

using ocl::TimeAlgorithms;

static bool Equals(double value, double compare, double tolerance = 0.00001)
{
    return value >= compare - tolerance && value <= compare + tolerance;
}

TEST_MEMBER_FUNCTION(TimeAlgorithms, CalculateTotalCount, clock_t_clock_t_uint32_t)
{
    TEST_OVERRIDE_ARGS("clock_t, clock_t, uint32_t");

    // If there is no sample, then test that the initial count is 1.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 0U, 0U), 1U);

    // Test that when a current sample count did not produce a time,
    // the returned count will be the count sample * total duration.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 0U, 1U), 1000U);

    // Check that when no duration is requested then no count can be deduced.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(0U, 100U, 1U), 0U);

    // Test that when a sample count of 1 takes 100ms, then a return count of 10 would
    // be expected when the total duration was 1000ms.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 100U, 1U), 10U);
}

TEST_MEMBER_FUNCTION(TimeAlgorithms, CalculateTotalCount, clock_t_clock_t_clock_t_uint32_t)
{
    TEST_OVERRIDE_ARGS("clock_t, clock_t, clock_t, uint32_t");

    // If there is no sample, then test that the initial count is 1.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 0U, 0U, 0U), 1U);

    // Test that when a current sample count did not produce a time,
    // the returned count will be the count sample * total duration.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 0U, 0U, 1U), 1000U);

    // Check that when no duration is requested then no count can be deduced.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(0U, 0U, 100U, 1U), 0U);

    // Test that when a sample count of 1 takes 100ms, then a return count of 10 would
    // be expected when the total duration was 1000ms.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 0U, 100U, 1U), 10U);

    // Test that when a sample count of 1 takes 100ms, then a return count of 5 would
    // be expected when the total duration was 1000ms, and we are already half way through.
    CHECK_EQUAL(TimeAlgorithms::CalculateTotalCount(1000U, 500U, 100U, 1U), 5U);
}

TEST_MEMBER_FUNCTION(TimeAlgorithms, CalculateCallTimeInSeconds, uint32_t_clock_t)
{
    TEST_OVERRIDE_ARGS("uint32_t, clock_t");

    double time_in_seconds = TimeAlgorithms::CalculateCallTimeInSeconds(1U, 1U);
    CHECK_TRUE(Equals(time_in_seconds, 0.001));

    time_in_seconds = TimeAlgorithms::CalculateCallTimeInSeconds(1U, 1000U);
    CHECK_TRUE(Equals(time_in_seconds, 1.0));
}

TEST_MEMBER_FUNCTION(TimeAlgorithms, CalculateCallTimeInMilliseconds, uint32_t_clock_t)
{
    TEST_OVERRIDE_ARGS("uint32_t, clock_t");

    double time_in_milliseconds = TimeAlgorithms::CalculateCallTimeInMilliseconds(1U, 1U);
    CHECK_TRUE(Equals(time_in_milliseconds, 1.0));

    time_in_milliseconds = TimeAlgorithms::CalculateCallTimeInMilliseconds(1U, 1000U);
    CHECK_TRUE(Equals(time_in_milliseconds, 1000.0));
}
