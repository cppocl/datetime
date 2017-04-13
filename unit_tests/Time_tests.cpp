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
using ocl::TimeMs;
using ocl::TimeNs;

TEST_MEMBER_FUNCTION(Time, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("TimeMs");

    TimeMs time;

    CHECK_EQUAL(time.GetNanoseconds(), 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);
}

TEST_MEMBER_FUNCTION(Time, constructor_ns, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("TimeNs");

    TimeNs time;

    CHECK_EQUAL(time.GetNanoseconds(), 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);
}

TEST_MEMBER_FUNCTION(Time, constructor, hour_type_minute_type_second_type_millisecond_type)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("TimeMs", "hour_type, minute_type, second_type, millisecond_type");

    TimeMs time1(4U, 3U, 2U, 1U);
    TimeMs time2(23U, 58U, 59U, 999U);
    TimeMs time3(24U, 60U, 60U, 1000U);

    CHECK_EQUAL(time1.GetNanoseconds(), 1000000UL);
    CHECK_EQUAL(time1.GetMilliseconds(), 1U);
    CHECK_EQUAL(time1.GetSeconds(), 2U);
    CHECK_EQUAL(time1.GetMinutes(), 3U);
    CHECK_EQUAL(time1.GetHours(), 4U);

    CHECK_EQUAL(time2.GetNanoseconds(), 999000000UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 59U);
    CHECK_EQUAL(time2.GetMinutes(), 58U);
    CHECK_EQUAL(time2.GetHours(), 23U);

    CHECK_EQUAL(time3.GetNanoseconds(), 999000000UL);
    CHECK_EQUAL(time3.GetMilliseconds(), 999U);
    CHECK_EQUAL(time3.GetSeconds(), 59U);
    CHECK_EQUAL(time3.GetMinutes(), 59U);
    CHECK_EQUAL(time3.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, constructor, hour_type_minute_type_second_type_nanosecond_type)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("TimeNs", "hour_type, minute_type, second_type, nanosecond_type");

    TimeNs time1(4U, 3U, 2U, 1U);
    TimeNs time2(23U, 58U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    TimeNs time3(24U, 60U, 60U, TimeNs::NANOSECONDS_PER_SECOND);

    CHECK_EQUAL(time1.GetNanoseconds(), 1UL);
    CHECK_EQUAL(time1.GetMilliseconds(), 0U);
    CHECK_EQUAL(time1.GetSeconds(), 2U);
    CHECK_EQUAL(time1.GetMinutes(), 3U);
    CHECK_EQUAL(time1.GetHours(), 4U);

    CHECK_EQUAL(time2.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 59U);
    CHECK_EQUAL(time2.GetMinutes(), 58U);
    CHECK_EQUAL(time2.GetHours(), 23U);

    CHECK_EQUAL(time2.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time3.GetMilliseconds(), 999U);
    CHECK_EQUAL(time3.GetSeconds(), 59U);
    CHECK_EQUAL(time3.GetMinutes(), 59U);
    CHECK_EQUAL(time3.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, constructor, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("TimeMs", "TimeMs const&");

    TimeMs time1;
    TimeMs time2(time1);

    CHECK_EQUAL(time2.GetNanoseconds(), 0UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 0U);
    CHECK_EQUAL(time2.GetSeconds(), 0U);
    CHECK_EQUAL(time2.GetMinutes(), 0U);
    CHECK_EQUAL(time2.GetHours(), 0U);

    time1.SetMilliseconds(1U);
    time1.SetSeconds(2U);
    time1.SetMinutes(3U);
    time1.SetHours(4U);
    TimeMs time3(time1);

    CHECK_EQUAL(time3.GetNanoseconds(), 1000000UL);
    CHECK_EQUAL(time3.GetMilliseconds(), 1U);
    CHECK_EQUAL(time3.GetSeconds(), 2U);
    CHECK_EQUAL(time3.GetMinutes(), 3U);
    CHECK_EQUAL(time3.GetHours(), 4U);

    time1.SetMilliseconds(999U);
    time1.SetSeconds(59U);
    time1.SetMinutes(58U);
    time1.SetHours(23U);
    TimeMs time4(time1);

    CHECK_EQUAL(time4.GetNanoseconds(), 999000000UL);
    CHECK_EQUAL(time4.GetMilliseconds(), 999U);
    CHECK_EQUAL(time4.GetSeconds(), 59U);
    CHECK_EQUAL(time4.GetMinutes(), 58U);
    CHECK_EQUAL(time4.GetHours(), 23U);

    time1.SetMilliseconds(1000U);
    time1.SetSeconds(60U);
    time1.SetMinutes(60U);
    time1.SetHours(24U);
    TimeMs time5(time1);

    CHECK_EQUAL(time5.GetNanoseconds(), 999000000UL);
    CHECK_EQUAL(time5.GetMilliseconds(), 999U);
    CHECK_EQUAL(time5.GetSeconds(), 59U);
    CHECK_EQUAL(time5.GetMinutes(), 59U);
    CHECK_EQUAL(time5.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, constructor, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("TimeNs", "TimeNs const&");

    TimeNs time1;
    TimeNs time2(time1);

    CHECK_EQUAL(time2.GetNanoseconds(), 0UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 0U);
    CHECK_EQUAL(time2.GetSeconds(), 0U);
    CHECK_EQUAL(time2.GetMinutes(), 0U);
    CHECK_EQUAL(time2.GetHours(), 0U);

    time1.SetNanoseconds(1U);
    time1.SetSeconds(2U);
    time1.SetMinutes(3U);
    time1.SetHours(4U);
    TimeNs time3(time1);

    CHECK_EQUAL(time3.GetNanoseconds(), 1UL);
    CHECK_EQUAL(time3.GetMilliseconds(), 0U);
    CHECK_EQUAL(time3.GetSeconds(), 2U);
    CHECK_EQUAL(time3.GetMinutes(), 3U);
    CHECK_EQUAL(time3.GetHours(), 4U);

    time1.SetNanoseconds(TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    time1.SetSeconds(59U);
    time1.SetMinutes(58U);
    time1.SetHours(23U);
    TimeNs time4(time1);

    CHECK_EQUAL(time4.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time4.GetMilliseconds(), 999U);
    CHECK_EQUAL(time4.GetSeconds(), 59U);
    CHECK_EQUAL(time4.GetMinutes(), 58U);
    CHECK_EQUAL(time4.GetHours(), 23U);

    time1.SetNanoseconds(TimeNs::NANOSECONDS_PER_SECOND);
    time1.SetSeconds(60U);
    time1.SetMinutes(60U);
    time1.SetHours(24U);
    TimeNs time5(time1);

    CHECK_EQUAL(time5.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time5.GetMilliseconds(), 999U);
    CHECK_EQUAL(time5.GetSeconds(), 59U);
    CHECK_EQUAL(time5.GetMinutes(), 59U);
    CHECK_EQUAL(time5.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, assignment_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "TimeMs const&");

    TimeMs time1;
    TimeMs time2;

    time2 = time1;
    CHECK_EQUAL(time2.GetNanoseconds(), 0U);
    CHECK_EQUAL(time2.GetMilliseconds(), 0U);
    CHECK_EQUAL(time2.GetSeconds(), 0U);
    CHECK_EQUAL(time2.GetMinutes(), 0U);
    CHECK_EQUAL(time2.GetHours(), 0U);

    time2 = TimeMs(01U, 02U, 03U, 04U);
    CHECK_EQUAL(time2.GetNanoseconds(), 4000000UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 4U);
    CHECK_EQUAL(time2.GetSeconds(), 3U);
    CHECK_EQUAL(time2.GetMinutes(), 2U);
    CHECK_EQUAL(time2.GetHours(), 1U);

    time2 = TimeMs(23U, 59U, 58U, 999U);
    CHECK_EQUAL(time2.GetNanoseconds(), 999000000UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 58U);
    CHECK_EQUAL(time2.GetMinutes(), 59U);
    CHECK_EQUAL(time2.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(Time, assignment_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "TimeNs const&");

    TimeNs time1;
    TimeNs time2;

    time2 = time1;
    CHECK_EQUAL(time2.GetNanoseconds(), 0UL);
    CHECK_EQUAL(time2.GetSeconds(), 0U);
    CHECK_EQUAL(time2.GetMinutes(), 0U);
    CHECK_EQUAL(time2.GetHours(), 0U);

    time2 = TimeNs(01U, 02U, 03U, 04U);
    CHECK_EQUAL(time2.GetNanoseconds(), 4U);
    CHECK_EQUAL(time2.GetMilliseconds(), 0U);
    CHECK_EQUAL(time2.GetSeconds(), 3U);
    CHECK_EQUAL(time2.GetMinutes(), 2U);
    CHECK_EQUAL(time2.GetHours(), 1U);

    time2 = TimeNs(23U, 59U, 58U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time2.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time2.GetMilliseconds(), 999U);
    CHECK_EQUAL(time2.GetSeconds(), 58U);
    CHECK_EQUAL(time2.GetMinutes(), 59U);
    CHECK_EQUAL(time2.GetHours(), 23U);
}

TEST_CONST_MEMBER_FUNCTION(Time, less_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <", "TimeMs const&");

    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) < TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 1U) < TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 2U) < TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) < TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 1U, 0U) < TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 2U, 0U) < TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) < TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 1U, 0U, 0U) < TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 2U, 0U, 0U) < TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) < TimeMs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(1U, 0U, 0U, 0U) < TimeMs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(2U, 0U, 0U, 0U) < TimeMs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, less_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <", "TimeNs const&");

    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) < TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 1U) < TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 2U) < TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) < TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 1U, 0U) < TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 2U, 0U) < TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) < TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 1U, 0U, 0U) < TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 2U, 0U, 0U) < TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) < TimeNs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(1U, 0U, 0U, 0U) < TimeNs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(2U, 0U, 0U, 0U) < TimeNs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, less_equal_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <=", "TimeMs const&");

    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) <= TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 1U) <= TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 2U) <= TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) <= TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 1U, 0U) <= TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 2U, 0U) <= TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) <= TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 1U, 0U, 0U) <= TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 2U, 0U, 0U) <= TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) <= TimeMs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(1U, 0U, 0U, 0U) <= TimeMs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(2U, 0U, 0U, 0U) <= TimeMs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, less_equal_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <=", "TimeNs const&");

    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) <= TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 1U) <= TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 2U) <= TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) <= TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 1U, 0U) <= TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 2U, 0U) <= TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) <= TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 1U, 0U, 0U) <= TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 2U, 0U, 0U) <= TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) <= TimeNs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(1U, 0U, 0U, 0U) <= TimeNs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(2U, 0U, 0U, 0U) <= TimeNs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, greater_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >", "TimeMs const&");

    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) > TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 1U) > TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 2U) > TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) > TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 1U, 0U) > TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 2U, 0U) > TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) > TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 1U, 0U, 0U) > TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 2U, 0U, 0U) > TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) > TimeMs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(1U, 0U, 0U, 0U) > TimeMs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(2U, 0U, 0U, 0U) > TimeMs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, greater_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >", "TimeNs const&");

    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) > TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 1U) > TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 2U) > TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) > TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 1U, 0U) > TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 2U, 0U) > TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) > TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 1U, 0U, 0U) > TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 2U, 0U, 0U) > TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) > TimeNs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(1U, 0U, 0U, 0U) > TimeNs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(2U, 0U, 0U, 0U) > TimeNs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, greater_equal_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >=", "TimeMs const&");

    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) >= TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 1U) >= TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 2U) >= TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) >= TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 1U, 0U) >= TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 2U, 0U) >= TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) >= TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 1U, 0U, 0U) >= TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 2U, 0U, 0U) >= TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) >= TimeMs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(1U, 0U, 0U, 0U) >= TimeMs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(2U, 0U, 0U, 0U) >= TimeMs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, greater_equal_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >=", "TimeNs const&");

    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) >= TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 1U) >= TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 2U) >= TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) >= TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 1U, 0U) >= TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 2U, 0U) >= TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) >= TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 1U, 0U, 0U) >= TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 2U, 0U, 0U) >= TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) >= TimeNs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(1U, 0U, 0U, 0U) >= TimeNs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(2U, 0U, 0U, 0U) >= TimeNs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, is_equal_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator ==", "TimeMs const&");

    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) == TimeMs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 1U) == TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 1U, 0U) == TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 1U, 0U, 0U) == TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(1U, 0U, 0U, 0U) == TimeMs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) == TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 1U) == TimeMs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) == TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 1U, 0U) == TimeMs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) == TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 1U, 0U, 0U) == TimeMs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) == TimeMs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(1U, 0U, 0U, 0U) == TimeMs(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, is_equal_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator ==", "TimeNs const&");

    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) == TimeNs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 1U) == TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 1U, 0U) == TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 1U, 0U, 0U) == TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(1U, 0U, 0U, 0U) == TimeNs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) == TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 1U) == TimeNs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) == TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 1U, 0U) == TimeNs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) == TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 1U, 0U, 0U) == TimeNs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) == TimeNs(1U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(1U, 0U, 0U, 0U) == TimeNs(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, is_not_equal_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator !=", "TimeMs const&");

    CHECK_FALSE(TimeMs(0U, 0U, 0U, 0U) != TimeMs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeMs(0U, 0U, 0U, 1U) != TimeMs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeMs(0U, 0U, 1U, 0U) != TimeMs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeMs(0U, 1U, 0U, 0U) != TimeMs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeMs(1U, 0U, 0U, 0U) != TimeMs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) != TimeMs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 1U) != TimeMs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) != TimeMs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 1U, 0U) != TimeMs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) != TimeMs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 1U, 0U, 0U) != TimeMs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(0U, 0U, 0U, 0U) != TimeMs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeMs(1U, 0U, 0U, 0U) != TimeMs(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, is_not_equal_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator !=", "TimeNs const&");

    CHECK_FALSE(TimeNs(0U, 0U, 0U, 0U) != TimeNs(0U, 0U, 0U, 0U));
    CHECK_FALSE(TimeNs(0U, 0U, 0U, 1U) != TimeNs(0U, 0U, 0U, 1U));
    CHECK_FALSE(TimeNs(0U, 0U, 1U, 0U) != TimeNs(0U, 0U, 1U, 0U));
    CHECK_FALSE(TimeNs(0U, 1U, 0U, 0U) != TimeNs(0U, 1U, 0U, 0U));
    CHECK_FALSE(TimeNs(1U, 0U, 0U, 0U) != TimeNs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) != TimeNs(0U, 0U, 0U, 1U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 1U) != TimeNs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) != TimeNs(0U, 0U, 1U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 1U, 0U) != TimeNs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) != TimeNs(0U, 1U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 1U, 0U, 0U) != TimeNs(0U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(0U, 0U, 0U, 0U) != TimeNs(1U, 0U, 0U, 0U));
    CHECK_TRUE(TimeNs(1U, 0U, 0U, 0U) != TimeNs(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, plus_equal_operator, size_type)
{
    TEST_OVERRIDE_FUNCTION_NAME("operator +=");

    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).operator+=(0U), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).operator+=(1U), TimeMs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U).operator+=(1U), TimeMs(0U, 0U, 0U, 2U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U).operator+=(2U), TimeMs(0U, 0U, 0U, 3U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 2U).operator+=(1U), TimeMs(0U, 0U, 0U, 3U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 999U).operator+=(1U), TimeMs(0U, 0U, 1U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U).operator+=(1U), TimeMs(0U, 0U, 1U, 1U));
    CHECK_EQUAL(TimeMs(0U, 0U, 59U, 999U).operator+=(1U), TimeMs(0U, 1U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U).operator+=(1U), TimeMs(0U, 1U, 0U, 1U));
    CHECK_EQUAL(TimeMs(0U, 59U, 59U, 999U).operator+=(1U), TimeMs(1U, 0U, 0U, 0U));

    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).operator+=(0U), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).operator+=(1U), TimeNs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U).operator+=(1U), TimeNs(0U, 0U, 0U, 2U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U).operator+=(2U), TimeNs(0U, 0U, 0U, 3U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 2U).operator+=(1U), TimeNs(0U, 0U, 0U, 3U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, TimeNs::NANOSECONDS_PER_SECOND - 1UL).operator+=(1U), TimeNs(0U, 0U, 1U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U).operator+=(1U), TimeNs(0U, 0U, 1U, 1U));
    CHECK_EQUAL(TimeNs(0U, 0U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL).operator+=(1U), TimeNs(0U, 1U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U).operator+=(1U), TimeNs(0U, 1U, 0U, 1U));
    CHECK_EQUAL(TimeNs(0U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL).operator+=(1U), TimeNs(1U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, minus_equal_operator, size_type)
{
    TEST_OVERRIDE_FUNCTION_NAME("operator -=");

    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).operator-=(0U), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).operator-=(1U), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U).operator-=(1U), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U).operator-=(2U), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 2U).operator-=(1U), TimeMs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 999U).operator-=(999U), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U).operator-=(1U), TimeMs(0U, 0U, 0U, 999U));
    CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U).operator-=(1U), TimeMs(0U, 0U, 59U, 999U));
    CHECK_EQUAL(TimeMs(1U, 0U, 0U, 0U).operator-=(1U), TimeMs(0U, 59U, 59U, 999U));
    CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U).operator-=(TimeMs::MILLISECONDS_PER_SECOND - 1U), TimeMs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U).operator-=(TimeMs::MILLISECONDS_PER_SECOND), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U).operator-=(TimeMs::MILLISECONDS_PER_MINUTE - 1U), TimeMs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U).operator-=(TimeMs::MILLISECONDS_PER_MINUTE), TimeMs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeMs(1U, 0U, 0U, 0U).operator-=(TimeMs::MILLISECONDS_PER_HOUR - 1U), TimeMs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeMs(1U, 0U, 0U, 0U).operator-=(TimeMs::MILLISECONDS_PER_HOUR), TimeMs(0U, 0U, 0U, 0U));

    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).operator-=(0U), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).operator-=(1U), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U).operator-=(1U), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U).operator-=(2U), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 2U).operator-=(1U), TimeNs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, TimeNs::NANOSECONDS_PER_SECOND - 1UL).operator-=(TimeNs::NANOSECONDS_PER_SECOND - 1UL), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U).operator-=(1U), TimeNs(0U, 0U, 0U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U).operator-=(1U), TimeNs(0U, 0U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(TimeNs(1U, 0U, 0U, 0U).operator-=(1U), TimeNs(0U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U).operator-=(TimeNs::NANOSECONDS_PER_SECOND - 1U), TimeNs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U).operator-=(TimeNs::NANOSECONDS_PER_SECOND), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U).operator-=(TimeNs::NANOSECONDS_PER_MINUTE - 1U), TimeNs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U).operator-=(TimeNs::NANOSECONDS_PER_MINUTE), TimeNs(0U, 0U, 0U, 0U));
    CHECK_EQUAL(TimeNs(1U, 0U, 0U, 0U).operator-=(TimeNs::NANOSECONDS_PER_HOUR - 1U), TimeNs(0U, 0U, 0U, 1U));
    CHECK_EQUAL(TimeNs(1U, 0U, 0U, 0U).operator-=(TimeNs::NANOSECONDS_PER_HOUR), TimeNs(0U, 0U, 0U, 0U));
}

TEST_CONST_MEMBER_FUNCTION(Time, minus_operator, Time_ms_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator -", "TimeMs const&");
    typedef TimeMs::diff_type diff_type;

    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U) - TimeMs(0U, 0U, 0U, 0U), 0);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U) - TimeMs(0U, 0U, 0U, 0U), 1);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U) - TimeMs(0U, 0U, 0U, 1U), -1);
    CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U) - TimeMs(0U, 0U, 0U, 0U), static_cast<diff_type>(TimeMs::MILLISECONDS_PER_SECOND));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U) - TimeMs(0U, 0U, 1U, 0U), -static_cast<diff_type>(TimeMs::MILLISECONDS_PER_SECOND));
    CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U) - TimeMs(0U, 0U, 0U, 0U), static_cast<diff_type>(TimeMs::MILLISECONDS_PER_MINUTE));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U) - TimeMs(0U, 1U, 0U, 0U), -static_cast<diff_type>(TimeMs::MILLISECONDS_PER_MINUTE));
    CHECK_EQUAL(TimeMs(1U, 0U, 0U, 0U) - TimeMs(0U, 0U, 0U, 0U), static_cast<diff_type>(TimeMs::MILLISECONDS_PER_HOUR));
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U) - TimeMs(1U, 0U, 0U, 0U), -static_cast<diff_type>(TimeMs::MILLISECONDS_PER_HOUR));
}

TEST_CONST_MEMBER_FUNCTION(Time, minus_operator, Time_ns_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator -", "TimeNs const&");
    typedef TimeNs::diff_type diff_type;

    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U) - TimeNs(0U, 0U, 0U, 0U), 0);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U) - TimeNs(0U, 0U, 0U, 0U), 1);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U) - TimeNs(0U, 0U, 0U, 1U), -1);
    CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U) - TimeNs(0U, 0U, 0U, 0U), static_cast<diff_type>(TimeNs::NANOSECONDS_PER_SECOND));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U) - TimeNs(0U, 0U, 1U, 0U), -static_cast<diff_type>(TimeNs::NANOSECONDS_PER_SECOND));
    CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U) - TimeNs(0U, 0U, 0U, 0U), static_cast<diff_type>(TimeNs::NANOSECONDS_PER_MINUTE));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U) - TimeNs(0U, 1U, 0U, 0U), -static_cast<diff_type>(TimeNs::NANOSECONDS_PER_MINUTE));
    CHECK_EQUAL(TimeNs(1U, 0U, 0U, 0U) - TimeNs(0U, 0U, 0U, 0U), static_cast<diff_type>(TimeNs::NANOSECONDS_PER_HOUR));
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U) - TimeNs(1U, 0U, 0U, 0U), -static_cast<diff_type>(TimeNs::NANOSECONDS_PER_HOUR));
}

TEST_MEMBER_FUNCTION(Time, Split, size_type_ref_size_type_ref_size_type_ref_size_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type&, size_type&, size_type&, size_type&");

    {
        TimeMs::size_type total_milliseconds = 0U;
        TimeMs::size_type hours = 0U;
        TimeMs::size_type minutes = 0U;
        TimeMs::size_type seconds = 0U;
        TimeMs::size_type milliseconds = 0U;
        TimeMs::Split(total_milliseconds, hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(milliseconds, 0U);

        hours = 1U;
        minutes = 1U;
        seconds = 1U;
        milliseconds = 0U;
        total_milliseconds = 999U;
        TimeMs::Split(total_milliseconds, hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(milliseconds, 999U);

        hours = 1U;
        minutes = 1U;
        seconds = 0U;
        milliseconds = 1U;
        total_milliseconds = TimeMs::MILLISECONDS_PER_SECOND;
        TimeMs::Split(total_milliseconds, hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 1U);
        CHECK_EQUAL(milliseconds, 0U);

        hours = 1U;
        minutes = 0U;
        seconds = 1U;
        milliseconds = 1U;
        total_milliseconds = TimeMs::MILLISECONDS_PER_MINUTE;
        TimeMs::Split(total_milliseconds, hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 1U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(milliseconds, 0U);

        hours = 0U;
        minutes = 1U;
        seconds = 1U;
        milliseconds = 1U;
        total_milliseconds = TimeMs::MILLISECONDS_PER_HOUR;
        TimeMs::Split(total_milliseconds, hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(hours, 1U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(milliseconds, 0U);

        hours = 0U;
        minutes = 0U;
        seconds = 0U;
        milliseconds = 0U;
        total_milliseconds = TimeMs::MILLISECONDS_PER_HOUR +
                             TimeMs::MILLISECONDS_PER_MINUTE +
                             TimeMs::MILLISECONDS_PER_SECOND + 2U;
        TimeMs::Split(total_milliseconds, hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(hours, 1U);
        CHECK_EQUAL(minutes, 1U);
        CHECK_EQUAL(seconds, 1U);
        CHECK_EQUAL(milliseconds, 2U);
    }

    {
        TimeNs::size_type total_nanoseconds = 0U;
        TimeNs::size_type hours = 0U;
        TimeNs::size_type minutes = 0U;
        TimeNs::size_type seconds = 0U;
        TimeNs::size_type nanoseconds = 0U;
        TimeNs::Split(total_nanoseconds, hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(nanoseconds, 0U);

        hours = 1U;
        minutes = 1U;
        seconds = 1U;
        nanoseconds = 0U;
        total_nanoseconds = TimeNs::NANOSECONDS_UPPER_BOUND;
        TimeNs::Split(total_nanoseconds, hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(nanoseconds, TimeNs::NANOSECONDS_UPPER_BOUND);

        hours = 1U;
        minutes = 1U;
        seconds = 0U;
        nanoseconds = 1U;
        total_nanoseconds = TimeNs::NANOSECONDS_PER_SECOND;
        TimeNs::Split(total_nanoseconds, hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 1U);
        CHECK_EQUAL(nanoseconds, 0U);

        hours = 1U;
        minutes = 0U;
        seconds = 1U;
        nanoseconds = 1U;
        total_nanoseconds = TimeNs::NANOSECONDS_PER_MINUTE;
        TimeNs::Split(total_nanoseconds, hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(hours, 0U);
        CHECK_EQUAL(minutes, 1U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(nanoseconds, 0U);

        hours = 0U;
        minutes = 1U;
        seconds = 1U;
        nanoseconds = 1U;
        total_nanoseconds = TimeNs::NANOSECONDS_PER_HOUR;
        TimeNs::Split(total_nanoseconds, hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(hours, 1U);
        CHECK_EQUAL(minutes, 0U);
        CHECK_EQUAL(seconds, 0U);
        CHECK_EQUAL(nanoseconds, 0U);

        hours = 0U;
        minutes = 0U;
        seconds = 0U;
        nanoseconds = 0U;
        total_nanoseconds = TimeNs::NANOSECONDS_PER_HOUR +
                            TimeNs::NANOSECONDS_PER_MINUTE +
                            TimeNs::NANOSECONDS_PER_SECOND + 2U;
        TimeNs::Split(total_nanoseconds, hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(hours, 1U);
        CHECK_EQUAL(minutes, 1U);
        CHECK_EQUAL(seconds, 1U);
        CHECK_EQUAL(nanoseconds, 2U);
    }
}

TEST_MEMBER_FUNCTION(Time, Merge, size_type_size_type_size_type_size_type)
{
    TEST_OVERRIDE_ARGS("size_type, size_type, size_type, size_type");

    {
        TimeMs::size_type hours = 0U;
        TimeMs::size_type minutes = 0U;
        TimeMs::size_type seconds = 0U;
        TimeMs::size_type milliseconds = 0U;
        TimeMs::size_type ms = TimeMs::Merge(hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(ms, 0U);

        hours = 0U;
        minutes = 0U;
        seconds = 0U;
        milliseconds = 1U;
        ms = TimeMs::Merge(hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(ms, 1U);

        hours = 0U;
        minutes = 0U;
        seconds = 1U;
        milliseconds = 0U;
        ms = TimeMs::Merge(hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(ms, TimeMs::MILLISECONDS_PER_SECOND);

        hours = 0U;
        minutes = 1U;
        seconds = 0U;
        milliseconds = 0U;
        ms = TimeMs::Merge(hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(ms, TimeMs::MILLISECONDS_PER_MINUTE);

        hours = 1U;
        minutes = 0U;
        seconds = 0U;
        milliseconds = 0U;
        ms = TimeMs::Merge(hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(ms, TimeMs::MILLISECONDS_PER_HOUR);

        hours = 1U;
        minutes = 1U;
        seconds = 1U;
        milliseconds = 2U;
        ms = TimeMs::Merge(hours, minutes, seconds, milliseconds);
        CHECK_EQUAL(ms, TimeMs::MILLISECONDS_PER_HOUR + TimeMs::MILLISECONDS_PER_MINUTE + TimeMs::MILLISECONDS_PER_SECOND + 2U);
    }

    {
        TimeNs::size_type hours = 0U;
        TimeNs::size_type minutes = 0U;
        TimeNs::size_type seconds = 0U;
        TimeNs::size_type nanoseconds = 0U;
        TimeNs::size_type ms = TimeNs::Merge(hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(ms, 0U);

        hours = 0U;
        minutes = 0U;
        seconds = 0U;
        nanoseconds = 1U;
        ms = TimeNs::Merge(hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(ms, 1U);

        hours = 0U;
        minutes = 0U;
        seconds = 1U;
        nanoseconds = 0U;
        ms = TimeNs::Merge(hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(ms, TimeNs::NANOSECONDS_PER_SECOND);

        hours = 0U;
        minutes = 1U;
        seconds = 0U;
        nanoseconds = 0U;
        ms = TimeNs::Merge(hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(ms, TimeNs::NANOSECONDS_PER_MINUTE);

        hours = 1U;
        minutes = 0U;
        seconds = 0U;
        nanoseconds = 0U;
        ms = TimeNs::Merge(hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(ms, TimeNs::NANOSECONDS_PER_HOUR);

        hours = 1U;
        minutes = 1U;
        seconds = 1U;
        nanoseconds = 2U;
        ms = TimeNs::Merge(hours, minutes, seconds, nanoseconds);
        CHECK_EQUAL(ms, TimeNs::NANOSECONDS_PER_HOUR + TimeNs::NANOSECONDS_PER_MINUTE + TimeNs::NANOSECONDS_PER_SECOND + 2U);
    }
}

TEST_MEMBER_FUNCTION(Time, GetMilliseconds, NA)
{
    for (TimeMs::millisecond_type ms = 0; ms < TimeMs::MILLISECONDS_PER_SECOND; ++ms)
    {
        TimeMs time_ms(0U, 1U, 2U, ms);
        TimeNs::nanosecond_type ns = TimeMs::NANOSECONDS_PER_MILLISECOND * ms;
        TimeNs time_ns(0U, 1U, 2U, ns);
        CHECK_EQUAL(time_ms.GetMilliseconds(), ms);
        CHECK_EQUAL(time_ns.GetMilliseconds(), ms);
    }
}

TEST_MEMBER_FUNCTION(Time, GetNanoseconds, NA)
{
    for (TimeNs::nanosecond_type ns = 0; ns < TimeNs::NANOSECONDS_PER_SECOND; ns += 1000000UL)
    {
        TimeMs::millisecond_type ms = static_cast<TimeMs::millisecond_type>(ns / TimeMs::NANOSECONDS_PER_MILLISECOND);
        TimeMs time_ms(0U, 1U, 2U, ms);
        TimeNs time_ns(0U, 1U, 2U, ns);
        CHECK_EQUAL(time_ms.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * ms);
        CHECK_EQUAL(time_ns.GetNanoseconds(), ns);
    }
}

TEST_MEMBER_FUNCTION(Time, SetMilliseconds, millisecond_type)
{
    TimeMs time_ms;
    TimeNs time_ns;
    for (TimeMs::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        time_ms.SetMilliseconds(ms);
        time_ns.SetMilliseconds(ms);
        CHECK_EQUAL(time_ms.GetMilliseconds(), ms);
        CHECK_EQUAL(time_ns.GetMilliseconds(), ms);
    }

    time_ms.SetMilliseconds(TimeMs::MILLISECONDS_PER_SECOND);
    time_ns.SetMilliseconds(TimeMs::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(time_ms.GetMilliseconds(), TimeMs::MILLISECONDS_UPPER_BOUND);
    CHECK_EQUAL(time_ns.GetMilliseconds(), TimeMs::MILLISECONDS_UPPER_BOUND);
}

TEST_MEMBER_FUNCTION(Time, GetSeconds, NA)
{
    for (TimeMs::second_type s = 0; s <= 59U; ++s)
    {
        TimeMs time_ms(0U, 1U, s, 3U);
        TimeNs time_ns(0U, 1U, s, 3U);
        CHECK_EQUAL(time_ms.GetSeconds(), s);
        CHECK_EQUAL(time_ns.GetSeconds(), s);
    }
}

TEST_MEMBER_FUNCTION(Time, SetSeconds, second_type)
{
    TimeMs time_ms;
    TimeNs time_ns;
    for (TimeMs::second_type s = 0; s <= 59U; ++s)
    {
        time_ms.SetSeconds(s);
        time_ns.SetSeconds(s);
        CHECK_EQUAL(time_ms.GetSeconds(), s);
        CHECK_EQUAL(time_ns.GetSeconds(), s);
    }

    time_ms.SetSeconds(60U);
    time_ns.SetSeconds(60U);
    CHECK_EQUAL(time_ms.GetSeconds(), 59U);
    CHECK_EQUAL(time_ns.GetSeconds(), 59U);
}

TEST_MEMBER_FUNCTION(Time, GetMinutes, NA)
{
    for (TimeMs::minute_type m = 0; m <= 59U; ++m)
    {
        TimeMs time_ms(0U, m, 2U, 3U);
        TimeNs time_ns(0U, m, 2U, 3U);
        CHECK_EQUAL(time_ms.GetMinutes(), m);
        CHECK_EQUAL(time_ns.GetMinutes(), m);
    }
}

TEST_MEMBER_FUNCTION(Time, SetMinutes, minute_type)
{
    TimeMs time_ms;
    TimeNs time_ns;
    for (TimeMs::minute_type m = 0; m <= 59U; ++m)
    {
        time_ms.SetMinutes(m);
        time_ns.SetMinutes(m);
        CHECK_EQUAL(time_ms.GetMinutes(), m);
        CHECK_EQUAL(time_ns.GetMinutes(), m);
    }

    time_ms.SetMinutes(60U);
    time_ns.SetMinutes(60U);
    CHECK_EQUAL(time_ms.GetMinutes(), 59U);
    CHECK_EQUAL(time_ns.GetMinutes(), 59U);
}

TEST_MEMBER_FUNCTION(Time, GetHours, NA)
{
    for (TimeMs::hour_type h = 0; h <= 23U; ++h)
    {
        TimeMs time_ms(h, 1U, 2U, 3U);
        TimeNs time_ns(h, 1U, 2U, 3U);
        CHECK_EQUAL(time_ms.GetHours(), h);
        CHECK_EQUAL(time_ns.GetHours(), h);
    }
}

TEST_MEMBER_FUNCTION(Time, SetHours, hour_type)
{
    TimeMs time_ms;
    TimeNs time_ns;
    for (TimeMs::hour_type h = 0; h <= 23U; ++h)
    {
        time_ms.SetHours(h);
        time_ns.SetHours(h);
        CHECK_EQUAL(time_ms.GetHours(), h);
        CHECK_EQUAL(time_ns.GetHours(), h);
    }

    time_ms.SetHours(24U);
    time_ns.SetHours(24U);
    CHECK_EQUAL(time_ms.GetHours(), 23U);
    CHECK_EQUAL(time_ns.GetHours(), 23U);
}

TEST_CONST_MEMBER_FUNCTION(Time, Transform, NA)
{
    {
        CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).Transform(), 0U);
        CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U).Transform(), 1U);
        CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U).Transform(), TimeMs::MILLISECONDS_PER_SECOND);
        CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U).Transform(), TimeMs::MILLISECONDS_PER_MINUTE);
        CHECK_EQUAL(TimeMs(1U, 0U, 0U, 0U).Transform(), TimeMs::MILLISECONDS_PER_HOUR);

        CHECK_EQUAL(TimeMs(1U, 1U, 1U, 2U).Transform(), TimeMs::MILLISECONDS_PER_HOUR +
                                                        TimeMs::MILLISECONDS_PER_MINUTE +
                                                        TimeMs::MILLISECONDS_PER_SECOND + 2U);

        CHECK_EQUAL(TimeMs(23U, 59U, 59U, 999U).Transform(), TimeNs::MILLISECONDS_PER_DAY - 1U);
    }

    {
        CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).Transform(), 0U);
        CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U).Transform(), 1U);
        CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U).Transform(), TimeNs::NANOSECONDS_PER_SECOND);
        CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U).Transform(), TimeNs::NANOSECONDS_PER_MINUTE);
        CHECK_EQUAL(TimeNs(1U, 0U, 0U, 0U).Transform(), TimeNs::NANOSECONDS_PER_HOUR);

        CHECK_EQUAL(TimeNs(1U, 1U, 1U, 2U).Transform(), TimeNs::NANOSECONDS_PER_HOUR +
                                                        TimeNs::NANOSECONDS_PER_MINUTE +
                                                        TimeNs::NANOSECONDS_PER_SECOND + 2U);

        CHECK_EQUAL(TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL).Transform(), TimeNs::NANOSECONDS_PER_DAY - 1UL);
    }
}

TEST_MEMBER_FUNCTION(Time, Transform, size_type)
{
    {
        TimeMs time;

        time.Transform(1U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), 1U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(TimeMs::MILLISECONDS_PER_SECOND);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 1U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(TimeMs::MILLISECONDS_PER_MINUTE);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 1U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(TimeMs::MILLISECONDS_PER_HOUR);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 1U);
    }

    {
        TimeNs time;

        time.Transform(1U);
        CHECK_EQUAL(time.GetNanoseconds(), 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(1000000UL);
        CHECK_EQUAL(time.GetNanoseconds(), 1000000UL);
        CHECK_EQUAL(time.GetMilliseconds(), 1U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(TimeMs::NANOSECONDS_PER_SECOND);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 1U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(TimeMs::NANOSECONDS_PER_MINUTE);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 1U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Transform(TimeMs::NANOSECONDS_PER_HOUR);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 1U);
    }
}

TEST_CONST_MEMBER_FUNCTION(Time, GetDifference, Time_ms_const_ref)
{
    TEST_OVERRIDE_ARGS("TimeMs const&");

    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).GetDifference(TimeMs(0U, 0U, 0U, 0U)), 0U);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).GetDifference(TimeMs(0U, 0U, 0U, 1U)), 1U);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).GetDifference(TimeMs(0U, 0U, 1U, 0U)), TimeMs::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).GetDifference(TimeMs(0U, 1U, 0U, 0U)), TimeMs::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).GetDifference(TimeMs(1U, 0U, 0U, 0U)), TimeMs::MILLISECONDS_PER_HOUR);

    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).GetDifference(TimeNs(0U, 0U, 0U, 0U)), 0U);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).GetDifference(TimeNs(0U, 0U, 0U, 1U)), 1U);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).GetDifference(TimeNs(0U, 0U, 1U, 0U)), TimeNs::NANOSECONDS_PER_SECOND);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).GetDifference(TimeNs(0U, 1U, 0U, 0U)), TimeNs::NANOSECONDS_PER_MINUTE);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).GetDifference(TimeNs(1U, 0U, 0U, 0U)), TimeNs::NANOSECONDS_PER_HOUR);
}

TEST_MEMBER_FUNCTION(Time, Add, size_type)
{
    // Test milliseconds.
    {
        TimeMs time;

        time.Add(1U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND);
        CHECK_EQUAL(time.GetMilliseconds(), 1U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(1U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * 2UL);
        CHECK_EQUAL(time.GetMilliseconds(), 2U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(998U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 1U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(1000U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 2U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(58000U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 1U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(TimeMs::MILLISECONDS_PER_MINUTE * 59U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 1U);

        time.Add(TimeMs::MILLISECONDS_PER_HOUR * 22U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.Add(TimeMs::MILLISECONDS_PER_HOUR * 2U);
        CHECK_EQUAL(time.GetNanoseconds(),
                    static_cast<TimeNs::size_type>(TimeNs::NANOSECONDS_PER_MILLISECOND) * (TimeNs::MILLISECONDS_PER_SECOND - 1UL));
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);
    }

    // Test Nanoseconds.
    {
        TimeNs time;

        time.Add(1U);
        CHECK_EQUAL(time.GetNanoseconds(), 1U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(1U);
        CHECK_EQUAL(time.GetNanoseconds(), 2U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(TimeNs::NANOSECONDS_PER_SECOND - 2UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 1U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(TimeNs::NANOSECONDS_PER_SECOND);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 2U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(TimeNs::NANOSECONDS_PER_MINUTE - (TimeNs::NANOSECONDS_PER_SECOND * 2UL));
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 1U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Add(TimeMs::NANOSECONDS_PER_MINUTE * 59UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 1U);

        time.Add(TimeMs::NANOSECONDS_PER_HOUR * 22UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.Add(TimeMs::NANOSECONDS_PER_HOUR * 2U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);
    }
}

TEST_MEMBER_FUNCTION(Time, Add, size_type_size_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type, size_type&");

    // Test milliseconds.
    {
        TimeMs time;
        TimeMs::size_type overflow = static_cast<TimeMs::size_type>(0xffffffffU);

        time.Add(1U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 1U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 0U, 1U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(1U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 2U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 0U, 2U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(998U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 1U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 1U, 0U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(1000U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 2U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 2U, 0U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(58000U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 1U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 1U, 0U, 0U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(TimeMs::MILLISECONDS_PER_MINUTE * 59U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 1U);

        time.SetTime(1U, 0U, 0U, 0U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(TimeMs::MILLISECONDS_PER_HOUR * 22U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, 998U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(1U, overflow);
        CHECK_EQUAL(overflow, 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 999U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, 998U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(2U, overflow);
        CHECK_EQUAL(overflow, 1U);
        CHECK_EQUAL(time.GetMilliseconds(), 999U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 0U, 0U, 0U);
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(TimeMs::MILLISECONDS_PER_HOUR * 2U, overflow);
        CHECK_EQUAL(overflow, TimeMs::MILLISECONDS_PER_HOUR + 1U);
        CHECK_EQUAL(time.GetMilliseconds(), 999U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetStart();
        overflow = static_cast<TimeMs::size_type>(0xffffffffU);
        time.Add(TimeMs::MILLISECONDS_PER_DAY, overflow);
        CHECK_EQUAL(overflow, 1U);
        CHECK_EQUAL(time.GetMilliseconds(), 999U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);
    }

    // Test nanoseconds.
    {
        TimeNs time;
        TimeNs::size_type overflow = static_cast<TimeNs::size_type>(0xffffffffU);

        time.Add(1U, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 0U, 1U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(1U, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 2UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 0U, 2U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_SECOND - 2UL, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 1U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 1U, 0U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_SECOND, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 2U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 0U, 2U, 0U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_MINUTE - (TimeNs::NANOSECONDS_PER_SECOND * 2UL), overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 1U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 1U, 0U, 0U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_MINUTE * 59U, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 1U);

        time.SetTime(1U, 0U, 0U, 0U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_HOUR * 22U, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 2UL);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(1UL, overflow);
        CHECK_EQUAL(overflow, 0UL);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 2UL);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(2U, overflow);
        CHECK_EQUAL(overflow, 1UL);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 0U, 0U, 0U);
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_HOUR * 2UL, overflow);
        CHECK_EQUAL(overflow, TimeNs::NANOSECONDS_PER_HOUR + 1UL);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetStart();
        overflow = static_cast<TimeNs::size_type>(0xffffffffU);
        time.Add(TimeNs::NANOSECONDS_PER_DAY, overflow);
        CHECK_EQUAL(overflow, 1UL);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);
    }
}

TEST_MEMBER_FUNCTION(Time, Subtract, size_type)
{
    // Test milliseconds.
    {
        TimeMs time(23U, 59U, 59U, TimeNs::MILLISECONDS_PER_SECOND - 1U);

        time.Subtract(1U);
        CHECK_EQUAL(time.GetNanoseconds(), (TimeNs::MILLISECONDS_PER_SECOND - 2U) * TimeNs::NANOSECONDS_PER_MILLISECOND);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 2U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, TimeNs::MILLISECONDS_PER_SECOND - 2U);
        time.Subtract(TimeNs::MILLISECONDS_PER_SECOND - 2U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, 0U);
        time.Subtract(1U);
        CHECK_EQUAL(time.GetNanoseconds(), (TimeNs::MILLISECONDS_PER_SECOND - 1U) * TimeNs::NANOSECONDS_PER_MILLISECOND);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 58U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 58U, TimeNs::MILLISECONDS_PER_SECOND - 1U);
        time.Subtract(TimeMs::MILLISECONDS_PER_SECOND * 59U);
        CHECK_EQUAL(time.GetNanoseconds(), (TimeNs::MILLISECONDS_PER_SECOND - 1U) * TimeNs::NANOSECONDS_PER_MILLISECOND);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 58U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 58U, 59U, TimeNs::MILLISECONDS_PER_SECOND - 1U);
        time.Subtract(TimeMs::MILLISECONDS_PER_MINUTE * 59U);
        CHECK_EQUAL(time.GetNanoseconds(), (TimeNs::MILLISECONDS_PER_SECOND - 1U) * TimeNs::NANOSECONDS_PER_MILLISECOND);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 22U);

        time.SetTime(22U, 59U, 59U, TimeNs::MILLISECONDS_PER_SECOND - 1U);
        time.Subtract(TimeMs::MILLISECONDS_PER_HOUR * 22U);
        CHECK_EQUAL(time.GetNanoseconds(), (TimeNs::MILLISECONDS_PER_SECOND - 1U) * TimeNs::NANOSECONDS_PER_MILLISECOND);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 59U, 59U, TimeNs::MILLISECONDS_PER_SECOND - 1U);
        time.Subtract(TimeMs::MILLISECONDS_PER_HOUR * 2U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);
    }

    // Test nanoseconds.
    {
        TimeNs time(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);

        time.Subtract(1U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 2UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 2UL);
        time.Subtract(TimeNs::NANOSECONDS_PER_SECOND - 2UL);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 59U, 0U);
        time.Subtract(1U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 58U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 59U, 58U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        time.Subtract(static_cast<TimeNs::size_type>(TimeMs::NANOSECONDS_PER_SECOND) * 59UL);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 58U);
        CHECK_EQUAL(time.GetHours(), 23U);

        time.SetTime(23U, 58U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        time.Subtract(TimeMs::NANOSECONDS_PER_MINUTE * 59U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 22U);

        time.SetTime(22U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        time.Subtract(TimeMs::NANOSECONDS_PER_HOUR * 22U);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.SetTime(0U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        time.Subtract(TimeMs::NANOSECONDS_PER_HOUR * 2U);
        CHECK_EQUAL(time.GetNanoseconds(), 0UL);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);
    }
}

TEST_MEMBER_FUNCTION(Time, Subtract, size_type_size_type_ref)
{
    TEST_OVERRIDE_ARGS("size_type, size_type&");

    TimeMs time(23U, 59U, 59U, 999U);
    TimeMs::size_type underflow = 0U;

    time.Subtract(1U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 998U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 998U);
    time.Subtract(998U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 59U, 0U);
    time.Subtract(1U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 58U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 59U, 58U, 999U);
    time.Subtract(TimeMs::MILLISECONDS_PER_SECOND * 59U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 58U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(23U, 58U, 59U, 999U);
    time.Subtract(TimeMs::MILLISECONDS_PER_MINUTE * 59U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 22U);

    time.SetTime(22U, 59U, 59U, 999U);
    time.Subtract(TimeMs::MILLISECONDS_PER_HOUR * 22U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 0U, 1U);
    time.Subtract(1U, underflow);
    CHECK_EQUAL(underflow, 0U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 0U, 0U, 1U);
    time.Subtract(2U, underflow);
    CHECK_EQUAL(underflow, 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(0U, 59U, 59U, 999U);
    time.Subtract(TimeMs::MILLISECONDS_PER_HOUR * 2U, underflow);
    CHECK_EQUAL(underflow, TimeMs::MILLISECONDS_PER_HOUR + 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);
}

// Macro for making testing of TimeNs easier.
#define HHMMSSNN2INT64(h, m, s, n) (static_cast<TimeNs::size_type>(n) | \
                                   (static_cast<TimeNs::size_type>(s) << 32UL) | \
                                   (static_cast<TimeNs::size_type>(m) << 40UL) | \
                                   (static_cast<TimeNs::size_type>(h) << 48UL))

TEST_MEMBER_FUNCTION(Time, Serialize, NA)
{
    // Test milliseconds.
    {
        TimeMs time1(0U, 0U, 0U, 0U);
        TimeMs time2(1U, 2U, 3U, 4U);
        TimeMs time3(23U, 59U, 59U, TimeMs::MILLISECONDS_PER_SECOND - 1UL);

        CHECK_EQUAL(time1.Serialize(), 0U);
        CHECK_EQUAL(time2.Serialize(), 0x01020c04u);
        CHECK_EQUAL(time3.Serialize(), 0x173befe7u);
    }

    // Test nanoseconds.
    {
        TimeNs time1(0U, 0U, 0U, 0U);
        TimeNs time2(1U, 2U, 3U, 4U);
        TimeNs time3(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);

        CHECK_EQUAL(time1.Serialize(), 0UL);
        CHECK_EQUAL(time2.Serialize(), HHMMSSNN2INT64(1UL, 2UL, 3UL, 4UL));
        CHECK_EQUAL(time3.Serialize(), HHMMSSNN2INT64(23UL, 59UL, 59UL, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    }
}

TEST_MEMBER_FUNCTION(Time, Deserialize, size_type)
{
    // Test milliseconds.
    {
        TimeMs time;

        time.Deserialize(0U);
        CHECK_EQUAL(time.Serialize(), 0U);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Deserialize(0x01020c04u);
        CHECK_EQUAL(time.Serialize(), 0x01020c04u);
        CHECK_EQUAL(time.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * 4U);
        CHECK_EQUAL(time.GetMilliseconds(), 4U);
        CHECK_EQUAL(time.GetSeconds(), 3U);
        CHECK_EQUAL(time.GetMinutes(), 2U);
        CHECK_EQUAL(time.GetHours(), 1U);

        time.Deserialize(0x173befe7u);
        CHECK_EQUAL(time.Serialize(), 0x173befe7u);
        CHECK_EQUAL(time.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * 999U);
        CHECK_EQUAL(time.GetMilliseconds(), 999U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);
    }

    // Test nanoseconds.
    {
        TimeNs time;

        time.Deserialize(0U);
        CHECK_EQUAL(time.Serialize(), 0U);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        TimeNs::serialize_type value = HHMMSSNN2INT64(1Ul, 2Ul, 3Ul, 4UL);
        time.Deserialize(value);
        CHECK_EQUAL(time.Serialize(), value);
        CHECK_EQUAL(time.GetNanoseconds(), 4U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 3U);
        CHECK_EQUAL(time.GetMinutes(), 2U);
        CHECK_EQUAL(time.GetHours(), 1U);

        value = HHMMSSNN2INT64(23UL, 59UL, 59UL, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        time.Deserialize(value);
        CHECK_EQUAL(time.Serialize(), value);
        CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
        CHECK_EQUAL(time.GetMilliseconds(), TimeNs::MILLISECONDS_PER_SECOND - 1U);
        CHECK_EQUAL(time.GetSeconds(), 59U);
        CHECK_EQUAL(time.GetMinutes(), 59U);
        CHECK_EQUAL(time.GetHours(), 23U);
    }
}

TEST_MEMBER_FUNCTION(Time, Copy, Time_ms_const_ref)
{
    TEST_OVERRIDE_ARGS("TimeMs const&");

    // Test milliseconds.
    {
        TimeMs time;
        TimeMs time_default;
        TimeMs time2(1U, 2U, 3U, 4U);

        time.Copy(time_default);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Copy(time2);
        CHECK_EQUAL(time.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * 4U);
        CHECK_EQUAL(time.GetMilliseconds(), 4U);
        CHECK_EQUAL(time.GetSeconds(), 3U);
        CHECK_EQUAL(time.GetMinutes(), 2U);
        CHECK_EQUAL(time.GetHours(), 1U);
    }

    // Test nanoseconds.
    {
        TimeNs time;
        TimeNs time_default;
        TimeNs time2(1U, 2U, 3U, 4U);

        time.Copy(time_default);
        CHECK_EQUAL(time.GetNanoseconds(), 0U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 0U);
        CHECK_EQUAL(time.GetMinutes(), 0U);
        CHECK_EQUAL(time.GetHours(), 0U);

        time.Copy(time2);
        CHECK_EQUAL(time.GetNanoseconds(), 4U);
        CHECK_EQUAL(time.GetMilliseconds(), 0U);
        CHECK_EQUAL(time.GetSeconds(), 3U);
        CHECK_EQUAL(time.GetMinutes(), 2U);
        CHECK_EQUAL(time.GetHours(), 1U);
    }
}

TEST_MEMBER_FUNCTION(Time, SetTime, hour_type_minute_type_second_type_millisecond_type)
{
    TEST_OVERRIDE_ARGS("hour_type, minute_type, second_type, millisecond_type");

    TimeMs time;

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

TEST_MEMBER_FUNCTION(Time, SetTime, hour_type_minute_type_second_type_nanosecond_type)
{
    TEST_OVERRIDE_ARGS("hour_type, minute_type, second_type, nanosecond_type");

    TimeNs time;

    time.SetTime(1U, 2U, 3U, 4U);
    CHECK_EQUAL(time.GetNanoseconds(), 4UL);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 3U);
    CHECK_EQUAL(time.GetMinutes(), 2U);
    CHECK_EQUAL(time.GetHours(), 1U);

    time.SetTime(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);

    time.SetTime(0U, 0U, 0U, 0U);
    CHECK_EQUAL(time.GetNanoseconds(), 0UL);
    CHECK_EQUAL(time.GetMilliseconds(), 0U);
    CHECK_EQUAL(time.GetSeconds(), 0U);
    CHECK_EQUAL(time.GetMinutes(), 0U);
    CHECK_EQUAL(time.GetHours(), 0U);

    time.SetTime(24U, 60U, 60U, TimeNs::NANOSECONDS_PER_SECOND);
    CHECK_EQUAL(time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1U);
    CHECK_EQUAL(time.GetMilliseconds(), 999U);
    CHECK_EQUAL(time.GetSeconds(), 59U);
    CHECK_EQUAL(time.GetMinutes(), 59U);
    CHECK_EQUAL(time.GetHours(), 23U);
}

TEST_CONST_MEMBER_FUNCTION(Time, Swap, Time_ref)
{
    TEST_OVERRIDE_ARGS("TimeMs&");

    // Test milliseconds.
    {
        TimeMs time1(1U, 2U, 3U, 4U);
        TimeMs time2(5U, 6U, 7U, 8U);

        time1.Swap(time2);
        CHECK_EQUAL(time1, TimeMs(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time2, TimeMs(1U, 2U, 3U, 4U));
    }

    // Test nanoseconds.
    {
        TimeNs time1(1U, 2U, 3U, 4U);
        TimeNs time2(5U, 6U, 7U, 8U);

        time1.Swap(time2);
        CHECK_EQUAL(time1, TimeNs(5U, 6U, 7U, 8U));
        CHECK_EQUAL(time2, TimeNs(1U, 2U, 3U, 4U));
    }
}

TEST_CONST_MEMBER_FUNCTION(Time, Compare, Time_ms_const_ref)
{
    TEST_OVERRIDE_ARGS("TimeMs const&");

    CHECK_EQUAL(TimeMs().Compare(TimeMs()), 0);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 0U).Compare(TimeMs(0U, 0U, 0U, 0U)), 0);
    CHECK_EQUAL(TimeMs(1U, 0U, 0U, 0U).Compare(TimeMs(2U, 0U, 0U, 0U)), -1);
    CHECK_EQUAL(TimeMs(0U, 1U, 0U, 0U).Compare(TimeMs(0U, 2U, 0U, 0U)), -1);
    CHECK_EQUAL(TimeMs(0U, 0U, 1U, 0U).Compare(TimeMs(0U, 0U, 2U, 0U)), -1);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 1U).Compare(TimeMs(0U, 0U, 0U, 2U)), -1);
    CHECK_EQUAL(TimeMs(2U, 0U, 0U, 0U).Compare(TimeMs(1U, 0U, 0U, 0U)), 1);
    CHECK_EQUAL(TimeMs(0U, 2U, 0U, 0U).Compare(TimeMs(0U, 1U, 0U, 0U)), 1);
    CHECK_EQUAL(TimeMs(0U, 0U, 2U, 0U).Compare(TimeMs(0U, 0U, 1U, 0U)), 1);
    CHECK_EQUAL(TimeMs(0U, 0U, 0U, 2U).Compare(TimeMs(0U, 0U, 0U, 1U)), 1);
}

TEST_CONST_MEMBER_FUNCTION(Time, Compare, Time_ns_const_ref)
{
    TEST_OVERRIDE_ARGS("TimeMs const&");

    CHECK_EQUAL(TimeNs().Compare(TimeNs()), 0);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 0U).Compare(TimeNs(0U, 0U, 0U, 0U)), 0);
    CHECK_EQUAL(TimeNs(1U, 0U, 0U, 0U).Compare(TimeNs(2U, 0U, 0U, 0U)), -1);
    CHECK_EQUAL(TimeNs(0U, 1U, 0U, 0U).Compare(TimeNs(0U, 2U, 0U, 0U)), -1);
    CHECK_EQUAL(TimeNs(0U, 0U, 1U, 0U).Compare(TimeNs(0U, 0U, 2U, 0U)), -1);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 1U).Compare(TimeNs(0U, 0U, 0U, 2U)), -1);
    CHECK_EQUAL(TimeNs(2U, 0U, 0U, 0U).Compare(TimeNs(1U, 0U, 0U, 0U)), 1);
    CHECK_EQUAL(TimeNs(0U, 2U, 0U, 0U).Compare(TimeNs(0U, 1U, 0U, 0U)), 1);
    CHECK_EQUAL(TimeNs(0U, 0U, 2U, 0U).Compare(TimeNs(0U, 0U, 1U, 0U)), 1);
    CHECK_EQUAL(TimeNs(0U, 0U, 0U, 2U).Compare(TimeNs(0U, 0U, 0U, 1U)), 1);
}

