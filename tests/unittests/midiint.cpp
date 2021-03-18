// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include "test_iobin.hpp"
#include <bj/binaryizer/midiint.hpp>

TEST_CASE("midiint works unsigned low number", "[midiint,unsigned,low]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::uint32_t num{ 5 };
    std::uint32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 1);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works unsigned medium number", "[midiint,unsigned,medium]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::uint32_t num{ 5000 };
    std::uint32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 2);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works unsigned high number", "[midiint,unsigned,high]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::uint32_t num{ 500000 };
    std::uint32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 3);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works unsigned huge number", "[midiint,unsigned,huge]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::uint64_t num{ 68719476735 };
    std::uint64_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 6);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works unsigned biggest number", "[midiint,unsigned,biggest]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::uint64_t num{ std::numeric_limits<std::uint64_t>::max() };
    std::uint64_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 10);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works unsigned smallest number", "[midiint,unsigned,smallest]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::uint64_t num{};
    std::uint64_t in{ 101 };

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 1);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}