/*
Copyright 2017 Colin Girling

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

#ifndef OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEPRECISIONTYPE_HPP
#define OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEPRECISIONTYPE_HPP

#include "internalTimeMs.hpp"
#include "internalTimeNs.hpp"
#include "TimePrecision.hpp"

namespace ocl
{

/// Implement easy way of mapping enum to type for Time class.
template<TimePrecision const time_precision>
struct InternalTimePrecisionType;

template<>
struct InternalTimePrecisionType<Milliseconds>
{
    typedef InternalTimeMs precision_time_type;
};

template<>
struct InternalTimePrecisionType<Nanoseconds>
{
    typedef InternalTimeNs precision_time_type;
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_INTERNAL_INTERNALTIMEPRECISIONTYPE_HPP
