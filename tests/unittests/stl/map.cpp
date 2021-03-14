// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/map.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::map de/binaryized with arithmetic type", "[container,map,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::map<int, int> cont{ {3,6}, {5,4}, {2,233}, {0,23} };
    std::map<int, int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::map de/binaryized with binaryizable type county", "[container,map,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::map<int, county> cont{ {3,{1,2,3}}, {5,{4,5,6}}, {2,{7,8,9}}, {0,{10,11,12}} };
    std::map<int, county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->second.binarized == 1);
    REQUIRE(cont.begin()->second.debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->second.binarized == 0);
    REQUIRE(empt.begin()->second.debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::map de/binaryized with emplaceable type emplacey", "[container,map,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::map<int, emplacey> cont{ {3,1}, {5,4}, {2,9}, {0,12} };
    std::map<int, emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->second.binarized == 1);
    REQUIRE(cont.begin()->second.debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->second.binarized == 0);
    REQUIRE(empt.begin()->second.debinarized == 1);

    REQUIRE(cont == empt);

}