// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include "test_iobin.hpp"
#include "county.hpp"
#include "compare_arrays.hpp"

TEST_CASE("C array de/binaryized with arithmetic types", "[container,carray,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    int intarr[]{ 1, 3, 5, 7, 9 };
    int emptyarr[5];

    REQUIRE(!compare_arrays(intarr, emptyarr));

    iobin.out(intarr);
    iobin.in(emptyarr);

    REQUIRE(compare_arrays(intarr, emptyarr));

}

TEST_CASE("C array de/binaryized with binaryizable type county", "[container,carray,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    county countyarr[]{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    county emptyarr[4];

    REQUIRE(!compare_arrays(countyarr, emptyarr));

    iobin.out(countyarr);

    REQUIRE(countyarr[0].binarized == 1);
    REQUIRE(countyarr[0].debinarized == 0);

    iobin.in(emptyarr);

    REQUIRE(emptyarr[0].binarized == 0);
    REQUIRE(emptyarr[0].debinarized == 1);

    REQUIRE(compare_arrays(countyarr, emptyarr));

}