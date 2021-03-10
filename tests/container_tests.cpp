// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <vector>

#include <catch2/catch.hpp>
#include <bj/iostream_binaryizer.hpp>
#include "county.hpp"

TEST_CASE("std::vector de/binaryized with arithmetic types", "[container,vector]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::vector<int> intvec{ 1, 3, 5, 7, 9 };
    std::vector<int> emptyvec;

    REQUIRE(intvec != emptyvec);

    obin(intvec);
    ibin(emptyvec);

    REQUIRE(intvec == emptyvec);

}

TEST_CASE("std::vector de/binaryized with binaryizable type county", "[container,vector,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::vector<county> countyvec{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::vector<county> emptyvec;

    REQUIRE(countyvec != emptyvec);
    
    obin(countyvec);

    REQUIRE(countyvec[0].binarized == 1);
    REQUIRE(countyvec[0].debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec[0].binarized == 0);
    REQUIRE(emptyvec[0].debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}