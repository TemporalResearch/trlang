//
// Created by Michael Lynch on 13/11/2021.
//

#include <catch2/catch.hpp>
#include <trlang/hfn/Box.hpp>

TEST_CASE("shouldGetInternalObject", "[Monad][i6]")
{
    hfn::Box<int> b(10);

    auto bTransform = b.flatMap<std::string>([](int i) {
        return hfn::Box<std::string>(std::to_string(i));
    });

    REQUIRE(bTransform.getVal() == "10");
}
