//
// Created by Michael Lynch on 21/06/2021.
//

#ifndef LIBTR_LANG_SCOPEDTIMER_HPP
#define LIBTR_LANG_SCOPEDTIMER_HPP

#include <iostream>
#include <chrono>
#include <string>
#include <cstring>
#include <vector>


/**
 * Use this macro to define the names of all the timer groups that are to be used within the application.
 */
#define TRL_TIMER_GROUP(group_names...) namespace trl { enum class timer_group { group_names }; } \
    template <class T> const std::string trl::ScopedTimer<T>::merged_timer_group_names(#group_names);

namespace trl
{

    enum class timer_group;

    /**
     * Example Usage:
     *
     * In order to use the scoped timer you must first define the timer groups using the
     * TRL_TIMER_GROUP macro.
     *
     * ```
     * ScopedTimer::initTimers();
     * {
     *     ScopedTimer t(trl::timer_group::A)
     *     std::cout << "Hello World!" << std::endl;
     * }
     *
     * ScopedTimer::printInfo();
     * ```
     *
     */
    template <class T = int>
    class ScopedTimer
    {
    private:
        inline static std::vector<std::string> timer_group_names{};
        inline static long* groupTotalTime;
        inline static long* groupCallCounter;

        static const std::string merged_timer_group_names;

        const trl::timer_group _group;
        const std::chrono::time_point<std::chrono::steady_clock> _start_time;

        static void populate_timer_group_names()
        {
            ScopedTimer::timer_group_names.clear();

            std::string current_string = trl::ScopedTimer<>::merged_timer_group_names;

            if (current_string.empty())
            {
                // There are no groups
            }

            std::string::size_type  next_pos = current_string.find(',');
            while (next_pos != std::string::npos)
            {
                timer_group_names.push_back(current_string.substr(0, next_pos));

                current_string = current_string.substr(next_pos + 1);
                next_pos = current_string.find(',');
            }
            timer_group_names.push_back(current_string.substr(0, next_pos));
        }
    public:
        /**
         * Reset timers
         */
        static void resetTimers()
        {
            ScopedTimer::timer_group_names.clear();

            delete [] ScopedTimer::groupTotalTime;
            ScopedTimer::groupTotalTime = nullptr;

            delete [] ScopedTimer::groupCallCounter;
            ScopedTimer::groupCallCounter = nullptr;

            initTimers();
        }

        /**
         * Call to initiate timer variables
         */
        static void initTimers()
        {
            populate_timer_group_names();

            auto timerGroupSize = ScopedTimer::timer_group_names.size();

            ScopedTimer::groupTotalTime = new long[timerGroupSize];
            memset(ScopedTimer::groupTotalTime, 0, sizeof(long) * timerGroupSize);

            ScopedTimer::groupCallCounter = new long[timerGroupSize];
            memset(ScopedTimer::groupCallCounter, 0, sizeof(long) * timerGroupSize);
        }

        /**
         * Print timer total calls and average call times
         */
        static void printInfo()
        {
            std::cout << "--Timer Stats--" << std::endl;
            for (unsigned int i = 0; i < ScopedTimer::timer_group_names.size(); i++)
            {
                double average_time = (ScopedTimer::groupTotalTime[i] * 1.0) / ScopedTimer::groupCallCounter[i];

                std::cout << ScopedTimer::timer_group_names[i]
                          << ": avg:" << average_time
                          << " total_time:" << ScopedTimer::groupTotalTime[i]
                          << " total_calls:" << ScopedTimer::groupCallCounter[i] << std::endl;
            }
        }

        /**
         * Create a timer at the start of the scope you want to time and provide the group name of the timer
         */
        explicit ScopedTimer(trl::timer_group group)
                : _group(group)
                , _start_time(std::chrono::steady_clock::now())
        {

        }

        ~ScopedTimer()
        {
            std::chrono::time_point<std::chrono::steady_clock> _end_time = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(_end_time - _start_time);

            ScopedTimer::groupCallCounter[static_cast<int>(_group)]++;
            ScopedTimer::groupTotalTime[static_cast<int>(_group)] += duration.count();
        }
    };
}


#endif //LIBTR_LANG_SCOPEDTIMER_HPP
