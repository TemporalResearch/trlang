//
// Created by Michael Lynch on 21/02/2022.
//

#include <trlang/ReversibleRandomGenerator.hpp>
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("shouldReturnPreviousValue", "[ReversibleRandomGenerator]")
{
    trl::ReversibleRandomGenerator gen(34);

    auto originalValue = gen.next();

    for (unsigned int i = 0; i < 2000000; i++)
    {
        gen.next();
    }

    for (unsigned int i = 0; i < 2000000; i++)
    {
        gen.previous();
    }

    REQUIRE(originalValue == gen.previous());
}

TEST_CASE("shouldReturnPreviousOnFirstTry", "[ReversibleRandomGenerator]")
{
    trl::ReversibleRandomGenerator gen(34);

    auto originalValue = gen.next();
    gen.next();
    gen.previous();
    REQUIRE(originalValue == gen.previous());
}

TEST_CASE("shouldResetToOriginalValue", "[ReversibleRandomGenerator]")
{
    trl::ReversibleRandomGenerator gen(2434);

    auto originalValue = gen.next();

    for (unsigned int i = 0; i < 3402490; i++)
    {
        gen.next();
    }

    gen.reset();
    REQUIRE(gen.next() == originalValue);
}

TEST_CASE("shouldActuallyBeRandom", "[ReversibleRandomGenerator]")
{
    trl::ReversibleRandomGenerator gen(240302);

    for (unsigned int i = 0; i < 3429; i++)
    {
        gen.next();
    }

    auto randomValue = gen.next();

    for (unsigned int i = 0; i < 1000000; i++)
    {
        REQUIRE(randomValue != gen.next());
    }
}