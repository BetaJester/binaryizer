// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/array.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"

TEST_CASE("std::array de/binaryized with arithmetic types", "[container,array,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::array<int, 5> cont{ 1, 3, 5, 7, 9 };
    std::array<int, 5> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::array de/binaryized with binaryizable type county", "[container,array,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::array<county, 4> cont{ county{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::array<county, 4> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont[0].binarized == 1);
    REQUIRE(cont[0].debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt[0].binarized == 0);
    REQUIRE(empt[0].debinarized == 1);

    REQUIRE(cont == empt);

}
