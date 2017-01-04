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
#include "../TimeFunction.hpp"
#include <string.h>

/*
Test timing functions, member functions and const member functions with or without a return.
*/

namespace
{

using ocl::TimeFunction;

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

// Test const member function with return value, with and without args.
TEST_CONST_MEMBER_FUNCTION(TimeFunction, Call, int_ref_unsigned_long_TestClass_const_ref_func_const_varargs)
{
    TEST_OVERRIDE_ARGS("int&, unsigned long, TestClass const&, int (class_type::*func)(varargs...) const, varargs...");

    typedef TimeFunction<> time_function;
    typedef typename time_function::time_type time_type;

    int ret = 0;

    LocalTestClass const test;

    time_type elapsed_ticks = time_function::Call(ret, 1000U, test, &LocalTestClass::LenTest);
    CHECK_EQUAL(ret, 5);
    CHECK_TRUE(elapsed_ticks >= 0U);

    elapsed_ticks = time_function::Call(ret, 1000U, test, &LocalTestClass::LenTest, "Hello", "Goodbye");
    CHECK_EQUAL(ret, 12);
    CHECK_TRUE(elapsed_ticks >= 0U);
}

// Test const member function with return value, with and without args.
TEST_MEMBER_FUNCTION(TimeFunction, Call, int_ref_unsigned_long_TestClass_ref_func_varargs)
{
    TEST_OVERRIDE_ARGS("int&, unsigned long, TestClass&, int (class_type::*func)(varargs...), varargs...");

    typedef TimeFunction<> time_function;
    typedef typename time_function::time_type time_type;

    int ret = 0;

    LocalTestClass test;

    time_type elapsed_ticks = time_function::Call(ret, 1000U, test, &LocalTestClass::LenTest);
    CHECK_EQUAL(ret, 5);
    CHECK_TRUE(elapsed_ticks >= 0U);

    elapsed_ticks = time_function::Call(ret, 1000U, test, &LocalTestClass::LenTest, "Hello", "Goodbye");
    CHECK_EQUAL(ret, 12);
    CHECK_TRUE(elapsed_ticks >= 0U);
}

// Test const member function without return value, with and without args.
TEST_CONST_MEMBER_FUNCTION(TimeFunction, Call, void_unsigned_long_TestClass_const_ref_func_const_varargs)
{
    TEST_OVERRIDE_ARGS("void, unsigned long, TestClass const&, void (class_type::*func)(varargs...) const, varargs...");

    typedef TimeFunction<> time_function;
    typedef typename time_function::time_type time_type;

    LocalTestClass const test;

    time_type elapsed_ticks = time_function::Call(1000U, test, &LocalTestClass::NoRetTest);
    CHECK_EQUAL(test.Length(), 5);
    CHECK_TRUE(elapsed_ticks >= 0U);

    elapsed_ticks = time_function::Call(1000U, test, &LocalTestClass::NoRetTest, "Hello", "Goodbye");
    CHECK_EQUAL(test.Length(), 12);
    CHECK_TRUE(elapsed_ticks >= 0U);
}

// Test member function without return value, with and without args.
TEST_MEMBER_FUNCTION(TimeFunction, Call, void_unsigned_long_TestClass_ref_func_varargs)
{
    TEST_OVERRIDE_ARGS("void, unsigned long, TestClass&, void (class_type::*func)(varargs...), varargs...");

    typedef TimeFunction<> time_function;
    typedef typename time_function::time_type time_type;

    LocalTestClass test;

    time_type elapsed_ticks = time_function::Call(1000U, test, &LocalTestClass::NoRetTest);
    CHECK_EQUAL(test.Length(), 5);
    CHECK_TRUE(elapsed_ticks >= 0U);

    elapsed_ticks = time_function::Call(1000U, test, &LocalTestClass::NoRetTest, "Hello", "Goodbye");
    CHECK_EQUAL(test.Length(), 12);
    CHECK_TRUE(elapsed_ticks >= 0U);
}

// Test function with return value, with and without args.
TEST_MEMBER_FUNCTION(TimeFunction, Call, int_ref_unsigned_long_func_varargs)
{
    TEST_OVERRIDE_ARGS("int&, unsigned long, int (::*func)(varargs...), varargs...");

    typedef TimeFunction<> time_function;
    typedef typename time_function::time_type time_type;

    int ret = 0;

    time_type elapsed_ticks = time_function::Call(ret, 1000U, &LenTest);
    CHECK_EQUAL(ret, 5);
    CHECK_TRUE(elapsed_ticks >= 0U);

    elapsed_ticks = time_function::Call(ret, 1000U, &LenTest, "Hello", "Goodbye");
    CHECK_EQUAL(ret, 12);
    CHECK_TRUE(elapsed_ticks >= 0U);
}

// Test function without return value, with and without args.
TEST_MEMBER_FUNCTION(TimeFunction, Call, void_ref_unsigned_long_func_varargs)
{
    TEST_OVERRIDE_ARGS("unsigned long, int (::*func)(varargs...), varargs...");

    typedef TimeFunction<> time_function;
    typedef typename time_function::time_type time_type;

    time_type elapsed_ticks = time_function::Call(1000U, &NoRetTest);
    CHECK_EQUAL(str_len, 5);
    CHECK_TRUE(elapsed_ticks >= 0U);

    elapsed_ticks = time_function::Call(1000U, &NoRetTest, "Hello", "Goodbye");
    CHECK_EQUAL(str_len, 12);
    CHECK_TRUE(elapsed_ticks >= 0U);
}

} // namespace

