//
// Created by Michael Lynch on 13/11/2021.
//

#include <catch2/catch.hpp>
#include <trlang/hfn/Box.hpp>


TEST_CASE("shouldProduceBox", "[Applicative][i6]")
{
    auto b = hfn::Box<int>::pure(10);

    REQUIRE(b.getVal() == 10);
//    static_assert(std::is_same_v<decltype(b), hfn::Box<int>>);
}

TEST_CASE("shouldApplyFunction", "[Applicative][i6]")
{
    hfn::Box<int> b(10);

    REQUIRE(b.getVal() == 10);

    auto bTransform = b.seqApp<std::string>([](int i) {
        return std::to_string(i);
    });

    REQUIRE(bTransform.getVal() == "10");
}