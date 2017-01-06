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
#include "../NowDate.hpp"
#include <ctime>

using ocl::NowDate;

TEST_MEMBER_FUNCTION(NowDate, Now, TimeZone)
{
    NowDate::time_type now_date = NowDate::Now(ocl::TimeZone::GMT);
    CHECK_TRUE(now_date.GetYear() >= 1900U);
}

TEST_MEMBER_FUNCTION(ToDate, ToDate, Date_ref_tm_const_ptr)
{
    TEST_OVERRIDE_ARGS("Date&, tm const* tm_time");

    using ocl::Date;

    tm tm_time;
    Date date;

    tm_time.tm_mday = 1;
    tm_time.tm_mon = 0; // Jan
    tm_time.tm_year = 0; // 1900
    NowDate::ToDate(date, tm_time);
    CHECK_TRUE(date == Date(1U, 1U, 1900U));

    tm_time.tm_mday = 31;
    tm_time.tm_mon = 11; // Dec
    tm_time.tm_year = 100; // 2000
    NowDate::ToDate(date, tm_time);
    CHECK_TRUE(date == Date(31U, 12U, 2000U));
}
