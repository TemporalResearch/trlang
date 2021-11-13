//
// Created by Michael Lynch on 13/11/2021.
//

#include <catch2/catch.hpp>
#include <trlang/hfn/Box.hpp>

TEST_CASE("shouldMapToNewValue", "[Functor][i6]")
{
    hfn::Box<int> b(10);

    REQUIRE(b.getVal() == 10);

    auto bTransform = b.map<std::string>([](int i) {
        return std::to_string(i);
    });

    REQUIRE(bTransform.getVal() == "10");
}