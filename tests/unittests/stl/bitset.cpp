// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/bitset.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::bitset de/binaryized", "[container,bitset]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::bitset<128> cont(0xFFEEBBCCDDEEAA77ull);
    std::bitset<128> empt;

    REQUIRE(cont != empt);

    iobin.out(cont);

    REQUIRE(iobin.stream().str().size() == 11);

    iobin.in(empt);

    REQUIRE(cont == empt);

}