//
// Created by Michael Lynch on 13/11/2021.
//

#include <catch2/catch.hpp>
#include <trlang/hfn/Box.hpp>
#include <trlang/hfn/DoubleBox.hpp>

TEST_CASE("shouldGetInternalObject", "[Monad][i6]")
{
    hfn::Box<int> b(10);

    auto bTransform = b.flatMap<std::string>([](int i) {
        return hfn::Box<std::string>(std::to_string(i));
    });

    REQUIRE(bTransform.getVal() == "10");
}

TEST_CASE("shouldGetInternalObjectDoubleBox", "[Monad][i6]")
{
    hfn::DoubleBox<std::string, int> b(10);

    auto bTransform = b.flatMap<std::string>([](int i) {
        return hfn::DoubleBox<std::string, std::string>(std::to_string(i));
    });

    REQUIRE(bTransform.getVal() == "10");
}
