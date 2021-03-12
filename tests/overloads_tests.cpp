// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/traits_n_concepts.hpp>

std::uint32_t tester{};

template<typename T>
void function(T &) {
    tester |= 0xFF000000;
}

template<bj::norawable T>
void function(T &) {
    tester |= 0x00FF0000;
}

struct binable {
    template<typename A> void binaryize(A &) const {}
    template<typename A> void debinaryize(A &) {}
};

struct unbinable {

};

template<bj::arithmetic T>
void arithfunction(T &) {
    tester |= 0x0000FF00;
}

template<bj::binaryizable T>
void arithfunction(T &) {
    tester |= 0x000000FF;
}

TEST_CASE("overload for binarizable are called correctly", "[overloads,concepts]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    binable binny{};
    function(binny);

    REQUIRE(tester == 0x00FF0000);

}

TEST_CASE("overload for arithmetic are called correctly", "[overloads,concepts]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    int inty{};
    function(inty);

    REQUIRE(tester == 0x00FF0000);

}

TEST_CASE("overload for others are called correctly", "[overloads,concepts]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    unbinable unbinny{};
    function(unbinny);

    REQUIRE(tester == 0xFF000000);

}

TEST_CASE("overload for just arithmetic are called correctly", "[overloads,concepts]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    int inty{};
    arithfunction(inty);

    REQUIRE(tester == 0x0000FF00);

}