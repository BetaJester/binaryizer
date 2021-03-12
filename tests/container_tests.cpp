// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <vector>
#include <sstream>

#include <catch2/catch.hpp>

// Endian flips for an extra twist.
#define BJ_FORCE_ENDIAN_OUT_BIG
#define BJ_FORCE_ENDIAN_IN_BIG
#include <bj/binaryizer/stl_binaryizer.hpp>
#include <bj/binaryizer/iostream_binaryizer.hpp>
#include "county.hpp"
#include "emplacey.hpp"

template<class A, std::size_t AN, class B, std::size_t BN>
[[nodiscard]] bool compare_arrays(A(&a)[AN], B(&b)[BN]) {
    static_assert(AN == BN);
    for (std::size_t i{}; i < AN; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// C array.

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

// std::array.

TEST_CASE("std::array de/binaryized with arithmetic types", "[container,array]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::array<int,5> intvec{ 1, 3, 5, 7, 9 };
    std::array<int,5> emptyvec;

    REQUIRE(intvec != emptyvec);

    obin(intvec);
    ibin(emptyvec);

    REQUIRE(intvec == emptyvec);

}

TEST_CASE("std::array de/binaryized with binaryizable type county", "[container,array,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::array<county,4> countyvec{ county{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::array<county,4> emptyvec;

    REQUIRE(countyvec != emptyvec);

    obin(countyvec);

    REQUIRE(countyvec[0].binarized == 1);
    REQUIRE(countyvec[0].debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec[0].binarized == 0);
    REQUIRE(emptyvec[0].debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}

// std::vector.

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

TEST_CASE("std::vector de/binaryized with emplaceable type county", "[container,vector,emplacey]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::vector<emplacey> countyvec{ {1}, { 4 }, { 7 }, { 10 } };
    std::vector<emplacey> emptyvec;

    REQUIRE(countyvec != emptyvec);

    obin(countyvec);

    REQUIRE(countyvec[0].binarized == 1);
    REQUIRE(countyvec[0].debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec[0].binarized == 0);
    REQUIRE(emptyvec[0].debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}

// std::deque.

TEST_CASE("std::deque de/binaryized with arithmetic types", "[container,deque]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::deque<int> intvec{ 1, 3, 5, 7, 9 };
    std::deque<int> emptyvec;

    REQUIRE(intvec != emptyvec);

    obin(intvec);
    ibin(emptyvec);

    REQUIRE(intvec == emptyvec);

}

TEST_CASE("std::deque de/binaryized with binaryizable type county", "[container,deque,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::deque<county> countyvec{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::deque<county> emptyvec;

    REQUIRE(countyvec != emptyvec);

    obin(countyvec);

    REQUIRE(countyvec[0].binarized == 1);
    REQUIRE(countyvec[0].debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec[0].binarized == 0);
    REQUIRE(emptyvec[0].debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}

// std::forward_list.

TEST_CASE("std::forward_list de/binaryized with binaryizable type county", "[container,forward_list,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::forward_list<county> countyvec{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::forward_list<county> emptyvec;

    REQUIRE(countyvec != emptyvec);

    obin(countyvec);

    REQUIRE(countyvec.front().binarized == 1);
    REQUIRE(countyvec.front().debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec.front().binarized == 0);
    REQUIRE(emptyvec.front().debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}

// std::list.

TEST_CASE("std::list de/binaryized with binaryizable type county", "[container,list,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::list<county> countyvec{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::list<county> emptyvec;

    REQUIRE(countyvec != emptyvec);

    obin(countyvec);

    REQUIRE(countyvec.front().binarized == 1);
    REQUIRE(countyvec.front().debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec.front().binarized == 0);
    REQUIRE(emptyvec.front().debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}

// std::string.

TEST_CASE("std::string de/binaryized", "[container,string]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::string str = "Get ready 'cause this ain't funny, My name's Mike D and I'm about to get money";
    std::string empty;

    REQUIRE(str != empty);

    obin(str);
    ibin(empty);

    REQUIRE(str == empty);

}

// std::set.

TEST_CASE("std::set de/binaryized with binaryizable type county", "[container,set,county]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    std::set<county> countyvec{ {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
    std::set<county> emptyvec;

    REQUIRE(countyvec != emptyvec);

    obin(countyvec);

    REQUIRE(countyvec.begin()->binarized == 1);
    REQUIRE(countyvec.begin()->debinarized == 0);

    ibin(emptyvec);

    REQUIRE(emptyvec.begin()->binarized == 0);
    REQUIRE(emptyvec.begin()->debinarized == 1);

    REQUIRE(countyvec == emptyvec);

}