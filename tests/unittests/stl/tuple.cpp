// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/tuple.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::tuple de/binaryized with arithmetic type", "[container,tuple,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::tuple<int, float> cont{ 768, 1.0f };
    std::tuple<int, float> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::tuple de/binaryized with binaryizable type county", "[container,tuple,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::tuple<county, county> cont{ {1,2,3}, {4,5,6} };
    std::tuple<county, county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(std::get<0>(cont).binarized == 1);
    REQUIRE(std::get<0>(cont).debinarized == 0);

    iobin.in(empt);

    REQUIRE(std::get<0>(empt).binarized == 0);
    REQUIRE(std::get<0>(empt).debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::tuple de/binaryized with emplaceable type emplacey", "[container,tuple,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::tuple<emplacey, emplacey> cont{ 1, 4 };

    iobin.out(cont);

    REQUIRE(std::get<0>(cont).binarized == 1);
    REQUIRE(std::get<0>(cont).debinarized == 0);

    std::tuple<emplacey, emplacey> empt{ iobin, iobin };

    REQUIRE(std::get<0>(empt).binarized == 0);
    REQUIRE(std::get<0>(empt).debinarized == 1);

    REQUIRE(cont == empt);

}
