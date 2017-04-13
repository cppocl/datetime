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

using ocl::Date;
using ocl::Time;
using ocl::TimeMs;
using ocl::TimeNs;
using ocl::DateTime;
using ocl::DateTimeMs;
using ocl::DateTimeNs;

TEST_MEMBER_FUNCTION(DateTimeMs, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("DateTimeMs");

    DateTimeMs dt;

    CHECK_EQUAL(dt.GetNanoseconds(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);
    CHECK_EQUAL(dt.GetYear(), DateTimeMs::DEFAULT_YEAR);
    CHECK_EQUAL(dt.GetMonth(), DateTimeMs::MIN_MONTH);
    CHECK_EQUAL(dt.GetDay(), DateTimeMs::MIN_DAY);
}

TEST_MEMBER_FUNCTION(DateTimeNs, constructor, NA)
{
    TEST_OVERRIDE_FUNCTION_NAME("DateTimeNs");

    DateTimeNs dt;

    CHECK_EQUAL(dt.GetNanoseconds(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);
    CHECK_EQUAL(dt.GetYear(), DateTimeNs::DEFAULT_YEAR);
    CHECK_EQUAL(dt.GetMonth(), DateTimeNs::MIN_MONTH);
    CHECK_EQUAL(dt.GetDay(), DateTimeNs::MIN_DAY);
}

TEST_MEMBER_FUNCTION(DateTimeMs, constructor, Date_const_ref_TimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTimeMs", "Date const&, TimeMs const&");

    {
        Date date;
        TimeMs time;
        DateTimeMs dt(date, time);

        CHECK_EQUAL(dt.GetNanoseconds(), 0U);
        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 0U);
        CHECK_EQUAL(dt.GetMinutes(), 0U);
        CHECK_EQUAL(dt.GetHours(), 0U);
        CHECK_EQUAL(dt.GetYear(), DateTimeMs::DEFAULT_YEAR);
        CHECK_EQUAL(dt.GetMonth(), DateTimeMs::MIN_MONTH);
        CHECK_EQUAL(dt.GetDay(), DateTimeMs::MIN_DAY);
    }

    {
        DateTimeMs dt(Date(1U, 2U, 2000U), TimeMs(1U, 2U, 3U, 4U));

        CHECK_EQUAL(dt.GetNanoseconds(), TimeNs::NANOSECONDS_PER_MILLISECOND * 4UL);
        CHECK_EQUAL(dt.GetMilliseconds(), 4U);
        CHECK_EQUAL(dt.GetSeconds(), 3U);
        CHECK_EQUAL(dt.GetMinutes(), 2U);
        CHECK_EQUAL(dt.GetHours(), 1U);
        CHECK_EQUAL(dt.GetYear(), 2000U);
        CHECK_EQUAL(dt.GetMonth(), 2U);
        CHECK_EQUAL(dt.GetDay(), 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, constructor, Date_const_ref_TimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTimeNs", "Date const&, TimeNs const&");

    {
        Date date;
        TimeNs time;
        DateTimeNs dt(date, time);

        CHECK_EQUAL(dt.GetNanoseconds(), 0U);
        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 0U);
        CHECK_EQUAL(dt.GetMinutes(), 0U);
        CHECK_EQUAL(dt.GetHours(), 0U);
        CHECK_EQUAL(dt.GetYear(), DateTimeMs::DEFAULT_YEAR);
        CHECK_EQUAL(dt.GetMonth(), DateTimeMs::MIN_MONTH);
        CHECK_EQUAL(dt.GetDay(), DateTimeMs::MIN_DAY);
    }

    {
        DateTimeNs dt(Date(1U, 2U, 2000U), TimeNs(1U, 2U, 3U, 4U));

        CHECK_EQUAL(dt.GetNanoseconds(), 4UL);
        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 3U);
        CHECK_EQUAL(dt.GetMinutes(), 2U);
        CHECK_EQUAL(dt.GetHours(), 1U);
        CHECK_EQUAL(dt.GetYear(), 2000U);
        CHECK_EQUAL(dt.GetMonth(), 2U);
        CHECK_EQUAL(dt.GetDay(), 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, constructor, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTimeMs", "DateTimeMs const&");

    {
        DateTimeMs dt_src;
        DateTimeMs dt(dt_src);

        CHECK_EQUAL(dt.GetNanoseconds(), 0UL);
        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 0U);
        CHECK_EQUAL(dt.GetMinutes(), 0U);
        CHECK_EQUAL(dt.GetHours(), 0U);
        CHECK_EQUAL(dt.GetYear(), DateTimeMs::DEFAULT_YEAR);
        CHECK_EQUAL(dt.GetMonth(), DateTimeMs::MIN_MONTH);
        CHECK_EQUAL(dt.GetDay(), DateTimeMs::MIN_DAY);
    }

    {
        DateTimeMs dt_src(Date(1U, 2U, 2000U), TimeMs(1U, 2U, 3U, 4U));
        DateTimeMs dt(dt_src);

        CHECK_EQUAL(dt.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * 4UL);
        CHECK_EQUAL(dt.GetMilliseconds(), 4U);
        CHECK_EQUAL(dt.GetSeconds(), 3U);
        CHECK_EQUAL(dt.GetMinutes(), 2U);
        CHECK_EQUAL(dt.GetHours(), 1U);
        CHECK_EQUAL(dt.GetYear(), 2000U);
        CHECK_EQUAL(dt.GetMonth(), 2U);
        CHECK_EQUAL(dt.GetDay(), 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, constructor, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("DateTimeNs", "DateTimeNs const&");

    {
        DateTimeNs dt_src;
        DateTimeNs dt(dt_src);

        CHECK_EQUAL(dt.GetNanoseconds(), 0UL);
        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 0U);
        CHECK_EQUAL(dt.GetMinutes(), 0U);
        CHECK_EQUAL(dt.GetHours(), 0U);
        CHECK_EQUAL(dt.GetYear(), DateTimeNs::DEFAULT_YEAR);
        CHECK_EQUAL(dt.GetMonth(), DateTimeNs::MIN_MONTH);
        CHECK_EQUAL(dt.GetDay(), DateTimeNs::MIN_DAY);
    }

    {
        DateTimeNs dt_src(Date(1U, 2U, 2000U), TimeNs(1U, 2U, 3U, 4U));
        DateTimeNs dt(dt_src);

        CHECK_EQUAL(dt.GetNanoseconds(), 4UL);
        CHECK_EQUAL(dt.GetMilliseconds(), 0U);
        CHECK_EQUAL(dt.GetSeconds(), 3U);
        CHECK_EQUAL(dt.GetMinutes(), 2U);
        CHECK_EQUAL(dt.GetHours(), 1U);
        CHECK_EQUAL(dt.GetYear(), 2000U);
        CHECK_EQUAL(dt.GetMonth(), 2U);
        CHECK_EQUAL(dt.GetDay(), 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, assignment_operator, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "DateTimeMs const&");

    DateTimeMs dt1;
    DateTimeMs dt2(Date(1U, 2U, 2000U), TimeMs(1U, 2U, 3U, 4U));
    DateTimeMs dt;

    dt = dt1;
    CHECK_TRUE(dt == dt1);

    dt = dt2;
    CHECK_TRUE(dt == dt2);
}

TEST_MEMBER_FUNCTION(DateTimeNs, assignment_operator, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator =", "DateTimeNs const&");

    DateTimeNs dt1;
    DateTimeNs dt2(Date(1U, 2U, 2000U), TimeNs(1U, 2U, 3U, 4U));
    DateTimeNs dt;

    dt = dt1;
    CHECK_TRUE(dt == dt1);

    dt = dt2;
    CHECK_TRUE(dt == dt2);
}

TEST_MEMBER_FUNCTION(DateTimeMs, operator_less, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <", "DateTimeMs const&");

    DateTimeMs dt(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt < DateTimeMs(Date(3U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 6U)));
    CHECK_TRUE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 5U, 5U)));
    CHECK_TRUE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 4U, 4U, 5U)));
    CHECK_TRUE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(3U, 3U, 4U, 5U)));

    CHECK_FALSE(dt < DateTimeMs(Date(1U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 4U)));
    CHECK_FALSE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt < DateTimeMs(Date(2U, 3U, 2000U), TimeMs(1U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, operator_less, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <", "DateTimeMs const&");

    DateTimeNs dt(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt < DateTimeNs(Date(3U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_TRUE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 6U)));
    CHECK_TRUE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 5U, 5U)));
    CHECK_TRUE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 4U, 4U, 5U)));
    CHECK_TRUE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(3U, 3U, 4U, 5U)));

    CHECK_FALSE(dt < DateTimeNs(Date(1U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_FALSE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 4U)));
    CHECK_FALSE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt < DateTimeNs(Date(2U, 3U, 2000U), TimeNs(1U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, operator_less_eq, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <=", "DateTimeMs const&");

    DateTimeMs dt(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt <= DateTimeMs(Date(3U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 6U)));
    CHECK_TRUE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 5U, 5U)));
    CHECK_TRUE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 4U, 4U, 5U)));
    CHECK_TRUE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(3U, 3U, 4U, 5U)));
    CHECK_TRUE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt <= DateTimeMs(Date(1U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 4U)));
    CHECK_FALSE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt <= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(1U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, operator_less_eq, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator <=", "DateTimeNs const&");

    DateTimeNs dt(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt <= DateTimeNs(Date(3U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_TRUE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 6U)));
    CHECK_TRUE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 5U, 5U)));
    CHECK_TRUE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 4U, 4U, 5U)));
    CHECK_TRUE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(3U, 3U, 4U, 5U)));
    CHECK_TRUE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt <= DateTimeNs(Date(1U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_FALSE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 4U)));
    CHECK_FALSE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt <= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(1U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, operator_greater, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >", "DateTimeMs const&");

    DateTimeMs dt(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt > DateTimeMs(Date(1U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 4U)));
    CHECK_TRUE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(1U, 3U, 4U, 5U)));

    CHECK_FALSE(dt > DateTimeMs(Date(3U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 6U)));
    CHECK_FALSE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 5U, 5U)));
    CHECK_FALSE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 4U, 4U, 5U)));
    CHECK_FALSE(dt > DateTimeMs(Date(2U, 3U, 2000U), TimeMs(3U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, operator_greater, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >", "DateTimeNs const&");

    DateTimeNs dt(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt > DateTimeNs(Date(1U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_TRUE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 4U)));
    CHECK_TRUE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(1U, 3U, 4U, 5U)));

    CHECK_FALSE(dt > DateTimeNs(Date(3U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_FALSE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 6U)));
    CHECK_FALSE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 5U, 5U)));
    CHECK_FALSE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 4U, 4U, 5U)));
    CHECK_FALSE(dt > DateTimeNs(Date(2U, 3U, 2000U), TimeNs(3U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, operator_greater_eq, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >=", "DateTimeMs const&");

    DateTimeMs dt(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt >= DateTimeMs(Date(1U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_TRUE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 4U)));
    CHECK_TRUE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(1U, 3U, 4U, 5U)));
    CHECK_TRUE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt >= DateTimeMs(Date(3U, 3U, 2000U), TimeMs(23U, 59U, 59U, 999U)));
    CHECK_FALSE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 6U)));
    CHECK_FALSE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 5U, 5U)));
    CHECK_FALSE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 4U, 4U, 5U)));
    CHECK_FALSE(dt >= DateTimeMs(Date(2U, 3U, 2000U), TimeMs(3U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, operator_greater_eq, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator >=", "DateTimeNs const&");

    DateTimeNs dt(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt >= DateTimeNs(Date(1U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_TRUE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 4U)));
    CHECK_TRUE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(1U, 3U, 4U, 5U)));
    CHECK_TRUE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt >= DateTimeNs(Date(3U, 3U, 2000U), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL)));
    CHECK_FALSE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 6U)));
    CHECK_FALSE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 5U, 5U)));
    CHECK_FALSE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 4U, 4U, 5U)));
    CHECK_FALSE(dt >= DateTimeNs(Date(2U, 3U, 2000U), TimeNs(3U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, operator_eq, DateTimeMs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator ==", "DateTimeMs const&");

    DateTimeMs dt(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt == DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt == DateTimeMs(Date(1U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeMs(Date(2U, 2U, 2000U), TimeMs(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeMs(Date(2U, 3U, 2001U), TimeMs(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeMs(Date(2U, 3U, 2000U), TimeMs(1U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt == DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 4U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, operator_eq, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator ==", "DateTimeNs const&");

    DateTimeNs dt(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt == DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U)));

    CHECK_FALSE(dt == DateTimeNs(Date(1U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeNs(Date(2U, 2U, 2000U), TimeNs(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeNs(Date(2U, 3U, 2001U), TimeNs(2U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeNs(Date(2U, 3U, 2000U), TimeNs(1U, 3U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 2U, 4U, 5U)));
    CHECK_FALSE(dt == DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 3U, 5U)));
    CHECK_FALSE(dt == DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 4U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, operator_not_eq, DateTime_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator !=", "DateTimeMs const&");

    DateTimeMs dt(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt != DateTimeMs(Date(1U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeMs(Date(2U, 2U, 2000U), TimeMs(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeMs(Date(2U, 3U, 2001U), TimeMs(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeMs(Date(2U, 3U, 2000U), TimeMs(1U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt != DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 4U)));

    CHECK_FALSE(dt != DateTimeMs(Date(2U, 3U, 2000U), TimeMs(2U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, operator_not_eq, DateTimeNs_const_ref)
{
    TEST_OVERRIDE_FUNCTION_NAME_ARGS("operator !=", "DateTimeNs const&");

    DateTimeNs dt(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U));

    CHECK_TRUE(dt != DateTimeNs(Date(1U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeNs(Date(2U, 2U, 2000U), TimeNs(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeNs(Date(2U, 3U, 2001U), TimeNs(2U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeNs(Date(2U, 3U, 2000U), TimeNs(1U, 3U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 2U, 4U, 5U)));
    CHECK_TRUE(dt != DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 3U, 5U)));
    CHECK_TRUE(dt != DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 4U)));

    CHECK_FALSE(dt != DateTimeNs(Date(2U, 3U, 2000U), TimeNs(2U, 3U, 4U, 5U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetDaysInMonth, month_type)
{
    Date::day_type days_in_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    for (DateTimeMs::month_type month = DateTimeMs::JANUARY; month <= DateTimeMs::DECEMBER; ++month)
        CHECK_EQUAL(days_in_month[month - Date::JANUARY], DateTimeMs::GetDaysInMonth(month));
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetDaysInMonth, month_type)
{
    Date::day_type days_in_month[Date::MONTHS_PER_YEAR] =
    {
        31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    for (DateTimeNs::month_type month = DateTimeNs::JANUARY; month <= DateTimeNs::DECEMBER; ++month)
        CHECK_EQUAL(days_in_month[month - Date::JANUARY], DateTimeNs::GetDaysInMonth(month));
}

TEST_MEMBER_FUNCTION(DateTimeMs, IsLeapYear, year_type)
{
    CHECK_FALSE(DateTimeMs::IsLeapYear(1800U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(1900U));
    CHECK_TRUE(DateTimeMs::IsLeapYear(2000U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(2003U));
    CHECK_TRUE(DateTimeMs::IsLeapYear(2004U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(2005U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(2006U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(2007U));
    CHECK_TRUE(DateTimeMs::IsLeapYear(2008U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(2100U));
    CHECK_FALSE(DateTimeMs::IsLeapYear(2200U));
}

TEST_MEMBER_FUNCTION(DateTimeNs, IsLeapYear, year_type)
{
    CHECK_FALSE(DateTimeNs::IsLeapYear(1800U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(1900U));
    CHECK_TRUE(DateTimeNs::IsLeapYear(2000U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(2003U));
    CHECK_TRUE(DateTimeNs::IsLeapYear(2004U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(2005U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(2006U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(2007U));
    CHECK_TRUE(DateTimeNs::IsLeapYear(2008U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(2100U));
    CHECK_FALSE(DateTimeNs::IsLeapYear(2200U));
}

TEST_MEMBER_FUNCTION(DateTimeMs, IsLeapMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 1800U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 1900U));
    CHECK_TRUE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2000U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2003U));
    CHECK_TRUE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2004U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2005U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2006U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2007U));
    CHECK_TRUE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2008U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2100U));
    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::FEBRUARY, 2200U));

    CHECK_FALSE(DateTimeMs::IsLeapMonth(DateTimeMs::JANUARY, 1800U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 1900U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2000U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2003U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2004U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2005U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2006U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2007U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2008U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2100U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeMs::JANUARY, 2200U));
}

TEST_MEMBER_FUNCTION(DateTimeNs, IsLeapMonth, month_type_year_type)
{
    TEST_OVERRIDE_ARGS("month_type, year_type");

    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 1800U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 1900U));
    CHECK_TRUE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2000U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2003U));
    CHECK_TRUE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2004U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2005U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2006U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2007U));
    CHECK_TRUE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2008U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2100U));
    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::FEBRUARY, 2200U));

    CHECK_FALSE(DateTimeNs::IsLeapMonth(DateTimeNs::JANUARY, 1800U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 1900U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2000U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2003U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2004U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2005U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2006U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2007U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2008U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2100U));
    CHECK_FALSE(Date::IsLeapMonth(DateTimeNs::JANUARY, 2200U));
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetDifference, DateTimeMs_const_ref_DateTimeMs_const_ref_date_size_type_ref_time_size_type_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs const&, DateTimeMs const&, date_size_type&, time_size_type&");

    DateTimeMs::date_size_type day;
    DateTimeMs::time_size_type milliseconds;

    {
        day = 1U;          // Set to something that will change.
        milliseconds = 1U;
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 0U);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        day = 2U;          // Set to something that will change.
        milliseconds = 2U;
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 0U);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        day = 2U;          // Set to something that will change.
        milliseconds = 2U;
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(2U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        day = 2U;          // Set to something that will change.
        milliseconds = 2U;
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(2U, 1U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        day = 2U;          // Set to something that will change.
        milliseconds = 2U;
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(1U, 2U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, Date::DAYS_IN_JANUARY);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        day = 2U;          // Set to something that will change.
        milliseconds = 2U;
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs date_time2(Date(1U, 2U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs::GetDifference(date_time1, date_time2, day, milliseconds);
        CHECK_EQUAL(day, Date::DAYS_IN_JANUARY - 1U);
        CHECK_EQUAL(milliseconds, TimeMs::MILLISECONDS_PER_DAY - 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetDifference, DateTimeNs_const_ref_DateTimeNs_const_ref_date_size_type_ref_time_size_type_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeNs const&, DateTimeNs const&, date_size_type&, time_size_type&");

    DateTimeNs::date_size_type day;
    DateTimeNs::time_size_type nanoseconds;

    {
        day = 1U;         // Set to something that will change.
        nanoseconds = 1U;
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs::GetDifference(date_time1, date_time2, day, nanoseconds);
        CHECK_EQUAL(day, 0U);
        CHECK_EQUAL(nanoseconds, 0U);
    }

    {
        day = 2U;         // Set to something that will change.
        nanoseconds = 2U;
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs::GetDifference(date_time1, date_time2, day, nanoseconds);
        CHECK_EQUAL(day, 0U);
        CHECK_EQUAL(nanoseconds, 1U);
    }

    {
        day = 2U;         // Set to something that will change.
        nanoseconds = 2U;
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(2U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs::GetDifference(date_time1, date_time2, day, nanoseconds);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(nanoseconds, 0U);
    }

    {
        day = 2U;         // Set to something that will change.
        nanoseconds = 2U;
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(2U, 1U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs::GetDifference(date_time1, date_time2, day, nanoseconds);
        CHECK_EQUAL(day, 1U);
        CHECK_EQUAL(nanoseconds, 1U);
    }

    {
        day = 2U;         // Set to something that will change.
        nanoseconds = 2U;
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(1U, 2U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs::GetDifference(date_time1, date_time2, day, nanoseconds);
        CHECK_EQUAL(day, Date::DAYS_IN_JANUARY);
        CHECK_EQUAL(nanoseconds, 1U);
    }

    {
        day = 2U;         // Set to something that will change.
        nanoseconds = 2U;
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs date_time2(Date(1U, 2U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs::GetDifference(date_time1, date_time2, day, nanoseconds);
        CHECK_EQUAL(day, Date::DAYS_IN_JANUARY - 1U);
        CHECK_EQUAL(nanoseconds, TimeNs::NANOSECONDS_PER_DAY - 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetDifference, DateTimeMs_const_ref_DateTimeMs_const_ref_time_size_type_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs const&, DateTimeMs const&, time_size_type&");

    DateTimeMs::time_size_type milliseconds;

    {
        milliseconds = 1U; // Set to something that will change.
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, 0U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, 1U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(2U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, TimeMs::MILLISECONDS_PER_DAY);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(2U, 1U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, TimeMs::MILLISECONDS_PER_DAY + 1U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs date_time2(Date(1U, 2U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, (TimeMs::MILLISECONDS_PER_DAY * Date::DAYS_IN_JANUARY) + 1U);
    }

    {
        milliseconds = 2U; // Set to something that will change.
        DateTimeMs date_time1(Date(1U, 1U, 1980U), TimeMs(0U, 0U, 0U, 1U));
        DateTimeMs date_time2(Date(1U, 2U, 1980U), TimeMs(0U, 0U, 0U, 0U));
        DateTimeMs::GetDifference(date_time1, date_time2, milliseconds);
        CHECK_EQUAL(milliseconds, (TimeMs::MILLISECONDS_PER_DAY * Date::DAYS_IN_JANUARY) - 1U);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetDifference, DateTimeNs_const_ref_DateTimeNs_const_ref_time_size_type_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs const&, DateTimeMs const&, time_size_type&");

    DateTimeNs::time_size_type nanoseconds;

    {
        nanoseconds = 1U; // Set to something that will change.
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs::GetDifference(date_time1, date_time2, nanoseconds);
        CHECK_EQUAL(nanoseconds, 0U);
    }

    {
        nanoseconds = 2U; // Set to something that will change.
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs::GetDifference(date_time1, date_time2, nanoseconds);
        CHECK_EQUAL(nanoseconds, 1U);
    }

    {
        nanoseconds = 2U; // Set to something that will change.
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(2U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs::GetDifference(date_time1, date_time2, nanoseconds);
        CHECK_EQUAL(nanoseconds, TimeNs::NANOSECONDS_PER_DAY);
    }

    {
        nanoseconds = 2U; // Set to something that will change.
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(2U, 1U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs::GetDifference(date_time1, date_time2, nanoseconds);
        CHECK_EQUAL(nanoseconds, TimeNs::NANOSECONDS_PER_DAY + 1U);
    }

    {
        nanoseconds = 2U; // Set to something that will change.
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs date_time2(Date(1U, 2U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs::GetDifference(date_time1, date_time2, nanoseconds);
        CHECK_EQUAL(nanoseconds, (TimeNs::NANOSECONDS_PER_DAY * Date::DAYS_IN_JANUARY) + 1U);
    }

    {
        nanoseconds = 2U; // Set to something that will change.
        DateTimeNs date_time1(Date(1U, 1U, 1980U), TimeNs(0U, 0U, 0U, 1U));
        DateTimeNs date_time2(Date(1U, 2U, 1980U), TimeNs(0U, 0U, 0U, 0U));
        DateTimeNs::GetDifference(date_time1, date_time2, nanoseconds);
        CHECK_EQUAL(nanoseconds, (TimeNs::NANOSECONDS_PER_DAY * Date::DAYS_IN_JANUARY) - 1U);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, GetDay, NA)
{
    DateTimeMs dt1(Date(1U, 2U, 1980U), TimeMs());
    CHECK_EQUAL(dt1.GetDay(), 1U);

    DateTimeMs dt2(Date(31U, 1U, 1980U), TimeMs());
    CHECK_EQUAL(dt2.GetDay(), 31U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, GetDay, NA)
{
    DateTimeNs dt1(Date(1U, 2U, 1980U), TimeNs());
    CHECK_EQUAL(dt1.GetDay(), 1U);

    DateTimeNs dt2(Date(31U, 1U, 1980U), TimeNs());
    CHECK_EQUAL(dt2.GetDay(), 31U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, SetDay, day_type)
{
    DateTimeMs dt;
    dt.SetDay(2U);
    CHECK_EQUAL(dt.GetDay(), 2U);

    dt.SetDay(31U);
    CHECK_EQUAL(dt.GetDay(), 31U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, SetDay, day_type)
{
    DateTimeNs dt;
    dt.SetDay(2U);
    CHECK_EQUAL(dt.GetDay(), 2U);

    dt.SetDay(31U);
    CHECK_EQUAL(dt.GetDay(), 31U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, GetMonth, NA)
{
    DateTimeMs dt1(Date(2U, 1U, 1980U), TimeMs());
    CHECK_EQUAL(dt1.GetMonth(), 1U);

    DateTimeMs dt2(Date(2U, 12U, 1980U), TimeMs());
    CHECK_EQUAL(dt2.GetMonth(), 12U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, GetMonth, NA)
{
    DateTimeNs dt1(Date(2U, 1U, 1980U), TimeNs());
    CHECK_EQUAL(dt1.GetMonth(), 1U);

    DateTimeNs dt2(Date(2U, 12U, 1980U), TimeNs());
    CHECK_EQUAL(dt2.GetMonth(), 12U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, SetMonth, month_type)
{
    DateTimeMs dt;

    dt.SetMonth(1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);

    dt.SetMonth(12U);
    CHECK_EQUAL(dt.GetMonth(), 12U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, SetMonth, month_type)
{
    DateTimeNs dt;

    dt.SetMonth(1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);

    dt.SetMonth(12U);
    CHECK_EQUAL(dt.GetMonth(), 12U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, GetYear, NA)
{
    DateTimeMs dt1(Date(2U, 1U, 1980U), TimeMs());
    CHECK_EQUAL(dt1.GetYear(), 1980U);

    DateTimeMs dt2(Date(2U, 12U, 2000U), TimeMs());
    CHECK_EQUAL(dt2.GetYear(), 2000U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, GetYear, NA)
{
    DateTimeNs dt1(Date(2U, 1U, 1980U), TimeNs());
    CHECK_EQUAL(dt1.GetYear(), 1980U);

    DateTimeNs dt2(Date(2U, 12U, 2000U), TimeNs());
    CHECK_EQUAL(dt2.GetYear(), 2000U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, SetYear, year_type)
{
    DateTimeMs dt;

    dt.SetYear(1980U);
    CHECK_EQUAL(dt.GetYear(), 1980U);

    dt.SetYear(2000U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, SetYear, year_type)
{
    DateTimeNs dt;

    dt.SetYear(1980U);
    CHECK_EQUAL(dt.GetYear(), 1980U);

    dt.SetYear(2000U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, IsLeapYear, NA)
{
    DateTimeMs dt;

    dt.SetYear(1800U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(1900U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2000U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2003U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2004U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2005U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2006U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2007U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2008U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2100U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2200U);
    CHECK_FALSE(dt.IsLeapYear());
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, IsLeapYear, NA)
{
    DateTimeNs dt;

    dt.SetYear(1800U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(1900U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2000U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2003U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2004U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2005U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2006U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2007U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2008U);
    CHECK_TRUE(dt.IsLeapYear());

    dt.SetYear(2100U);
    CHECK_FALSE(dt.IsLeapYear());

    dt.SetYear(2200U);
    CHECK_FALSE(dt.IsLeapYear());
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetNanoseconds, NA)
{
    for (DateTimeMs::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        DateTimeMs dt(Date(), TimeMs(0U, 1U, 2U, ms));
        CHECK_EQUAL(dt.GetNanoseconds(), TimeMs::NANOSECONDS_PER_MILLISECOND * ms);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetNanoseconds, NA)
{
    for (DateTimeNs::nanosecond_type ns = 0;
         ns < TimeNs::NANOSECONDS_PER_SECOND;
         ns += TimeNs::NANOSECONDS_PER_MILLISECOND)
    {
        DateTimeNs dt(Date(), TimeNs(0U, 1U, 2U, ns));
        CHECK_EQUAL(dt.GetNanoseconds(), ns);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, SetNanoseconds, nanosecond_type)
{
    DateTimeMs dt;
    for (DateTimeMs::nanosecond_type ns = 0;
         ns < TimeMs::NANOSECONDS_PER_SECOND;
         ns += TimeMs::NANOSECONDS_PER_MILLISECOND)
    {
        dt.SetNanoseconds(ns);
        CHECK_EQUAL(dt.GetNanoseconds(), ns);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, SetNanoseconds, nanosecond_type)
{
    DateTimeNs dt;
    for (DateTimeNs::nanosecond_type ns = 0;
         ns < TimeNs::NANOSECONDS_PER_SECOND;
         ns += TimeNs::NANOSECONDS_PER_MILLISECOND)
    {
        dt.SetNanoseconds(ns);
        CHECK_EQUAL(dt.GetNanoseconds(), ns);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetMilliseconds, NA)
{
    for (DateTimeMs::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        DateTimeMs dt(Date(), TimeMs(0U, 1U, 2U, ms));
        CHECK_EQUAL(dt.GetMilliseconds(), ms);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetMilliseconds, NA)
{
    for (DateTimeNs::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        DateTimeNs dt(Date(), TimeNs(0U, 1U, 2U, TimeNs::NANOSECONDS_PER_MILLISECOND * ms));
        CHECK_EQUAL(dt.GetMilliseconds(), ms);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, SetMilliseconds, millisecond_type)
{
    DateTimeMs dt;
    for (DateTimeMs::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        dt.SetMilliseconds(ms);
        CHECK_EQUAL(dt.GetMilliseconds(), ms);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, SetMilliseconds, millisecond_type)
{
    DateTimeNs dt;
    for (DateTimeNs::millisecond_type ms = 0; ms <= 999U; ++ms)
    {
        dt.SetMilliseconds(ms);
        CHECK_EQUAL(dt.GetMilliseconds(), ms);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetSeconds, NA)
{
    for (DateTimeMs::second_type s = 0; s <= 59U; ++s)
    {
        DateTimeMs dt(Date(), TimeMs(0U, 1U, s, 3U));
        CHECK_EQUAL(dt.GetSeconds(), s);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetSeconds, NA)
{
    for (DateTimeNs::second_type s = 0; s <= 59U; ++s)
    {
        DateTimeNs dt(Date(), TimeNs(0U, 1U, s, 3U));
        CHECK_EQUAL(dt.GetSeconds(), s);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, SetSeconds, second_type)
{
    DateTimeMs dt;
    for (DateTimeMs::second_type s = 0; s <= 59U; ++s)
    {
        dt.SetSeconds(s);
        CHECK_EQUAL(dt.GetSeconds(), s);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, SetSeconds, second_type)
{
    DateTimeNs dt;
    for (DateTimeNs::second_type s = 0; s <= 59U; ++s)
    {
        dt.SetSeconds(s);
        CHECK_EQUAL(dt.GetSeconds(), s);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetMinutes, NA)
{
    for (DateTimeMs::minute_type m = 0; m <= 59U; ++m)
    {
        DateTimeMs dt(Date(), TimeMs(0U, m, 2U, 3U));
        CHECK_EQUAL(dt.GetMinutes(), m);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetMinutes, NA)
{
    for (DateTimeNs::minute_type m = 0; m <= 59U; ++m)
    {
        DateTimeNs dt(Date(), TimeNs(0U, m, 2U, 3U));
        CHECK_EQUAL(dt.GetMinutes(), m);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, SetMinutes, minute_type)
{
    DateTimeMs dt;
    for (DateTimeMs::minute_type m = 0; m <= 59U; ++m)
    {
        dt.SetMinutes(m);
        CHECK_EQUAL(dt.GetMinutes(), m);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, SetMinutes, minute_type)
{
    DateTimeNs dt;
    for (DateTimeNs::minute_type m = 0; m <= 59U; ++m)
    {
        dt.SetMinutes(m);
        CHECK_EQUAL(dt.GetMinutes(), m);
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, GetHours, NA)
{
    for (DateTimeMs::hour_type h = 0; h <= 23U; ++h)
    {
        DateTimeMs dt(Date(), TimeMs(h, 1U, 2U, 3U));
        CHECK_EQUAL(dt.GetHours(), h);
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, GetHours, NA)
{
    for (DateTimeNs::hour_type h = 0; h <= 23U; ++h)
    {
        DateTimeNs dt(Date(), TimeNs(h, 1U, 2U, 3U));
        CHECK_EQUAL(dt.GetHours(), h);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, SetHours, hour_type)
{
    DateTimeMs dt;
    for (DateTimeMs::hour_type h = 0; h <= 23U; ++h)
    {
        dt.SetHours(h);
        CHECK_EQUAL(dt.GetHours(), h);
    }
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, SetHours, hour_type)
{
    DateTimeNs dt;
    for (DateTimeNs::hour_type h = 0; h <= 23U; ++h)
    {
        dt.SetHours(h);
        CHECK_EQUAL(dt.GetHours(), h);
    }
}

// Macro for making testing of TimeNs easier.
#define HHMMSSNN2INT64(h, m, s, n) (static_cast<TimeNs::size_type>(n) | \
                                   (static_cast<TimeNs::size_type>(s) << 32UL) | \
                                   (static_cast<TimeNs::size_type>(m) << 40UL) | \
                                   (static_cast<TimeNs::size_type>(h) << 48UL))

TEST_MEMBER_FUNCTION(DateTimeMs, SerializeDate, NA)
{
    CHECK_EQUAL(DateTimeMs().SerializeDate(), 0x07b20101U);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 2000U), TimeMs()).SerializeDate(), 0x07d00201U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, SerializeDate, NA)
{
    CHECK_EQUAL(DateTimeNs().SerializeDate(), 0x07b20101U);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 2000U), TimeNs()).SerializeDate(), 0x07d00201U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, DeserializeDate, uint32_t)
{
    DateTimeMs dt;

    dt.DeserializeDate(0x07b20101U);
    CHECK_EQUAL(dt.SerializeDate(), 0x07b20101U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);
    CHECK_EQUAL(dt.GetYear(), 1970U);

    dt.DeserializeDate(0x07d00201U);
    CHECK_EQUAL(dt.SerializeDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, DeserializeDate, uint32_t)
{
    DateTimeNs dt;

    dt.DeserializeDate(0x07b20101U);
    CHECK_EQUAL(dt.SerializeDate(), 0x07b20101U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);
    CHECK_EQUAL(dt.GetYear(), 1970U);

    dt.DeserializeDate(0x07d00201U);
    CHECK_EQUAL(dt.SerializeDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
}

// Macro for making testing of TimeNs easier.
#define HHMMSSNN2INT64(h, m, s, n) (static_cast<TimeNs::size_type>(n) | \
                                   (static_cast<TimeNs::size_type>(s) << 32UL) | \
                                   (static_cast<TimeNs::size_type>(m) << 40UL) | \
                                   (static_cast<TimeNs::size_type>(h) << 48UL))

TEST_MEMBER_FUNCTION(DateTimeMs, SerializeTime, NA)
{
    DateTimeMs dt1(Date(), TimeMs(0U, 0U, 0U, 0U));
    DateTimeMs dt2(Date(), TimeMs(1U, 2U, 3U, 4U));
    DateTimeMs dt3(Date(), TimeMs(23U, 59U, 59U, 999U));

    CHECK_EQUAL(dt1.SerializeTime(), 0U);
    CHECK_EQUAL(dt2.SerializeTime(), 0x01020c04u);
    CHECK_EQUAL(dt3.SerializeTime(), 0x173befe7u);
}

TEST_MEMBER_FUNCTION(DateTimeNs, SerializeTime, NA)
{
    DateTimeNs dt1(Date(), TimeNs(0U, 0U, 0U, 0U));
    DateTimeNs dt2(Date(), TimeNs(1U, 2U, 3U, 4U));
    DateTimeNs dt3(Date(), TimeNs(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));

    CHECK_EQUAL(dt1.SerializeTime(), 0U);
    CHECK_EQUAL(dt2.SerializeTime(), HHMMSSNN2INT64(1U, 2U, 3U, 4U));
    CHECK_EQUAL(dt3.SerializeTime(), HHMMSSNN2INT64(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
}

TEST_CONST_MEMBER_FUNCTION(DateTimeMs, DeserializeTime, uint32_t)
{
    DateTimeMs dt;

    dt.DeserializeTime(0U);
    CHECK_EQUAL(dt.SerializeTime(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);

    dt.DeserializeTime(0x01020c04u);
    CHECK_EQUAL(dt.SerializeTime(), 0x01020c04u);
    CHECK_EQUAL(dt.GetMilliseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);

    dt.DeserializeTime(0x173befe7u);
    CHECK_EQUAL(dt.SerializeTime(), 0x173befe7u);
    CHECK_EQUAL(dt.GetMilliseconds(), 999U);
    CHECK_EQUAL(dt.GetSeconds(), 59U);
    CHECK_EQUAL(dt.GetMinutes(), 59U);
    CHECK_EQUAL(dt.GetHours(), 23U);
}

TEST_CONST_MEMBER_FUNCTION(DateTimeNs, DeserializeTime, uint64_t)
{
    DateTimeNs dt;

    dt.DeserializeTime(0U);
    CHECK_EQUAL(dt.SerializeTime(), 0U);
    CHECK_EQUAL(dt.GetNanoseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);

    dt.DeserializeTime(HHMMSSNN2INT64(1U, 2U, 3U, 4U));
    CHECK_EQUAL(dt.SerializeTime(), HHMMSSNN2INT64(1U, 2U, 3U, 4U));
    CHECK_EQUAL(dt.GetNanoseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);

    dt.DeserializeTime(HHMMSSNN2INT64(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(dt.SerializeTime(), HHMMSSNN2INT64(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(dt.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(dt.GetSeconds(), 59U);
    CHECK_EQUAL(dt.GetMinutes(), 59U);
    CHECK_EQUAL(dt.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, Deserialize, uint32_t_uint32_t)
{
    TEST_OVERRIDE_ARGS("uint32_t, uint32_t");

    DateTimeMs dt;

    dt.Deserialize(0x07b20101U, 0U);
    CHECK_EQUAL(dt.SerializeDate(), 0x07b20101U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);
    CHECK_EQUAL(dt.GetYear(), 1970U);
    CHECK_EQUAL(dt.SerializeTime(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);

    dt.Deserialize(0x07d00201U, 0x01020c04u);
    CHECK_EQUAL(dt.SerializeDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
    CHECK_EQUAL(dt.SerializeTime(), 0x01020c04u);
    CHECK_EQUAL(dt.GetMilliseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);

    dt.Deserialize(0x07d00201U, 0x173befe7u);
    CHECK_EQUAL(dt.SerializeDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
    CHECK_EQUAL(dt.SerializeTime(), 0x173befe7u);
    CHECK_EQUAL(dt.GetMilliseconds(), 999U);
    CHECK_EQUAL(dt.GetSeconds(), 59U);
    CHECK_EQUAL(dt.GetMinutes(), 59U);
    CHECK_EQUAL(dt.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, Deserialize, uint32_t_uint64_t)
{
    TEST_OVERRIDE_ARGS("uint32_t, uint64_t");

    DateTimeNs dt;

    dt.Deserialize(0x07b20101U, 0UL);
    CHECK_EQUAL(dt.SerializeDate(), 0x07b20101U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 1U);
    CHECK_EQUAL(dt.GetYear(), 1970U);
    CHECK_EQUAL(dt.SerializeTime(), 0U);
    CHECK_EQUAL(dt.GetMilliseconds(), 0U);
    CHECK_EQUAL(dt.GetSeconds(), 0U);
    CHECK_EQUAL(dt.GetMinutes(), 0U);
    CHECK_EQUAL(dt.GetHours(), 0U);

    dt.Deserialize(0x07d00201U, HHMMSSNN2INT64(1U, 2U, 3U, 4U));
    CHECK_EQUAL(dt.SerializeDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
    CHECK_EQUAL(dt.SerializeTime(), HHMMSSNN2INT64(1U, 2U, 3U, 4U));
    CHECK_EQUAL(dt.GetNanoseconds(), 4U);
    CHECK_EQUAL(dt.GetSeconds(), 3U);
    CHECK_EQUAL(dt.GetMinutes(), 2U);
    CHECK_EQUAL(dt.GetHours(), 1U);

    dt.Deserialize(0x07d00201U, HHMMSSNN2INT64(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(dt.SerializeDate(), 0x07d00201U);
    CHECK_EQUAL(dt.GetDay(), 1U);
    CHECK_EQUAL(dt.GetMonth(), 2U);
    CHECK_EQUAL(dt.GetYear(), 2000U);
    CHECK_EQUAL(dt.SerializeTime(), HHMMSSNN2INT64(23U, 59U, 59U, TimeNs::NANOSECONDS_PER_SECOND - 1UL));
    CHECK_EQUAL(dt.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(dt.GetSeconds(), 59U);
    CHECK_EQUAL(dt.GetMinutes(), 59U);
    CHECK_EQUAL(dt.GetHours(), 23U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, AddDays, size_type)
{
    DateTimeMs date_time;

    Date::size_type days_in_leap_year = Date::GetDaysInYear(2000U);
    Date::size_type days_in_year = Date::GetDaysInYear(2001U);

    for (DateTimeMs::year_type year = 2000U; year <= 2001U; ++year)
    {
        for (DateTimeMs::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            DateTimeMs::day_type days_in_month = Date::GetDaysInMonth(month, year);

            // Test adding 0 days to every day in the month has no effect.
            for (DateTimeMs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                date_time.AddDays(0U);
                CHECK_EQUAL(date_time.GetDay(), day);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test offsetting days for a complete year wraps correctly to next day, month and year.
            for (DateTimeMs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                bool need_leap_days = (year == 2000U) && (month <= Date::FEBRUARY);
                DateTimeMs::date_size_type days_to_next_year = need_leap_days ? days_in_leap_year : days_in_year;
                date_time.AddDays(days_to_next_year);
                CHECK_EQUAL(date_time, DateTimeMs(day, month, year + 1U, 0U, 0U, 0U, 0U));
            }

            // Test adding a single day to every day except last day
            // sets correct day and doesn't wrap month.
            for (DateTimeMs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                date_time.AddDays(1U);
                CHECK_EQUAL(date_time.GetDay(), day + 1U);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test adding number of days to reach last day doesn't overflow the month,
            // and sets the day to the last day of the month.
            for (DateTimeMs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDay(day);
                date_time.AddDays(days_in_month - day);
                CHECK_EQUAL(date_time.GetDay(), days_in_month);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test adding days in the month wraps to the start of the following month.
            date_time.SetDate(1U, month, year);
            date_time.AddDays(days_in_month);
            CHECK_EQUAL(date_time.GetDay(), 1U);
            Date::month_type next_month = Date::GetNextMonth(month);
            CHECK_EQUAL(date_time.GetMonth(), next_month);
            Date::year_type expected_year = month < Date::DECEMBER ? year : year + 1U;
            CHECK_EQUAL(date_time.GetYear(), expected_year);
        }
    }
}

TEST_MEMBER_FUNCTION(DateTimeNs, AddDays, size_type)
{
    DateTimeNs date_time;

    Date::size_type days_in_leap_year = Date::GetDaysInYear(2000U);
    Date::size_type days_in_year = Date::GetDaysInYear(2001U);

    for (DateTimeNs::year_type year = 2000U; year <= 2001U; ++year)
    {
        for (DateTimeNs::month_type month = Date::JANUARY; month <= Date::DECEMBER; ++month)
        {
            DateTimeNs::day_type days_in_month = Date::GetDaysInMonth(month, year);

            // Test adding 0 days to every day in the month has no effect.
            for (DateTimeNs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                date_time.AddDays(0U);
                CHECK_EQUAL(date_time.GetDay(), day);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test offsetting days for a complete year wraps correctly to next day, month and year.
            for (DateTimeNs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                bool need_leap_days = (year == 2000U) && (month <= Date::FEBRUARY);
                DateTimeNs::date_size_type days_to_next_year = need_leap_days ? days_in_leap_year : days_in_year;
                date_time.AddDays(days_to_next_year);
                CHECK_EQUAL(date_time, DateTimeNs(day, month, year + 1U, 0U, 0U, 0U, 0U));
            }

            // Test adding a single day to every day except last day
            // sets correct day and doesn't wrap month.
            for (DateTimeNs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDate(day, month, year);
                date_time.AddDays(1U);
                CHECK_EQUAL(date_time.GetDay(), day + 1U);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test adding number of days to reach last day doesn't overflow the month,
            // and sets the day to the last day of the month.
            for (DateTimeNs::day_type day = 1U; day < days_in_month; ++day)
            {
                date_time.SetDay(day);
                date_time.AddDays(days_in_month - day);
                CHECK_EQUAL(date_time.GetDay(), days_in_month);
                CHECK_EQUAL(date_time.GetMonth(), month);
                CHECK_EQUAL(date_time.GetYear(), year);
            }

            // Test adding days in the month wraps to the start of the following month.
            date_time.SetDate(1U, month, year);
            date_time.AddDays(days_in_month);
            CHECK_EQUAL(date_time.GetDay(), 1U);
            Date::month_type next_month = Date::GetNextMonth(month);
            CHECK_EQUAL(date_time.GetMonth(), next_month);
            Date::year_type expected_year = month < Date::DECEMBER ? year : year + 1U;
            CHECK_EQUAL(date_time.GetYear(), expected_year);
        }
    }
}

TEST_MEMBER_FUNCTION(DateTimeMs, Add, size_type)
{
    DateTimeMs date_time;
    date_time.SetDate(1U, Date::JANUARY, 1980U);

    // Test 0 millisecond to 1 millisecond.
    date_time.Add(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 1U);

    // Test 0 millisecond to 999 millisecond.
    date_time.SetStartTime();
    date_time.Add(999U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 999U);

    // Test 0 millisecond to 1 second.
    date_time.SetStartTime();
    date_time.Add(1000U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 1U);

    // Test 0 millisecond to 1 minute.
    date_time.SetStartTime();
    date_time.Add(TimeMs::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 1U);

    // Test 0 millisecond to 1 hour.
    date_time.SetStartTime();
    date_time.Add(TimeMs::MILLISECONDS_PER_HOUR);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 1U);

    // Test 0 millisecond to 1 day.
    date_time.SetStartTime();
    date_time.Add(TimeMs::MILLISECONDS_PER_DAY);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 2U);

    // Test 0 millisecond to 1 day, 23 hours, 59 minutes, 59 seconds, 999 milliseconds.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.Add((TimeMs::MILLISECONDS_PER_DAY * 2) - 1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 999U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), 2U);

    // Test 0 millisecond to 2 days.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.Add(TimeMs::MILLISECONDS_PER_DAY * 2);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 3U);

    // Test 0 millisecond to 2 days and 1 millisecond.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.Add((TimeMs::MILLISECONDS_PER_DAY * 2) + 1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 1U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 3U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, Add, size_type)
{
    DateTimeNs date_time;
    date_time.SetDate(1U, Date::JANUARY, 1980U);

    // Test 0 nanosecond to 1 nanoseconds.
    date_time.Add(1U);
    CHECK_EQUAL(date_time.GetNanoseconds(), 1U);

    // Test 0 nanosecond to 999999999 nanoseconds.
    date_time.SetStartTime();
    date_time.Add(TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(date_time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);

    // Test 0 nanoseconds to 1 second.
    date_time.SetStartTime();
    date_time.Add(TimeNs::NANOSECONDS_PER_SECOND);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 1U);

    // Test 0 nanoseconds to 1 minute.
    date_time.SetStartTime();
    date_time.Add(TimeMs::NANOSECONDS_PER_MINUTE);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 1U);

    // Test 0 nanoseconds to 1 hour.
    date_time.SetStartTime();
    date_time.Add(TimeMs::NANOSECONDS_PER_HOUR);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 1U);

    // Test 0 nanoseconds to 1 day.
    date_time.SetStartTime();
    date_time.Add(TimeMs::NANOSECONDS_PER_DAY);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 2U);

    // Test 0 nanosecond to 1 day, 23 hours, 59 minutes, 59 seconds, 999999999 nanoseconds.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.Add((TimeMs::NANOSECONDS_PER_DAY * 2) - 1U);
    CHECK_EQUAL(date_time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), 2U);

    // Test 0 nanoseconds to 2 days.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.Add(TimeMs::NANOSECONDS_PER_DAY * 2);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 3U);

    // Test 0 nanosecond to 2 days and 1 nanoseconds.
    date_time.SetStartTime();
    date_time.SetDay(1U);
    date_time.Add((TimeMs::NANOSECONDS_PER_DAY * 2) + 1U);
    CHECK_EQUAL(date_time.GetNanoseconds(), 1U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 3U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, Subtract, size_type)
{
    DateTimeMs date_time;
    date_time.SetDate(1U, Date::JANUARY, 1980U);

    // Test 999 milliseconds to 998 milliseconds.
    date_time.SetEndTime();
    date_time.Subtract(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 998U);

    // Test 999 milliseconds to 0 milliseconds.
    date_time.SetEndTime();
    date_time.Subtract(999U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);

    // Test 1 milliseconds to 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SetMilliseconds(1U);
    date_time.Subtract(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 1U);
    CHECK_EQUAL(date_time.GetMonth(), Date::JANUARY);
    CHECK_EQUAL(date_time.GetYear(), 1980U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 59 seconds and 999 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(1U);
    CHECK_EQUAL(date_time.GetMilliseconds(), 999U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 59 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::MILLISECONDS_PER_SECOND);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 0 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::MILLISECONDS_PER_MINUTE);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 23 hours, 0 minutes, 0 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::MILLISECONDS_PER_HOUR);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 milliseconds to 0 hours, 0 minutes, 0 seconds and 0 milliseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::MILLISECONDS_PER_DAY);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);
}

TEST_MEMBER_FUNCTION(DateTimeNs, Subtract, size_type)
{
    DateTimeNs date_time;
    date_time.SetDate(1U, Date::JANUARY, 1980U);

    // Test 999999999 nanoseconds to 999999998 nanoseconds.
    date_time.SetEndTime();
    date_time.Subtract(1U);
    CHECK_EQUAL(date_time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 2UL);

    // Test 999999999 nanoseconds to 0 nanoseconds.
    date_time.SetEndTime();
    date_time.Subtract(TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);

    // Test 1 nanoseconds to 0 nanoseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.SetNanoseconds(1U);
    date_time.Subtract(1U);
    CHECK_EQUAL(date_time.GetNanoseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetDay(), 1U);
    CHECK_EQUAL(date_time.GetMonth(), Date::JANUARY);
    CHECK_EQUAL(date_time.GetYear(), 1980U);

    // Test 0 milliseconds to 23 hours, 59 minutes, 59 seconds and 999999999 nanoseconds.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(1U);
    CHECK_EQUAL(date_time.GetNanoseconds(), TimeNs::NANOSECONDS_PER_SECOND - 1UL);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 nanosecond to 23 hours, 59 minutes, 59 seconds and 0 nanosecond.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::NANOSECONDS_PER_SECOND);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 59U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 nanosecond to 23 hours, 59 minutes, 0 seconds and 0 nanosecond.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::NANOSECONDS_PER_MINUTE);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 59U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 nanosecond to 23 hours, 0 minutes, 0 seconds and 0 nanosecond.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::NANOSECONDS_PER_HOUR);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 23U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);

    // Test 0 nanosecond to 0 hours, 0 minutes, 0 seconds and 0 nanosecond.
    date_time.SetDate(1U, Date::JANUARY, 1980U);
    date_time.SetStartTime();
    date_time.Subtract(TimeMs::NANOSECONDS_PER_DAY);
    CHECK_EQUAL(date_time.GetMilliseconds(), 0U);
    CHECK_EQUAL(date_time.GetSeconds(), 0U);
    CHECK_EQUAL(date_time.GetMinutes(), 0U);
    CHECK_EQUAL(date_time.GetHours(), 0U);
    CHECK_EQUAL(date_time.GetDay(), Date::DAYS_IN_DECEMBER);
    CHECK_EQUAL(date_time.GetMonth(), Date::DECEMBER);
    CHECK_EQUAL(date_time.GetYear(), 1979U);
}

TEST_MEMBER_FUNCTION(DateTimeMs, Swap, DateTime_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs&");

    DateTimeMs date_time1(Date(1U, Date::FEBRUARY, 1980U), TimeMs(1U, 2U, 3U, 4U));
    DateTimeMs date_time2(Date(3U, Date::APRIL, 2000U), TimeMs(5U, 6U, 7U, 8U));

    date_time1.Swap(date_time2);
    CHECK_EQUAL(date_time1, DateTimeMs(Date(3U, Date::APRIL, 2000U), TimeMs(5U, 6U, 7U, 8U)));
    CHECK_EQUAL(date_time2, DateTimeMs(Date(1U, Date::FEBRUARY, 1980U), TimeMs(1U, 2U, 3U, 4U)));
}

TEST_MEMBER_FUNCTION(DateTimeNs, Swap, DateTime_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs&");

    DateTimeNs date_time1(Date(1U, Date::FEBRUARY, 1980U), TimeNs(1U, 2U, 3U, 4U));
    DateTimeNs date_time2(Date(3U, Date::APRIL, 2000U), TimeNs(5U, 6U, 7U, 8U));

    date_time1.Swap(date_time2);
    CHECK_EQUAL(date_time1, DateTimeNs(Date(3U, Date::APRIL, 2000U), TimeNs(5U, 6U, 7U, 8U)));
    CHECK_EQUAL(date_time2, DateTimeNs(Date(1U, Date::FEBRUARY, 1980U), TimeNs(1U, 2U, 3U, 4U)));
}

TEST_MEMBER_FUNCTION(DateTimeMs, Compare, DateTime_const_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs const&");

    // Compare date and time differences.
    CHECK_EQUAL(DateTimeMs().Compare(DateTimeMs()), 0);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 0);
    CHECK_EQUAL(DateTimeMs(Date(1U, 1U, 1980U), TimeMs(1U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1979U), TimeMs(1U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(0U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 1U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 2U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 3U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(2U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 3U, 1980U), TimeMs(1U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1981U), TimeMs(1U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(2U, 2U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 3U, 3U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 4U, 4U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 5U)).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs(1U, 2U, 3U, 4U))), 1);

    // Compare only date differences.
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs()).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs())), 0);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1980U), TimeMs()).Compare(DateTimeMs(Date(2U, 2U, 1980U), TimeMs())), -1);
    CHECK_EQUAL(DateTimeMs(Date(2U, 1U, 1980U), TimeMs()).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs())), -1);
    CHECK_EQUAL(DateTimeMs(Date(3U, 2U, 1979U), TimeMs()).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs())), -1);
    CHECK_EQUAL(DateTimeMs(Date(2U, 2U, 1980U), TimeMs()).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs())), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 3U, 1980U), TimeMs()).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs())), 1);
    CHECK_EQUAL(DateTimeMs(Date(1U, 2U, 1981U), TimeMs()).Compare(DateTimeMs(Date(1U, 2U, 1980U), TimeMs())), 1);

    // Compare only time differences.
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 0U, 0U, 0U)).Compare(DateTimeMs(Date(), TimeMs(0U, 0U, 0U, 0U))), 0);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(1U, 0U, 0U, 0U)).Compare(DateTimeMs(Date(), TimeMs(2U, 0U, 0U, 0U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 1U, 0U, 0U)).Compare(DateTimeMs(Date(), TimeMs(0U, 2U, 0U, 0U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 0U, 1U, 0U)).Compare(DateTimeMs(Date(), TimeMs(0U, 0U, 2U, 0U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 0U, 0U, 1U)).Compare(DateTimeMs(Date(), TimeMs(0U, 0U, 0U, 2U))), -1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(2U, 0U, 0U, 0U)).Compare(DateTimeMs(Date(), TimeMs(1U, 0U, 0U, 0U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 2U, 0U, 0U)).Compare(DateTimeMs(Date(), TimeMs(0U, 1U, 0U, 0U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 0U, 2U, 0U)).Compare(DateTimeMs(Date(), TimeMs(0U, 0U, 1U, 0U))), 1);
    CHECK_EQUAL(DateTimeMs(Date(), TimeMs(0U, 0U, 0U, 2U)).Compare(DateTimeMs(Date(), TimeMs(0U, 0U, 0U, 1U))), 1);
}

TEST_MEMBER_FUNCTION(DateTimeNs, Compare, DateTime_const_ref)
{
    TEST_OVERRIDE_ARGS("DateTimeMs const&");

    // Compare date and time differences.
    CHECK_EQUAL(DateTimeNs().Compare(DateTimeNs()), 0);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 0);
    CHECK_EQUAL(DateTimeNs(Date(1U, 1U, 1980U), TimeNs(1U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1979U), TimeNs(1U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(0U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 1U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 2U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 3U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(2U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 3U, 1980U), TimeNs(1U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1981U), TimeNs(1U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(2U, 2U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 3U, 3U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 4U, 4U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 5U)).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs(1U, 2U, 3U, 4U))), 1);

    // Compare only date differences.
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs()).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs())), 0);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1980U), TimeNs()).Compare(DateTimeNs(Date(2U, 2U, 1980U), TimeNs())), -1);
    CHECK_EQUAL(DateTimeNs(Date(2U, 1U, 1980U), TimeNs()).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs())), -1);
    CHECK_EQUAL(DateTimeNs(Date(3U, 2U, 1979U), TimeNs()).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs())), -1);
    CHECK_EQUAL(DateTimeNs(Date(2U, 2U, 1980U), TimeNs()).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs())), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 3U, 1980U), TimeNs()).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs())), 1);
    CHECK_EQUAL(DateTimeNs(Date(1U, 2U, 1981U), TimeNs()).Compare(DateTimeNs(Date(1U, 2U, 1980U), TimeNs())), 1);

    // Compare only time differences.
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 0U, 0U, 0U)).Compare(DateTimeNs(Date(), TimeNs(0U, 0U, 0U, 0U))), 0);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(1U, 0U, 0U, 0U)).Compare(DateTimeNs(Date(), TimeNs(2U, 0U, 0U, 0U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 1U, 0U, 0U)).Compare(DateTimeNs(Date(), TimeNs(0U, 2U, 0U, 0U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 0U, 1U, 0U)).Compare(DateTimeNs(Date(), TimeNs(0U, 0U, 2U, 0U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 0U, 0U, 1U)).Compare(DateTimeNs(Date(), TimeNs(0U, 0U, 0U, 2U))), -1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(2U, 0U, 0U, 0U)).Compare(DateTimeNs(Date(), TimeNs(1U, 0U, 0U, 0U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 2U, 0U, 0U)).Compare(DateTimeNs(Date(), TimeNs(0U, 1U, 0U, 0U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 0U, 2U, 0U)).Compare(DateTimeNs(Date(), TimeNs(0U, 0U, 1U, 0U))), 1);
    CHECK_EQUAL(DateTimeNs(Date(), TimeNs(0U, 0U, 0U, 2U)).Compare(DateTimeNs(Date(), TimeNs(0U, 0U, 0U, 1U))), 1);
}
