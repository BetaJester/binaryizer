// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/vector.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::vector de/binaryized with arithmetic types", "[container,vector,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::vector<int> cont{ 1, 3, 5, 7, 9 };
    std::vector<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::vector de/binaryized with binaryizable type county", "[container,vector,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::vector<county> cont{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::vector<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont[0].binarized == 1);
    REQUIRE(cont[0].debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt[0].binarized == 0);
    REQUIRE(empt[0].debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::vector de/binaryized with emplaceable type emplacey", "[container,vector,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::vector<emplacey> cont{ {1}, { 4 }, { 7 }, { 10 } };
    std::vector<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont[0].binarized == 1);
    REQUIRE(cont[0].debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt[0].binarized == 0);
    REQUIRE(empt[0].debinarized == 1);

    REQUIRE(cont == empt);

}
