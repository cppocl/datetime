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
#include "../Time.hpp"

using ocl::Time;

TEST_MEMBER_FUNCTION(Time, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("Time");

    Time time;

    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);
}

TEST_MEMBER_FUNCTION(Time, constructor, hour_type_minute_type_second_type_millisecond_type)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("Time", "hour_type, minute_type, second_type, millisecond_type");

    Time time1(4U, 3U, 2U, 1U);
    Time time2(23U, 58U, 59U, 999U);

    CHECK_EQUAL(time1.GetMilliseconds(), 1U);
    CHECK_EQUAL(time1.GetSeconds(), 2U);
    CHECK_EQUAL(time1.GetMinutes(), 3U);
    CHECK_EQUAL(time1.GetHours(), 4U);

    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 59U);
    CHECK_EQUAL(time2.GetMinutes(), 58U);
    CHECK_EQUAL(time2.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, constructor, Time_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("Time", "Time const&");

    Time time1;
    Time time2(time1);

    CHECK_EQUAL(time2.GetMilliseconds(), 0U);
    CHECK_EQUAL(time2.GetSeconds(), 0U);
    CHECK_EQUAL(time2.GetMinutes(), 0U);
    CHECK_EQUAL(time2.GetHours(), 0U);

    time1.SetMilliseconds(1U);
    time1.SetSeconds(2U);
    time1.SetMinutes(3U);
    time1.SetHours(4U);
    Time time3(time1);

    CHECK_EQUAL(time3.GetMilliseconds(), 1U);
    CHECK_EQUAL(time3.GetSeconds(), 2U);
    CHECK_EQUAL(time3.GetMinutes(), 3U);
    CHECK_EQUAL(time3.GetHours(), 4U);

    time1.SetMilliseconds(999U);
    time1.SetSeconds(59U);
    time1.SetMinutes(58U);
    time1.SetHours(23U);
    Time time4(time1);

    CHECK_EQUAL(time4.GetMilliseconds(), 999U);
    CHECK_EQUAL(time4.GetSeconds(), 59U);
    CHECK_EQUAL(time4.GetMinutes(), 58U);
    CHECK_EQUAL(time4.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, assignment_operator, Time_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "Time const&");

    Time time1;
    Time time2;

    time2 = time1;
    CHECK_EQUAL(time2.GetMilliseconds(), 0U);
    CHECK_EQUAL(time2.GetSeconds(), 0U);
    CHECK_EQUAL(time2.GetMinutes(), 0U);
    CHECK_EQUAL(time2.GetHours(), 0U);

    time2 = Time(01U, 02U, 03U, 04U);
    CHECK_EQUAL(time2.GetMilliseconds(), 4U);
    CHECK_EQUAL(time2.GetSeconds(), 3U);
    CHECK_EQUAL(time2.GetMinutes(), 2U);
    CHECK_EQUAL(time2.GetHours(), 1U);

    time2 = Time(23U, 59U, 58U, 999U);
    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 58U);
    CHECK_EQUAL(time2.GetMinutes(), 59U);
    CHECK_EQUAL(time2.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, GetMilliseconds, NA)
{
    for (Time::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        Time time(0U, 1U, 2U, ms);
        CHECK_EQUAL(time.GetMilliseconds(), ms);
    }
}

TEST_MEMBER_FUNCTION(Time, SetMilliseconds, millisecond_type)
{
    Time time;
    for (Time::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        time.SetMilliseconds(ms);
        CHECK_EQUAL(time.GetMilliseconds(), ms);
    }
}

TEST_MEMBER_FUNCTION(Time, GetSeconds, NA)
{
    for (Time::second_type s = 0; s <= 59U; ++s)
    {
        Time time(0U, 1U, s, 3U);
        CHECK_EQUAL(time.GetSeconds(), s);
    }
}

TEST_MEMBER_FUNCTION(Time, SetSeconds, second_type)
{
    Time time;
    for (Time::second_type s = 0; s <= 59U; ++s)
    {
        time.SetSeconds(s);
        CHECK_EQUAL(time.GetSeconds(), s);
    }
}

TEST_MEMBER_FUNCTION(Time, GetMinutes, NA)
{
    for (Time::minute_type m = 0; m <= 59U; ++m)
    {
        Time time(0U, m, 2U, 3U);
        CHECK_EQUAL(time.GetMinutes(), m);
    }
}

TEST_MEMBER_FUNCTION(Time, SetMinutes, minute_type)
{
    Time time;
    for (Time::minute_type m = 0; m <= 59U; ++m)
    {
        time.SetMinutes(m);
        CHECK_EQUAL(time.GetMinutes(), m);
    }
}

TEST_MEMBER_FUNCTION(Time, GetHours, NA)
{
    for (Time::hour_type h = 0; h <= 23U; ++h)
    {
        Time time(h, 1U, 2U, 3U);
        CHECK_EQUAL(time.GetHours(), h);
    }
}

TEST_MEMBER_FUNCTION(Time, SetHours, hour_type)
{
    Time time;
    for (Time::hour_type h = 0; h <= 23U; ++h)
    {
        time.SetHours(h);
        CHECK_EQUAL(time.GetHours(), h);
    }
}

TEST_MEMBER_FUNCTION(Time, GetTime, NA)
{
    Time time1(0U, 0U, 0U, 0U);
    Time time2(1U, 2U, 3U, 4U);
    Time time3(23U, 59U, 59U, 999U);

    CHECK_EQUAL(time1.GetTime(), 0U);
    CHECK_EQUAL(time2.GetTime(), 0x01020304u);
    CHECK_EQUAL(time3.GetTime(), 0x173bfbe7u);
}

TEST_MEMBER_FUNCTION(Time, SetTime, uint32_t)
{
    Time time;

    time.SetTime(0U);
    CHECK_EQUAL(time.GetTime(), 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0x01020304u);
    CHECK_EQUAL(time.GetTime(), 0x01020304u);
    CHECK_EQUAL(time.GetMilliseconds(), 4U);
    CHECK_EQUAL(time.GetSeconds(), 3U);
    CHECK_EQUAL(time.GetMinutes(), 2U);
    CHECK_EQUAL(time.GetHours(), 1U);

    time.SetTime(0x173bfbe7u);
    CHECK_EQUAL(time.GetTime(), 0x173bfbe7u);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);
}
