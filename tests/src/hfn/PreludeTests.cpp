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