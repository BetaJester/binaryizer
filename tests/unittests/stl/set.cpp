// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/set.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::set de/binaryized with arithmetic type", "[container,set,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::set<int> cont{ 768, 65, 12, 4, 1 };
    std::set<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::set de/binaryized with binaryizable type county", "[container,set,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::set<county> cont{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::set<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::set de/binaryized with emplaceable type emplacey", "[container,set,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::set<emplacey> cont{ 1, 4, 6, 1, 6, 8 };
    std::set<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.begin()->binarized == 1);
    REQUIRE(cont.begin()->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.begin()->binarized == 0);
    REQUIRE(empt.begin()->debinarized == 1);

    REQUIRE(cont == empt);

}
