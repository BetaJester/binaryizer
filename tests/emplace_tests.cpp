// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <sstream>
#include <vector>
#include <catch2/catch.hpp>
#include <bj/binaryizer/iostream_binaryizer.hpp>

struct constructy {

    int x{};

    constructy() = default;
    constructy(int n) : x{ n } {}

    constructy(bj::ibinaryizer &a) {
        a(x);
    }

};

template<typename T>
void putinvec(bj::ibinaryizer &in, std::vector<T> &t) {
    t.emplace_back(in);
    t.emplace_back(50);
}

template<bj::debinaryizable_emplace T>
void putinvec(bj::ibinaryizer &in, std::vector<T> &t) {
    t.emplace_back(in);
    t.emplace_back(100);
}

TEST_CASE("construct with ibinaryizer", "[emplace]") {

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    obin(5);

    constructy c(ibin);

    REQUIRE(c.x == 5);

}

TEST_CASE("emplace with correct overload function", "[emplace,overload]") {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    obin(5);

    std::vector<constructy> vec;

    putinvec(ibin, vec);

    REQUIRE(vec[0].x == 5);     // Worked.
    REQUIRE(vec[1].x == 100);   // Correct overload.

}
