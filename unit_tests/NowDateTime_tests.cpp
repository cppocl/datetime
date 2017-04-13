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
#include "../NowDateTime.hpp"
#include <ctime>

using ocl::DateTime;
using ocl::NowDateTime;
typedef DateTime<ocl::Milliseconds> date_time_ms_type;
typedef NowDateTime<ocl::Milliseconds> now_date_time_ms_type;

TEST_MEMBER_FUNCTION(NowDateTime, Now, TimeZone)
{
    now_date_time_ms_type::time_type start = now_date_time_ms_type::Now(ocl::TimeZone::GMT);
    now_date_time_ms_type::time_type curr = start;
    while (curr == start)
        curr = now_date_time_ms_type::Now(ocl::TimeZone::GMT);
    CHECK_TRUE(curr > start);

    start = now_date_time_ms_type::Now(ocl::TimeZone::Local);
    curr = start;
    while (curr == start)
        curr = now_date_time_ms_type::Now(ocl::TimeZone::Local);
    CHECK_TRUE(curr > start);
}

TEST_MEMBER_FUNCTION(ToDateTime, ToDateTime, DateTime_ref_tm_const_ptr)
{
    TEST_OVERRIDE_ARGS("DateTime&, tm const* tm_time");

    tm tm_time;
    date_time_ms_type date_time;

    tm_time.tm_hour = 0;
    tm_time.tm_min = 0;
    tm_time.tm_sec = 0;
    tm_time.tm_mday = 1;
    tm_time.tm_mon = 0; // Jan
    tm_time.tm_year = 0; // 1900
    now_date_time_ms_type::ToDateTime(date_time, tm_time);
    CHECK_TRUE(date_time == date_time_ms_type(1U, 1U, 1900U, 0U, 0U, 0U, 0U));

    tm_time.tm_hour = 23;
    tm_time.tm_min = 59;
    tm_time.tm_sec = 59;
    tm_time.tm_mday = 31;
    tm_time.tm_mon = 11; // Dec
    tm_time.tm_year = 100; // 2000
    now_date_time_ms_type::ToDateTime(date_time, tm_time);
    CHECK_TRUE(date_time == date_time_ms_type(31U, 12U, 2000U, 23U, 59U, 59U, 0U));
}
