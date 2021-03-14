// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/stack.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::stack de/binaryized with arithmetic type", "[container,stack,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::stack<int>::container_type inner{ 2, 4, 6, 234, 24 };
    std::stack<int> cont{ inner };
    std::stack<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::stack de/binaryized with binaryizable type county", "[container,stack,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::stack<county>::container_type inner{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::stack<county> cont{ inner };
    std::stack<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.top().binarized == 1);
    REQUIRE(cont.top().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.top().binarized == 0);
    REQUIRE(empt.top().debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::stack de/binaryized with emplaceable type emplacey", "[container,stack,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::stack<emplacey>::container_type inner{ 23, 64, 34, 88 };
    std::stack<emplacey> cont{ inner };
    std::stack<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.top().binarized == 1);
    REQUIRE(cont.top().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.top().binarized == 0);
    REQUIRE(empt.top().debinarized == 1);

    REQUIRE(cont == empt);

}