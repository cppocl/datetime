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
    Time time3(24U, 60U, 60U, 1000U);

    CHECK_EQUAL(time1.GetMilliseconds(), 1U);
    CHECK_EQUAL(time1.GetSeconds(), 2U);
    CHECK_EQUAL(time1.GetMinutes(), 3U);
    CHECK_EQUAL(time1.GetHours(), 4U);

    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 59U);
    CHECK_EQUAL(time2.GetMinutes(), 58U);
    CHECK_EQUAL(time2.GetHours(), 23U);

    CHECK_EQUAL(time3.GetMilliseconds(), 999U);
    CHECK_EQUAL(time3.GetSeconds(), 59U);
    CHECK_EQUAL(time3.GetMinutes(), 59U);
    CHECK_EQUAL(time3.GetHours(), 23U);
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

TEST_CONST_MEMBER_FUNCTION(Time, plus_equal_operator, uint32_t)
{
    TEST_OVERRIDE_FUNCTION_NAME("operator +=");
    typedef Time::diff_type diff_type;

    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).operator+=(0U), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).operator+=(1U), Time(0U, 0U, 0U, 1U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).operator+=(1U), Time(0U, 0U, 0U, 2U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).operator+=(2U), Time(0U, 0U, 0U, 3U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 2U).operator+=(1U), Time(0U, 0U, 0U, 3U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 999U).operator+=(1U), Time(0U, 0U, 1U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).operator+=(1U), Time(0U, 0U, 1U, 1U));
    CHECK_EQUAL(Time(0U, 0U, 59U, 999U).operator+=(1U), Time(0U, 1U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).operator+=(1U), Time(0U, 1U, 0U, 1U));
    CHECK_EQUAL(Time(0U, 59U, 59U, 999U).operator+=(1U), Time(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, minus_equal_operator, uint32_t)
{
    TEST_OVERRIDE_FUNCTION_NAME("operator -=");
    typedef Time::diff_type diff_type;

    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).operator-=(0U), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).operator-=(1U), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).operator-=(1U), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).operator-=(2U), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 2U).operator-=(1U), Time(0U, 0U, 0U, 1U));
    CHECK_EQUAL(Time(0U, 0U, 0U, 999U).operator-=(999U), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).operator-=(1U), Time(0U, 0U, 0U, 999U));
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).operator-=(1U), Time(0U, 0U, 59U, 999U));
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U).operator-=(1U), Time(0U, 59U, 59U, 999U));
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).operator-=(Time::MILLISECONDS_PER_SECOND - 1U), Time(0U, 0U, 0U, 1U));
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).operator-=(Time::MILLISECONDS_PER_SECOND), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).operator-=(Time::MILLISECONDS_PER_MINUTE - 1U), Time(0U, 0U, 0U, 1U));
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).operator-=(Time::MILLISECONDS_PER_MINUTE), Time(0U, 0U, 0U, 0U));
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U).operator-=(Time::MILLISECONDS_PER_HOUR - 1U), Time(0U, 0U, 0U, 1U));
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U).operator-=(Time::MILLISECONDS_PER_HOUR), Time(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, minus_operator, Time_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator -", "Time const&");
    typedef Time::diff_type diff_type;

    CHECK_EQUAL(Time(0U, 0U, 0U, 0U) - Time(0U, 0U, 0U, 0U), 0);
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U) - Time(0U, 0U, 0U, 0U), 1);
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U) - Time(0U, 0U, 0U, 1U), -1);
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U) - Time(0U, 0U, 0U, 0U), static_cast<diff_type>(Time::MILLISECONDS_PER_SECOND));
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U) - Time(0U, 0U, 1U, 0U), -static_cast<diff_type>(Time::MILLISECONDS_PER_SECOND));
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U) - Time(0U, 0U, 0U, 0U), static_cast<diff_type>(Time::MILLISECONDS_PER_MINUTE));
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U) - Time(0U, 1U, 0U, 0U), -static_cast<diff_type>(Time::MILLISECONDS_PER_MINUTE));
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U) - Time(0U, 0U, 0U, 0U), static_cast<diff_type>(Time::MILLISECONDS_PER_HOUR));
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U) - Time(1U, 0U, 0U, 0U), -static_cast<diff_type>(Time::MILLISECONDS_PER_HOUR));
}

TEST_MEMBER_FUNCTION(Time, SplitMilliseconds, uint32_t_ref_uint32_t_ref_uint32_t_ref_uint32_t_ref)
{
    TEST_OVERRIDE_ARGS("uint32_t&, uint32_t&, uint32_t&, uint32_t&");

    uint32_t hours = 0U;
    uint32_t minutes = 0U;
    uint32_t seconds = 0U;
    uint32_t milliseconds = 0U;
    Time::SplitMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(hours, 0U);
    CHECK_EQUAL(minutes, 0U);
    CHECK_EQUAL(seconds, 0U);
    CHECK_EQUAL(milliseconds, 0U);

    hours = 0U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = 999U;
    Time::SplitMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(hours, 0U);
    CHECK_EQUAL(minutes, 0U);
    CHECK_EQUAL(seconds, 0U);
    CHECK_EQUAL(milliseconds, 999U);

    hours = 0U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = Time::MILLISECONDS_PER_SECOND;
    Time::SplitMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(hours, 0U);
    CHECK_EQUAL(minutes, 0U);
    CHECK_EQUAL(seconds, 1U);
    CHECK_EQUAL(milliseconds, 0U);

    hours = 0U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = Time::MILLISECONDS_PER_MINUTE;
    Time::SplitMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(hours, 0U);
    CHECK_EQUAL(minutes, 1U);
    CHECK_EQUAL(seconds, 0U);
    CHECK_EQUAL(milliseconds, 0U);

    hours = 0U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = Time::MILLISECONDS_PER_HOUR;
    Time::SplitMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(hours, 1U);
    CHECK_EQUAL(minutes, 0U);
    CHECK_EQUAL(seconds, 0U);
    CHECK_EQUAL(milliseconds, 0U);

    hours = 0U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = Time::MILLISECONDS_PER_HOUR + Time::MILLISECONDS_PER_MINUTE + Time::MILLISECONDS_PER_SECOND + 2U;
    Time::SplitMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(hours, 1U);
    CHECK_EQUAL(minutes, 1U);
    CHECK_EQUAL(seconds, 1U);
    CHECK_EQUAL(milliseconds, 2U);
}

TEST_MEMBER_FUNCTION(Time, ToMilliseconds, uint32_t_uint32_t_uint32_t_uint32_t)
{
    TEST_OVERRIDE_ARGS("uint32_t, uint32_t, uint32_t, uint32_t");

    uint32_t hours = 0U;
    uint32_t minutes = 0U;
    uint32_t seconds = 0U;
    uint32_t milliseconds = 0U;
    uint32_t ms = Time::ToMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(ms, 0U);

    hours = 0U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = 1U;
    ms = Time::ToMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(ms, 1U);

    hours = 0U;
    minutes = 0U;
    seconds = 1U;
    milliseconds = 0U;
    ms = Time::ToMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(ms, Time::MILLISECONDS_PER_SECOND);

    hours = 0U;
    minutes = 1U;
    seconds = 0U;
    milliseconds = 0U;
    ms = Time::ToMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(ms, Time::MILLISECONDS_PER_MINUTE);

    hours = 1U;
    minutes = 0U;
    seconds = 0U;
    milliseconds = 0U;
    ms = Time::ToMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(ms, Time::MILLISECONDS_PER_HOUR);

    hours = 1U;
    minutes = 1U;
    seconds = 1U;
    milliseconds = 2U;
    ms = Time::ToMilliseconds(hours, minutes, seconds, milliseconds);
    CHECK_EQUAL(ms, Time::MILLISECONDS_PER_HOUR + Time::MILLISECONDS_PER_MINUTE + Time::MILLISECONDS_PER_SECOND + 2U);
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

    time.SetMilliseconds(1000U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
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

    time.SetSeconds(60U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
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

    time.SetMinutes(60U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
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

    time.SetHours(24U);
    CHECK_EQUAL(time.GetHours(), 23U);
}

TEST_CONST_MEMBER_FUNCTION(Time, GetAsMilliseconds, NA)
{
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).GetAsMilliseconds(), 0U);
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).GetAsMilliseconds(), 1U);
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).GetAsMilliseconds(), Time::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).GetAsMilliseconds(), Time::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U).GetAsMilliseconds(), Time::MILLISECONDS_PER_HOUR);

    CHECK_EQUAL(Time(1U, 1U, 1U, 2U).GetAsMilliseconds(), Time::MILLISECONDS_PER_HOUR +
                                                          Time::MILLISECONDS_PER_MINUTE +
                                                          Time::MILLISECONDS_PER_SECOND + 2U);

    CHECK_EQUAL(Time(23U, 59U, 59U, 999U).GetAsMilliseconds(), (Time::MILLISECONDS_PER_HOUR * 23U) +
                                                               (Time::MILLISECONDS_PER_MINUTE * 59U) +
                                                               (Time::MILLISECONDS_PER_SECOND * 59U) + 999U);
}

TEST_MEMBER_FUNCTION(Time, SetFromMilliseconds, uint32_t)
{
    Time time;

    time.SetFromMilliseconds(1U);
    CHECK_EQUAL(time.GetMilliseconds(), 1U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetFromMilliseconds(Time::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 1U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetFromMilliseconds(Time::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 1U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetFromMilliseconds(Time::MILLISECONDS_PER_HOUR);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 1U);
}

TEST_CONST_MEMBER_FUNCTION(Time, GetDifference, Time_const_ref)
{
    TEST_OVERRIDE_ARGS("Time const&");

    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).GetDifference(Time(0U, 0U, 0U, 0U)), 0U);
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).GetDifference(Time(0U, 0U, 0U, 0U)), 1U);
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).GetDifference(Time(0U, 0U, 0U, 1U)), 1U);
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).GetDifference(Time(0U, 0U, 0U, 0U)), Time::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).GetDifference(Time(0U, 0U, 1U, 0U)), Time::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).GetDifference(Time(0U, 0U, 0U, 0U)), Time::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).GetDifference(Time(0U, 1U, 0U, 0U)), Time::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U).GetDifference(Time(0U, 0U, 0U, 0U)), Time::MILLISECONDS_PER_HOUR);
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).GetDifference(Time(1U, 0U, 0U, 0U)), Time::MILLISECONDS_PER_HOUR);
}

TEST_MEMBER_FUNCTION(Time, AddMilliseconds, uint32_t)
{
    Time time;

    time.AddMilliseconds(1U);
    CHECK_EQUAL(time.GetMilliseconds(), 1U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.AddMilliseconds(1U);
    CHECK_EQUAL(time.GetMilliseconds(), 2U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.AddMilliseconds(998U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 1U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.AddMilliseconds(1000U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 2U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.AddMilliseconds(58000U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 1U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.AddMilliseconds(Time::MILLISECONDS_PER_MINUTE * 59U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 1U);

    time.AddMilliseconds(Time::MILLISECONDS_PER_HOUR * 22U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.AddMilliseconds(Time::MILLISECONDS_PER_HOUR * 2U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, AddMilliseconds, uint32_t_uint32_t_ref)
{
    TEST_OVERRIDE_ARGS("uint32_t, uint32_t&");

    Time time;
    Time::size_type overflow = 0U;

    time.AddMilliseconds(1U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 1U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 0U, 1U);
    time.AddMilliseconds(1U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 2U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 0U, 2U);
    time.AddMilliseconds(998U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 1U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 1U, 0U);
    time.AddMilliseconds(1000U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 2U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 2U, 0U);
    time.AddMilliseconds(58000U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 1U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 1U, 0U, 0U);
    time.AddMilliseconds(Time::MILLISECONDS_PER_MINUTE * 59U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 1U);

    time.SetTime(1U, 0U, 0U, 0U);
    time.AddMilliseconds(Time::MILLISECONDS_PER_HOUR * 22U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 998U);
    time.AddMilliseconds(1U, overflow);
    CHECK_EQUAL(overflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 998U);
    time.AddMilliseconds(2U, overflow);
    CHECK_EQUAL(overflow, 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 0U, 0U, 0U);
    time.AddMilliseconds(Time::MILLISECONDS_PER_HOUR * 2U, overflow);
    CHECK_EQUAL(overflow, Time::MILLISECONDS_PER_HOUR + 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, SubtractMilliseconds, uint32_t)
{
    Time time(23U, 59U, 59U, 999U);

    time.SubtractMilliseconds(1U);
    CHECK_EQUAL(time.GetMilliseconds(), 998U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 998U);
    time.SubtractMilliseconds(998U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 0U);
    time.SubtractMilliseconds(1U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 58U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 58U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_SECOND * 59U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 58U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 58U, 59U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_MINUTE * 59U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 22U);

    time.SetTime(22U, 59U, 59U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_HOUR * 22U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 59U, 59U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_HOUR * 2U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);
}

TEST_MEMBER_FUNCTION(Time, SubtractMilliseconds, uint32_t_uint32_t_ref)
{
    TEST_OVERRIDE_ARGS("uint32_t, uint32_t&");

    Time time(23U, 59U, 59U, 999U);
    Time::size_type underflow = 0U;

    time.SubtractMilliseconds(1U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 998U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 998U);
    time.SubtractMilliseconds(998U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 0U);
    time.SubtractMilliseconds(1U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 58U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 58U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_SECOND * 59U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 58U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 58U, 59U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_MINUTE * 59U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 22U);

    time.SetTime(22U, 59U, 59U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_HOUR * 22U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 0U, 1U);
    time.SubtractMilliseconds(1U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 0U, 1U);
    time.SubtractMilliseconds(2U, underflow);
    CHECK_EQUAL(underflow, 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 59U, 59U, 999U);
    time.SubtractMilliseconds(Time::MILLISECONDS_PER_HOUR * 2U, underflow);
    CHECK_EQUAL(underflow, Time::MILLISECONDS_PER_HOUR + 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);
}

TEST_MEMBER_FUNCTION(Time, GetTime, NA)
{
    Time time1(0U, 0U, 0U, 0U);
    Time time2(1U, 2U, 3U, 4U);
    Time time3(23U, 59U, 59U, 999U);

    CHECK_EQUAL(time1.GetTime(), 0U);
    CHECK_EQUAL(time2.GetTime(), 0x01020c04u);
    CHECK_EQUAL(time3.GetTime(), 0x173befe7u);
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

    time.SetTime(0x01020c04u);
    CHECK_EQUAL(time.GetTime(), 0x01020c04u);
    CHECK_EQUAL(time.GetMilliseconds(), 4U);
    CHECK_EQUAL(time.GetSeconds(), 3U);
    CHECK_EQUAL(time.GetMinutes(), 2U);
    CHECK_EQUAL(time.GetHours(), 1U);

    time.SetTime(0x173befe7u);
    CHECK_EQUAL(time.GetTime(), 0x173befe7u);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, SetTime, Time_const_ref)
{
    TEST_OVERRIDE_ARGS("Time const&");

    Time time;
    Time time_default;
    Time time2(1U, 2U, 3U, 4U);

    time.SetTime(time_default);
    CHECK_EQUAL(time.GetTime(), 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(time2);
    CHECK_EQUAL(time.GetMilliseconds(), 4U);
    CHECK_EQUAL(time.GetSeconds(), 3U);
    CHECK_EQUAL(time.GetMinutes(), 2U);
    CHECK_EQUAL(time.GetHours(), 1U);
}

TEST_MEMBER_FUNCTION(Time, SetTime, hour_type_minute_type_second_type_millisecond_type)
{
    TEST_OVERRIDE_ARGS("hour_type, minute_type, second_type, millisecond_type");

    Time time;

    time.SetTime(1U, 2U, 3U, 4U);
    CHECK_EQUAL(time.GetMilliseconds(), 4U);
    CHECK_EQUAL(time.GetSeconds(), 3U);
    CHECK_EQUAL(time.GetMinutes(), 2U);
    CHECK_EQUAL(time.GetHours(), 1U);

    time.SetTime(23U, 59U, 59U, 999U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(0U, 0U, 0U, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(24U, 60U, 60U, 1000U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);
}

TEST_CONST_MEMBER_FUNCTION(Time, Compare, Time_const_ref)
{
    TEST_OVERRIDE_ARGS("Time const&");

    CHECK_EQUAL(Time().Compare(Time()), 0);
    CHECK_EQUAL(Time(0U, 0U, 0U, 0U).Compare(Time(0U, 0U, 0U, 0U)), 0);
    CHECK_EQUAL(Time(1U, 0U, 0U, 0U).Compare(Time(2U, 0U, 0U, 0U)), -1);
    CHECK_EQUAL(Time(0U, 1U, 0U, 0U).Compare(Time(0U, 2U, 0U, 0U)), -1);
    CHECK_EQUAL(Time(0U, 0U, 1U, 0U).Compare(Time(0U, 0U, 2U, 0U)), -1);
    CHECK_EQUAL(Time(0U, 0U, 0U, 1U).Compare(Time(0U, 0U, 0U, 2U)), -1);
    CHECK_EQUAL(Time(2U, 0U, 0U, 0U).Compare(Time(1U, 0U, 0U, 0U)), 1);
    CHECK_EQUAL(Time(0U, 2U, 0U, 0U).Compare(Time(0U, 1U, 0U, 0U)), 1);
    CHECK_EQUAL(Time(0U, 0U, 2U, 0U).Compare(Time(0U, 0U, 1U, 0U)), 1);
    CHECK_EQUAL(Time(0U, 0U, 0U, 2U).Compare(Time(0U, 0U, 0U, 1U)), 1);
}
