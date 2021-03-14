// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/priority_queue.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::priority_queue de/binaryized with arithmetic type", "[container,priority_queue,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::priority_queue<int>::container_type inner{ 4, 23, 4, 566, 22, 2};
    std::priority_queue<int> cont{ inner.begin(), inner.end() };
    std::priority_queue<int> empt;

    auto &c = cont.*(&bj::inner_container<std::priority_queue<int>>::c);
    auto &e = empt.*(&bj::inner_container<std::priority_queue<int>>::c);

    REQUIRE(c != e);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(c == e);

}

TEST_CASE("std::priority_queue de/binaryized with binaryizable type county", "[container,priority_queue,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::priority_queue<county>::container_type inner{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::priority_queue<county> cont{ inner.begin(), inner.end() };
    std::priority_queue<county> empt;

    auto &c = cont.*(&bj::inner_container<std::priority_queue<county>>::c);
    auto &e = empt.*(&bj::inner_container<std::priority_queue<county>>::c);

    REQUIRE(c != e);

    iobin.out(cont);

    REQUIRE(cont.top().binarized == 1);
    REQUIRE(cont.top().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.top().binarized == 0);
    REQUIRE(empt.top().debinarized == 1);

    REQUIRE(c == e);

}

TEST_CASE("std::priority_queue de/binaryized with emplaceable type county", "[container,priority_queue,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::priority_queue<emplacey>::container_type inner{4, 3, 6, 34, 346, 2432};
    std::priority_queue<emplacey> cont{ inner.begin(), inner.end() };
    std::priority_queue<emplacey> empt;

    auto &c = cont.*(&bj::inner_container<std::priority_queue<emplacey>>::c);
    auto &e = empt.*(&bj::inner_container<std::priority_queue<emplacey>>::c);

    REQUIRE(c != e);

    iobin.out(cont);

    REQUIRE(cont.top().binarized == 1);
    REQUIRE(cont.top().debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt.top().binarized == 0);
    REQUIRE(empt.top().debinarized == 1);

    REQUIRE(c == e);

}