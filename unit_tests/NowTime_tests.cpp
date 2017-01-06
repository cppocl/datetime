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

using ocl::NowTime;

TEST_MEMBER_FUNCTION(NowTime, Now, TimeZone)
{
    NowTime::time_type start = NowTime::Now(ocl::TimeZone::GMT);
    NowTime::time_type curr = start;
    while (curr == start)
        curr = NowTime::Now();
    CHECK_TRUE(curr > start);

    start = NowTime::Now(ocl::TimeZone::Local);
    curr = start;
    while (curr == start)
        curr = NowTime::Now();
    CHECK_TRUE(curr > start);
}

TEST_MEMBER_FUNCTION(ToDateTime, ToTime, Time_ref_tm_const_ptr)
{
    TEST_OVERRIDE_ARGS("Time&, tm const* tm_time");

    using ocl::Time;

    tm tm_time;
    Time time;

    tm_time.tm_hour = 0;
    tm_time.tm_min = 0;
    tm_time.tm_sec = 0;
    NowTime::ToTime(time, tm_time);
    CHECK_TRUE(time == Time(0U, 0U, 0U, 0U));

    tm_time.tm_hour = 23;
    tm_time.tm_min = 59;
    tm_time.tm_sec = 59;
    NowTime::ToTime(time, tm_time);
    CHECK_TRUE(time == Time(23U, 59U, 59U, 0U));
}
