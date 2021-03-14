// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/multiset.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::multiset de/binaryized with arithmetic type county", "[container,multiset,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::multiset<int> cont{3, 5, 7, 23, 214, 5, 5};
    std::multiset<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::multiset de/binaryized with binaryizable type county", "[container,multiset,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::multiset<county> cont{ {1,2,3}, {4,5,6}, {1,2,3}, {10,11,12} };
    std::multiset<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::multiset de/binaryized with emplaceable type emplacey", "[container,multiset,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::multiset<emplacey> cont{ 43, 2, 5, 2, 6 };
    std::multiset<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}