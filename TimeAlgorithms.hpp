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

#ifndef OCL_GUARD_DATETIME_TIMEALGORITHMS_HPP
#define OCL_GUARD_DATETIME_TIMEALGORITHMS_HPP

namespace ocl
{

class TimeAlgorithms
{
public:
    // Calculate the number of times a function would need to be called to
    // reach the total duration.
    // If this cannot be calculated from the sample duration or sample count,
    // then provide a count that can be used as a starting point.
    template<typename count_type, typename time_type>
    static count_type CalculateTotalCount(time_type total_duration,
                                          time_type sample_duration,
                                          count_type count_for_sample)
    {
        count_type count;
        if (total_duration > 0)
        {
            if (count_for_sample > 0)
            {
                // There was a sample count for a sample duration, so estimate
                // the complete count for the complete duration required.

                if (sample_duration > 0)
                {
                    // The sample duration has a value that can be used with the sample count,
                    // so estimate what the total count would be.
                    count = (count_for_sample * static_cast<count_type>(total_duration)) /
                        static_cast<count_type>(sample_duration);
                }
                else
                {
                    // The current sample count was not enough to time a function call,
                    // so we know multiplying the count for the number of times the
                    // function is called won't exceed the total required duration.
                    count = count_for_sample * static_cast<count_type>(total_duration);
                }
            }
            else
                count = 1; // When sample count is 0, try timing a function call once initially.
        }
        else
            count = 0; // Cannot calculate a count without a required duration!

        return count;
    }

    // Calculate the number of times a function would need to be called to
    // reach the total duration.
    // If this cannot be calculated from the sample duration or sample count,
    // then provide a count that can be used as a starting point.
    // When the current duration is greater than 0, provide the count for the
    // remaining duration (i.e. total duration - current duration).
    template<typename count_type, typename time_type>
    static count_type CalculateTotalCount(time_type total_duration,
                                          time_type current_duration_to_exclude,
                                          time_type sample_duration,
                                          count_type count_for_sample)
    {
        count_type count;
        if (total_duration > 0)
        {
            if (count_for_sample > 0)
            {
                // There was a sample count for a sample duration, so estimate
                // the complete count for the complete duration required.

                if (sample_duration > 0)
                {
                    // The sample duration has a value that can be used with the sample count,
                    // so estimate what the total count would be.
                    count = (count_for_sample * static_cast<count_type>(total_duration)) /
                        static_cast<count_type>(sample_duration);

                    if (current_duration_to_exclude > 0)
                    {
                        // When we already have a current duration for timed calls,
                        // adjust count to exclude the currently timed function calls.
                        // i.e. The count that will time only total_duration - current_duration.
                        count -= (count * static_cast<count_type>(current_duration_to_exclude)) /
                            static_cast<count_type>(total_duration);
                    }
                }
                else
                {
                    // The current sample count was not enough to time a function call,
                    // so we know multiplying the count for the number of times the
                    // function is called won't exceed the total required duration.
                    count = count_for_sample * static_cast<count_type>(total_duration);
                }
            }
            else
                count = 1; // When sample count is 0, try timing a function call once initially.
        }
        else
            count = 0; // Cannot calculate a count without a required duration!

        return count;
    }

    template<typename count_type, typename time_type>
    static double CalculateCallTimeInSeconds(count_type count,
                                             time_type duration_in_milliseconds)
    {
        // Calculate the time it takes to make a single call,
        // based on a count and duration in seconds.
        double call_time_in_seconds = ((double)duration_in_milliseconds / count) / (double)1000.0;
        return call_time_in_seconds;
    }

    template<typename count_type, typename time_type>
    static double CalculateCallTimeInMilliseconds(count_type count,
                                                  time_type duration_in_milliseconds)
    {
        // Calculate the time it takes to make a single call,
        // based on a count and duration in milliseconds.
        double call_time_in_milliseconds = (double)duration_in_milliseconds / count;
        return call_time_in_milliseconds;
    }
};

} // namespace ocl

#endif // OCL_GUARD_DATETIME_TIMEALGORITHMS_HPP
