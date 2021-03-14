// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/unordered_set.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::unordered_set de/binaryized with arithmetic type", "[container,unordered_set,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unordered_set<int> cont{5, 7, 2, 65, 23};
    std::unordered_set<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::unordered_set de/binaryized with binaryizable type county", "[container,unordered_set,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unordered_set<county> cont{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::unordered_set<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::unordered_set de/binaryized with emplaceable type emplacey", "[container,unordered_set,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unordered_set<emplacey> cont{ 1, 243, 6, 2, 56};
    std::unordered_set<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}