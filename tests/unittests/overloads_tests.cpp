// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <array>
#include <catch2/catch.hpp>

// Test fails unless on a little endian system.
#define BJ_FORCE_ENDIAN_IN_BIG
#include <bj/binaryizer/traits_n_concepts.hpp>
#include <bj/binaryizer/ibinaryizer.hpp>
#include <bj/binaryizer/endian.hpp>

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

template<typename T, std::size_t N>
inline void arraytest(const std::array<T, N> &) {
    tester |= 0xFF000000;
}

template<bj::arithmetic_noraw_in T, std::size_t N>
inline void arraytest(const std::array<T, N> &) {
    tester |= 0x00FF0000;
}

template<bj::noraw_in T, std::size_t N>
inline void arraytest(const std::array<T, N> &) {
    tester |= 0x0000FF00;
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

TEST_CASE("overload for array int endian are called correctly", "[overloads,concepts,array,endian]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    std::array<int, 5> arr;

    arraytest(arr);

    REQUIRE(tester == 0x00FF0000);

}

TEST_CASE("overload for array binable rawable are called correctly", "[overloads,concepts,array,endian]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    std::array<binable, 5> arr;

    arraytest(arr);

    REQUIRE(tester == 0x0000FF00);

}

TEST_CASE("overload for array unbinable rawable are called correctly", "[overloads,concepts,array,endian]") {

    tester = 0;
    REQUIRE(tester == 0x00000000);

    std::array<unbinable, 5> arr;

    arraytest(arr);

    REQUIRE(tester == 0xFF000000);

}

