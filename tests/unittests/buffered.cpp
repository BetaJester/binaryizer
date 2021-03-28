// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <sstream>
#include <catch2/catch.hpp>
#include <bj/binaryizer/buffered.hpp>
#include <bj/binaryizer/iostream_binaryizer.hpp>

TEST_CASE("buffered basic test", "[buffered,basic]") {

    bj::buffered<bj::iostream_binaryizer<std::stringstream>> iobin(std::ios::in | std::ios::out | std::ios::binary);

    iobin.out(2001);
    const int in = iobin.get<int>();

    REQUIRE(in == 2001);

}