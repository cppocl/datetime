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

#ifndef OCL_GUARD_DATETIME_TIMEZONE_HPP
#define OCL_GUARD_DATETIME_TIMEZONE_HPP

namespace ocl
{

class TimeZone
{
// Enumerations.
public:
    enum Zones
    {
        Local,
        GMT    // Greenwich Mean Time
    };

// Overloaded operators.
public:
    operator Zones() const throw()
    {
        return m_zone;
    }

// Constructors.
public:
    TimeZone(Zones zone = GMT) throw()
        : m_zone(zone)
    {
    }

    TimeZone(TimeZone const& zone) throw()
        : m_zone(zone.m_zone)
    {
    }

// Data (internal use only)
private:
    Zones m_zone;
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_TIMEZONE_HPP
