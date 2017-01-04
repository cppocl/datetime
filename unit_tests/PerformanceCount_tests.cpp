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
#include "../PerformanceCount.hpp"

namespace
{

using ocl::PerformanceCount;

static int str_len = 0;

static void NoRetTest()
{
    char str[100];
    strcpy(str, "A");
    strcat(str, "B");
    strcat(str, "C");
    strcat(str, "D");
    strcat(str, "E");
    str_len = static_cast<int>(strlen(str));
}

static void NoRetTest(char const* str1, char const* str2)
{
    char* str = new char[strlen(str1) + strlen(str2) + 1];
    strcpy(str, str1);
    strcat(str, str2);
    str_len = static_cast<int>(strlen(str));
    delete[] str;
}

static int LenTest()
{
    char str[100];
    strcpy(str, "A");
    strcat(str, "B");
    strcat(str, "C");
    strcat(str, "D");
    strcat(str, "E");
    return static_cast<int>(strlen(str));
}

static int LenTest(char const* str1, char const* str2)
{
    char* str = new char[strlen(str1) + strlen(str2) + 1];
    strcpy(str, str1);
    strcat(str, str2);
    int len = static_cast<int>(strlen(str));
    delete[] str;
    return len;
}

class LocalTestClass
{
public:
    LocalTestClass() throw()
        : m_len(0)
    {
    }

    int LenTest()
    {
        return ::LenTest();
    }

    int LenTest() const
    {
        return ::LenTest();
    }

    int LenTest(char const* str1, char const* str2)
    {
        return ::LenTest(str1, str2);
    }

    int LenTest(char const* str1, char const* str2) const
    {
        return ::LenTest(str1, str2);
    }

    void NoRetTest()
    {
        m_len = ::LenTest();
    }

    void NoRetTest() const
    {
        m_len = ::LenTest();
    }

    void NoRetTest(char const* str1, char const* str2)
    {
        m_len = ::LenTest(str1, str2);
    }

    void NoRetTest(char const* str1, char const* str2) const
    {
        m_len = ::LenTest(str1, str2);
    }

    int Length() const throw()
    {
        return m_len;
    }

private:
    mutable int m_len;
};

TEST_MEMBER_FUNCTION(PerformanceCount, Call, unsigned_long_long_ref_clock_t_ref_int_ref_LocalTestClass_ref_func_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long long&, clock_t&, int&, LocalTestClass&, int (class_type::*func)(varargs...), varargs...");

    typedef PerformanceCount<> performance_count;
    typedef typename performance_count::time_type time_type;

    unsigned long long count = 0ULL;
    time_type duration_ticks = 5U;
    int return_value = 0;
    LocalTestClass obj;

    performance_count::Call(count, duration_ticks, return_value, obj, &LocalTestClass::LenTest);
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(return_value, 5);

    performance_count::Call(count, duration_ticks, return_value, obj, &LocalTestClass::LenTest, "Hello", "Goodbye");
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(return_value, 12);
}

TEST_MEMBER_FUNCTION(PerformanceCount, Call, unsigned_long_long_ref_clock_t_ref_LocalTestClass_ref_func_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long long&, clock_t&, LocalTestClass&, void (class_type::*func)(varargs...), varargs...");

    typedef PerformanceCount<> performance_count;
    typedef typename performance_count::time_type time_type;

    unsigned long long count = 0ULL;
    time_type duration_ticks = 5U;
    LocalTestClass obj;

    performance_count::Call(count, duration_ticks, obj, &LocalTestClass::NoRetTest);
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(obj.Length(), 5);

    performance_count::Call(count, duration_ticks, obj, &LocalTestClass::NoRetTest, "Hello", "Goodbye");
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(obj.Length(), 12);
}

TEST_CONST_MEMBER_FUNCTION(PerformanceCount, Call, unsigned_long_long_ref_clock_t_ref_int_ref_LocalTestClass_const_ref_func_const_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long long&, clock_t&, int&, LocalTestClass const&, int (class_type::*func)(varargs...) const, varargs...");

    typedef PerformanceCount<> performance_count;
    typedef typename performance_count::time_type time_type;

    unsigned long long count = 0ULL;
    time_type duration_ticks = 5U;
    int return_value = 0;
    LocalTestClass const obj;

    performance_count::Call(count, duration_ticks, return_value, obj, &LocalTestClass::LenTest);
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(return_value, 5);

    performance_count::Call(count, duration_ticks, return_value, obj, &LocalTestClass::LenTest, "Hello", "Goodbye");
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(return_value, 12);
}

TEST_CONST_MEMBER_FUNCTION(PerformanceCount, Call, unsigned_long_long_ref_clock_t_ref_LocalTestClass_const_ref_func_const_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long long&, clock_t&, LocalTestClass const&, void (class_type::*func)(varargs...) const, varargs...");

    typedef PerformanceCount<> performance_count;
    typedef typename performance_count::time_type time_type;

    unsigned long long count = 0ULL;
    time_type duration_ticks = 5U;
    LocalTestClass const obj;

    performance_count::Call(count, duration_ticks, obj, &LocalTestClass::NoRetTest);
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(obj.Length(), 5);

    performance_count::Call(count, duration_ticks, obj, &LocalTestClass::NoRetTest, "Hello", "Goodbye");
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(obj.Length(), 12);
}

TEST_MEMBER_FUNCTION(PerformanceCount, Call, unsigned_long_long_ref_clock_t_ref_int_ref_func_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long long&, clock_t&, int&, int (*func)(varargs...), varargs...");

    typedef PerformanceCount<> performance_count;
    typedef typename performance_count::time_type time_type;

    unsigned long long count = 0ULL;
    time_type duration_ticks = 5U;
    int return_value = 0;

    performance_count::Call(count, duration_ticks, return_value, &LenTest);
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(return_value, 5);

    performance_count::Call(count, duration_ticks, return_value, &LenTest, "Hello", "Goodbye");
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(return_value, 12);
}

TEST_MEMBER_FUNCTION(PerformanceCount, Call, unsigned_long_long_ref_clock_t_ref_func_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long long&, clock_t&, void (*func)(varargs...), varargs...");

    typedef PerformanceCount<> performance_count;
    typedef typename performance_count::time_type time_type;

    unsigned long long count = 0ULL;
    time_type duration_ticks = 5U;

    performance_count::Call(count, duration_ticks, &NoRetTest);
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(str_len, 5);

    performance_count::Call(count, duration_ticks, &NoRetTest, "Hello", "Goodbye");
    CHECK_TRUE(count > 0ULL);
    CHECK_EQUAL(str_len, 12);
}

} // namespace
