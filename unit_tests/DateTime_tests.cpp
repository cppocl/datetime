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
#include "../DateTime.hpp"

using ocl::DateTime;

TEST_MEMBER_FUNCTION(DateTime, constructor, NA)
{
    DateTime dt;

    CHECK_EQUAL(dt.GetTime(), 0U);
    CHECK_EQUAL(dt.GetDate(), 0x07b20101U);
}
