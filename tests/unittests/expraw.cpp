// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include "test_iobin.hpp"
#include "compare_arrays.hpp"
#include <bj/binaryizer/stl/array.hpp>
#include <bj/binaryizer/expraw.hpp>
#include "nobin.hpp"
#include "rawable.hpp"

TEST_CASE("expraw does it's stuff", "[overloads,expraw]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    const nobin nope1{ 19, true, 2.4f };
    nobin nope2;

    REQUIRE(nope1 != nope2);

    iobin.out(bj::expraw{ nope1 });

    iobin.in(bj::expraw{ nope2 });

    REQUIRE(nope1 == nope2);

}

TEST_CASE("expraw array does it's stuff", "[overloads,expraw,carray]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    const nobin nope1[2]{ {19, true, 2.4f}, {23, false, 6.9f} };
    nobin nope2[2];

    REQUIRE(!compare_arrays(nope1, nope2));

    iobin.out(bj::expraw(nope1));

    iobin.in(bj::expraw(nope2));

    REQUIRE(compare_arrays(nope1, nope2));

    nope2[0].a = 892;

    REQUIRE(!compare_arrays(nope1, nope2));
}

TEST_CASE("binwrap does it's stuff", "[overloads,binwrap]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    const bj::expraw<nobin> nope1{ 19, true, 2.4f };
    bj::expraw<nobin> nope2;

    REQUIRE(*nope1 != *nope2);

    iobin.out(nope1);

    iobin.in(nope2);

    REQUIRE(*nope1 == *nope2);

}

TEST_CASE("binwrap std::array does it's stuff", "[overloads,binwrap,array]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    using bw = bj::expraw<nobin>;

    std::array<bw, 2> nope1{ bw{19, true, 2.4f}, bw{23, false, 6.9f} };
    std::array<bw, 2> nope2;

    // Should NOT work.
    // std::array<nobin, 2> nope3;
    // iobin.out(nope3);
    // std::list<nobin> nope4;
    // iobin.out(nope4);

    REQUIRE(nope1 != nope2);

    iobin.out(nope1);
    iobin.in(nope2);

    REQUIRE(nope1 == nope2);

}

TEST_CASE("binwrap carray does it's stuff", "[overloads,binwrap,carray]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    using bw = bj::expraw<nobin>;

    // Should NOT work.
    // nobin nope3[3];
    // iobin.out(nope3);

    bw nope1[2]{ bw{19, true, 2.4f}, bw{23, false, 6.9f} };
    bw nope2[2];

    REQUIRE(!compare_arrays(nope1, nope2));

    iobin.out(nope1);
    iobin.in(nope2);

    REQUIRE(compare_arrays(nope1, nope2));

}

TEST_CASE("explictly_raw does it's stuff", "[overloads,explictly_raw]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    const rawable nope1{ 19, true, 2.4f };
    rawable nope2;

    REQUIRE(nope1 != nope2);

    iobin.out(nope1);

    iobin.in(nope2);

    REQUIRE(nope1 == nope2);

}

TEST_CASE("explictly_raw carray does it's stuff", "[overloads,explictly_raw,carray]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    rawable nope1[2]{ {19, true, 2.4f}, {23, false, 6.9f} };
    rawable nope2[2];

    REQUIRE(!compare_arrays(nope1, nope2));

    iobin.out(nope1);
    iobin.in(nope2);

    REQUIRE(compare_arrays(nope1, nope2));

}