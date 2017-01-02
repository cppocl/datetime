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
#include "../Ticks.hpp"

using ocl::Ticks;
typedef Ticks<> ticks_type;
typedef Ticks<>::time_type time_type;

TEST_MEMBER_FUNCTION(Ticks, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("Ticks");

    ticks_type ticks;
    CHECK_TRUE(ticks.GetStart() == static_cast<time_type>(0));
    CHECK_TRUE(ticks.GetStop() == static_cast<time_type>(0));
}

TEST_MEMBER_FUNCTION(Ticks, constructor, bool)
{
    TEST_OVERRIDE_FUNCTION_NAME("Ticks");

    {
        ticks_type ticks(false);
        CHECK_EQUAL(ticks.GetStart(), static_cast<time_type>(0));
        CHECK_EQUAL(ticks.GetStop(), static_cast<time_type>(0));
    }

    {
        ticks_type ticks(true);
        CHECK_TRUE(ticks.GetStart() > static_cast<time_type>(0));
        CHECK_EQUAL(ticks.GetStop(), static_cast<time_type>(0));
    }
}

TEST_MEMBER_FUNCTION(Ticks, constructor, time_type_ptr)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("Ticks", "time_type*");

    time_type elapsed = static_cast<time_type>(0);
    time_type start   = static_cast<time_type>(0);

    {
        ticks_type ticks(elapsed);
        start = ticks.GetStart();
        time_type curr = start;
        while (curr == ticks_type::Now())
            ;
    }

    CHECK_TRUE(elapsed > static_cast<time_type>(0));
}
