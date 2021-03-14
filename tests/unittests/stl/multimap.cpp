// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/multimap.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::multimap de/binaryized with arithmetic type", "[container,multimap,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::multimap<int, int> cont{ {3,3}, {5,7}, {3,0}, {0,12} };
    std::multimap<int, int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::multimap de/binaryized with binaryizable type county", "[container,multimap,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::multimap<int, county> cont{ {3,{1,2,3}}, {5,{4,5,6}}, {3,{7,8,9}}, {0,{10,11,12}} };
    std::multimap<int, county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->second.binarized == 1);
    REQUIRE(cont.begin()->second.debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->second.binarized == 0);
    REQUIRE(empt.begin()->second.debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::multimap de/binaryized with emplaceable type emplacey", "[container,multimap,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::multimap<int, emplacey> cont{ {3,3}, {5,4}, {3,9}, {0,11} };
    std::multimap<int, emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->second.binarized == 1);
    REQUIRE(cont.begin()->second.debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->second.binarized == 0);
    REQUIRE(empt.begin()->second.debinarized == 1);

    REQUIRE(cont == empt);

}