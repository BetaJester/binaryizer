// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/unordered_multiset.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::unordered_multiset de/binaryized with arithmetic type", "[container,unordered_multiset,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unordered_multiset<int> cont{ 6, 3, 8, 243, 7};
    std::unordered_multiset<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::unordered_multiset de/binaryized with binaryizable type county", "[container,unordered_multiset,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unordered_multiset<county> cont{ {1,2,3}, {4,5,6}, {1,2,3}, {10,11,12} };
    std::unordered_multiset<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::unordered_multiset de/binaryized with emplaceble type emplacey", "[container,unordered_multiset,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unordered_multiset<emplacey> cont{3, 5, 2, 7, 23, 78};
    std::unordered_multiset<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}