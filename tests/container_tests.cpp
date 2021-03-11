// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <vector>
#include <sstream>

#include <catch2/catch.hpp>
#include <bj/stl_binaryizer.hpp>
#include <bj/iostream_binaryizer.hpp>
#include "county.hpp"

template<class A, std::size_t AN, class B, std::size_t BN>
[[nodiscard]] bool compare_arrays(A(&a)[AN], B(&b)[BN]) {
    static_assert(AN == BN);
    for (std::size_t i{}; i < AN; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

TEST_CASE("C array de/binaryized with arithmetic types", "[container,carray]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    int intarr[]{ 1, 3, 5, 7, 9 };
    int emptyarr[5];

    REQUIRE(!compare_arrays(intarr, emptyarr));

    obin(intarr);
    ibin(emptyarr);

    REQUIRE(compare_arrays(intarr, emptyarr));

}

TEST_CASE("C array de/binaryized with binaryizable type county", "[container,carray,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    county countyarr[]{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    county emptyarr[4];

    REQUIRE(!compare_arrays(countyarr, emptyarr));

    obin(countyarr);

    REQUIRE(countyarr[0].binarized == 1);
    REQUIRE(countyarr[0].debinarized == 0);

    ibin(emptyarr);

    REQUIRE(emptyarr[0].binarized == 0);
    REQUIRE(emptyarr[0].debinarized == 1);

    REQUIRE(compare_arrays(countyarr, emptyarr));

}

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

