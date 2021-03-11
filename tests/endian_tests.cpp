// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <sstream>
#include <catch2/catch.hpp>

#define BJ_FORCE_ENDIAN_OUT_BIG
#include <bj/binaryizer/iostream_binaryizer.hpp>

static_assert(std::endian::native == std::endian::little, "Endian tests must be run on a little endian machine");

TEST_CASE("endian conversion works", "[endian,iostream,arithmetic]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    const std::uint16_t value = 0xAABB;

    obin(value);

    const auto tester = ibin.get<std::uint16_t>();

    REQUIRE(tester == 0xBBAA);

}