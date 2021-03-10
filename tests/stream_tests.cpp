// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <sstream>

#include <catch2/catch.hpp>
#include <bj/iostream_binaryizer.hpp>
#include "county.hpp"


TEST_CASE("std::stringstream de/binaryize of 'county'", "[stream,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;
    
    county c1{ .a = 1, .b = 2, .c = 3 }, c2{ .a = 4, .b = 5, .c = 6};
    
    REQUIRE(c1 != c2);
    
    obin(c1);
    REQUIRE(c1.binarized == 1);
    REQUIRE(c1.debinarized == 0);

    iobin.rewind();

    ibin(c2);
    REQUIRE(c2.binarized == 0);
    REQUIRE(c2.debinarized == 1);
    
    REQUIRE(c1 == c2);

}