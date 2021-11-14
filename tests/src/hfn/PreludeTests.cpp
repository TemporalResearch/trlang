//
// Created by Michael Lynch on 14/11/2021.
//

#include <catch2/catch.hpp>
#include <trlang/hfn/Prelude.hpp>

#include <trlang/hfn/Box.hpp>

TEST_CASE("shouldSequenceToNextValue", "[Prelude][i6]")
{
    hfn::Box<int> b(10);
    hfn::Box<std::string> c("Hello world");

    auto cAgain = hfn::seq(b, c);

    REQUIRE(cAgain == c);
}

int add(int a, int b)
{
    return a + b;
}

TEST_CASE("shouldCurryOneArgument", "[Prelude][i6]")
{
    auto add10 = hfn::curry(add, 10);

    REQUIRE(add10(20) == 30);
}

int addThree(int a, int b, int c)
{
    return a + b + c;
}

TEST_CASE("shouldCurryMultipleArgs", "[Prelude][i6]")
{
    auto add10 = hfn::curry(addThree, 10);
    auto add20 = hfn::curry(add10, 10);

    REQUIRE(add10(10, 10) == 30);
    REQUIRE(add20(10) == 30);
}