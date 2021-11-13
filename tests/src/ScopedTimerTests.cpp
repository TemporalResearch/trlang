//
// Created by Michael Lynch on 21/06/2021.
//

#include <trlang/timers/ScopedTimer.hpp>
#include <auto_test.hpp>
#include <catch2/catch.hpp>

TRL_TIMER_GROUP(
        TEST_1,
        TEST_2);

TEST_CASE("shouldDoSomething", "[ManualTest]")
{
    trl::ScopedTimer<>::initTimers();

    {
        trl::ScopedTimer<> timer(trl::timer_group::TEST_1);

        std::cout << "Hello world" << std::endl;
    }

    {

        trl::ScopedTimer<> timer(trl::timer_group::TEST_2);

        std::cout << "Different words" << std::endl;
    }

    {
        trl::ScopedTimer<> timer(trl::timer_group::TEST_1);

        std::cout << "Yet other words" << std::endl;
    }

    trl::ScopedTimer<>::printInfo();
}
