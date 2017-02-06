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
#include "../Now.hpp"

using ocl::Now;
using ocl::NowTicks;
using ocl::Date;
using ocl::Time;
using ocl::DateTime;

TEST_MEMBER_FUNCTION(Now, GetNow, NA)
{
    NowTicks<>::time_type start = Now<NowTicks<>::time_type>::GetNow();
    NowTicks<>::time_type curr = start;
    while (curr == start)
        curr = NowTicks<>::Now();
    CHECK_TRUE(curr > start);

    Date date(1U, 1U, 1900U);
    date = Now<Date>::GetNow();
    CHECK_TRUE(date != Date(1U, 1U, 1900U));

    Time time(0U, 0U, 0U, 0U);
    time = Now<Time>::GetNow();
    CHECK_TRUE(time != Time(0U, 0U, 0U, 0U));

    DateTime date_time(1U, 1U, 1900U, 0U, 0U, 0U, 0U);
    date_time = Now<DateTime>::GetNow();
    CHECK_TRUE(date_time != DateTime(1U, 1U, 1900U, 0U, 0U, 0U, 0U));
}
