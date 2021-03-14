// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/list.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::list de/binaryized with artimetic type", "[container,list,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::list<int> cont{ 2, 45, 23, 2 };
    std::list<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::list de/binaryized with binaryizable type county", "[container,list,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::list<county> cont{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::list<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.front().binarized == 1);
    REQUIRE(cont.front().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.front().binarized == 0);
    REQUIRE(empt.front().debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::list de/binaryized with emplaceable type emplacey", "[container,list,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::list<county> cont{ {1}, {4}, {7}, {12} };
    std::list<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.front().binarized == 1);
    REQUIRE(cont.front().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.front().binarized == 0);
    REQUIRE(empt.front().debinarized == 1);

    REQUIRE(cont == empt);

}