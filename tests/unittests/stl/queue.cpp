// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/queue.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::queue de/binaryized with arithmetic type", "[container,queue,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::queue<int>::container_type inner{ 5, 34, 87, 23, 35 };
    std::queue<int> cont{ inner };
    std::queue<int> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}

TEST_CASE("std::queue de/binaryized with binaryizable type county", "[container,queue,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::queue<county>::container_type inner{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::queue<county> cont{ inner };
    std::queue<county> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.front().binarized == 1);
    REQUIRE(cont.front().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.front().binarized == 0);
    REQUIRE(empt.front().debinarized == 1);

    REQUIRE(cont == empt);

}

TEST_CASE("std::queue de/binaryized with emplaceable type emplacey", "[container,queue,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::queue<emplacey>::container_type inner{ 3, 3, 5, 7, 23, 886 };
    std::queue<emplacey> cont{ inner };
    std::queue<emplacey> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(cont.front().binarized == 1);
    REQUIRE(cont.front().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.front().binarized == 0);
    REQUIRE(empt.front().debinarized == 1);

    REQUIRE(cont == empt);

}