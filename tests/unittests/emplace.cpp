// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <sstream>
#include <vector>
#include <catch2/catch.hpp>
#include "test_iobin.hpp"

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

template<bj::debinaryizer_constructable T>
void putinvec(bj::ibinaryizer &in, std::vector<T> &t) {
    t.emplace_back(in);
    t.emplace_back(100);
}

TEST_CASE("construct with ibinaryizer", "[emplace]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    obin(5);

    constructy c(ibin);

    REQUIRE(c.x == 5);

}

TEST_CASE("emplace with correct overload function", "[emplace,overload]") {
    
    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    obin(5);

    std::vector<constructy> vec;

    putinvec(ibin, vec);

    REQUIRE(vec[0].x == 5);     // Worked.
    REQUIRE(vec[1].x == 100);   // Correct overload.

}
