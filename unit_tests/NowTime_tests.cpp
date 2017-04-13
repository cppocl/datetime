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
#include "../NowTime.hpp"
#include <ctime>

using ocl::Time;
using ocl::NowTime;
using ocl::TimeMs;
using ocl::TimeNs;
using ocl::NowTimeMs;
using ocl::NowTimeNs;

TEST_MEMBER_FUNCTION(NowTimeMs, Now, TimeZone)
{
    NowTimeMs::time_type start = NowTimeMs::Now(ocl::TimeZone::GMT);
    NowTimeMs::time_type curr = start;
    while (curr == start)
        curr = NowTimeMs::Now(ocl::TimeZone::GMT);
    CHECK_TRUE(curr > start);

    start = NowTimeMs::Now(ocl::TimeZone::Local);
    curr = start;
    while (curr.GetSeconds() == start.GetSeconds())
    {
        curr = NowTimeMs::Now(ocl::TimeZone::Local);
        CHECK_TRUE(curr.GetMilliseconds() >= start.GetMilliseconds());
    }
    CHECK_TRUE(curr > start);
}

TEST_MEMBER_FUNCTION(NowTimeNs, Now, TimeZone)
{
    NowTimeNs::time_type start = NowTimeNs::Now(ocl::TimeZone::GMT);
    NowTimeNs::time_type curr = start;
    while (curr == start)
        curr = NowTimeNs::Now(ocl::TimeZone::GMT);
    CHECK_TRUE(curr > start);

    start = NowTimeNs::Now(ocl::TimeZone::Local);
    curr = start;
    while (curr.GetSeconds() == start.GetSeconds())
    {
        curr = NowTimeNs::Now(ocl::TimeZone::Local);
        if (curr.GetNanoseconds() < start.GetNanoseconds())
        {
            CHECK_TRUE(curr.GetNanoseconds() >= start.GetNanoseconds());
        }
        CHECK_TRUE(curr.GetNanoseconds() >= start.GetNanoseconds());
    }
    CHECK_TRUE(curr > start);
}

TEST_MEMBER_FUNCTION(ToDateTime, ToTime, Time_ref_tm_const_ptr)
{
    TEST_OVERRIDE_ARGS("TimeMs&, tm const* tm_time");

    tm tm_time;
    TimeMs time;

    tm_time.tm_hour = 0;
    tm_time.tm_min = 0;
    tm_time.tm_sec = 0;
    NowTimeMs::ToTime(time, tm_time);
    CHECK_TRUE(time == TimeMs(0U, 0U, 0U, 0U));

    tm_time.tm_hour = 23;
    tm_time.tm_min = 59;
    tm_time.tm_sec = 59;
    NowTimeMs::ToTime(time, tm_time);
    CHECK_TRUE(time == TimeMs(23U, 59U, 59U, 0U));
}
