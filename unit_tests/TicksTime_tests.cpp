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
#include "../TicksTime.hpp"
#include <ctime>

using ocl::TicksTime;

typedef TicksTime<signed long long> ticks_time;

TEST_MEMBER_FUNCTION(TicksTime, SecondsToTicks, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::SecondsToTicks(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::SecondsToTicks(1L, 1000L), 1000LL);
    CHECK_EQUAL(ticks_time::SecondsToTicks(10L, 1000L), 10000LL);
}

TEST_MEMBER_FUNCTION(TicksTime, MillisecondsToTicks, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::MillisecondsToTicks(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::MillisecondsToTicks(1L, 1000L), 1LL);
    CHECK_EQUAL(ticks_time::MillisecondsToTicks(10L, 1000L), 10LL);
    CHECK_EQUAL(ticks_time::MillisecondsToTicks(100L, 1000L), 100LL);
    CHECK_EQUAL(ticks_time::MillisecondsToTicks(1000L, 1000L), 1000LL);
    CHECK_EQUAL(ticks_time::MillisecondsToTicks(10000L, 1000L), 10000LL);
}

TEST_MEMBER_FUNCTION(TicksTime, MicrosecondsToTicks, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(1L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(999L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(1000L, 1000L), 1LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(10000L, 1000L), 10LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(100000L, 1000L), 100LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(1000000L, 1000L), 1000LL);
    CHECK_EQUAL(ticks_time::MicrosecondsToTicks(10000000L, 1000L), 10000LL);
}

TEST_MEMBER_FUNCTION(TicksTime, NanosecondsToTicks, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::NanosecondsToTicks(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(1L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(10L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(100L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(1000L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(10000L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(100000L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(999999L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(1000000L, 1000L), 1LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(10000000L, 1000L), 10LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(100000000L, 1000L), 100LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(1000000000L, 1000L), 1000LL);
    CHECK_EQUAL(ticks_time::NanosecondsToTicks(2000000000L, 1000L), 2000LL);
}

TEST_MEMBER_FUNCTION(TicksTime, TicksToSeconds, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::TicksToSeconds(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToSeconds(10L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToSeconds(100L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToSeconds(999L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToSeconds(1000L, 1000L), 1LL);
    CHECK_EQUAL(ticks_time::TicksToSeconds(10000L, 1000L), 10LL);
}

TEST_MEMBER_FUNCTION(TicksTime, TicksToMilliseconds, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::TicksToMilliseconds(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToMilliseconds(1L, 1000L), 1LL);
    CHECK_EQUAL(ticks_time::TicksToMilliseconds(10L, 1000L), 10LL);
    CHECK_EQUAL(ticks_time::TicksToMilliseconds(100L, 1000L), 100LL);
    CHECK_EQUAL(ticks_time::TicksToMilliseconds(1000L, 1000L), 1000LL);
    CHECK_EQUAL(ticks_time::TicksToMilliseconds(10000L, 1000L), 10000LL);
}

TEST_MEMBER_FUNCTION(TicksTime, TicksToMicroseconds, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::TicksToMicroseconds(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToMicroseconds(1L, 1000L), 1000LL);
    CHECK_EQUAL(ticks_time::TicksToMicroseconds(10L, 1000L), 10000LL);
}

TEST_MEMBER_FUNCTION(TicksTime, TicksToNanoseconds, clock_t_const_clock_t_const)
{
    TEST_OVERRIDE_ARGS("clock_t const, clock_t const");

    CHECK_EQUAL(ticks_time::TicksToNanoseconds(0L, 1000L), 0LL);
    CHECK_EQUAL(ticks_time::TicksToNanoseconds(1L, 1000L), 1000000LL);
    CHECK_EQUAL(ticks_time::TicksToNanoseconds(10L, 1000L), 10000000LL);
}
