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

// Signed :)

TEST_CASE("midiint works signed low number", "[midiint,signed,low]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int32_t num{ 5 };
    std::int32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 1);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works signed medium number", "[midiint,signed,medium]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int32_t num{ 5000 };
    std::int32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 2);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works signed high number", "[midiint,signed,high]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int32_t num{ 500000 };
    std::int32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 3);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works signed huge number", "[midiint,signed,huge]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int64_t num{ 68719476735 };
    std::int64_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 6);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works signed biggest number", "[midiint,signed,biggest]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int64_t num{ std::numeric_limits<std::int64_t>::max() };
    std::int64_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 10);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works signed zero number", "[midiint,signed,zero]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int64_t num{};
    std::int64_t in{ 101 };

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 1);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

// Signed negative :)

TEST_CASE("midiint works negative low number", "[midiint,negative,low]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int32_t num{ -5 };
    std::int32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 1);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works negative medium number", "[midiint,negative,medium]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int32_t num{ -5000 };
    std::int32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 2);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works negative high number", "[midiint,negative,high]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int32_t num{ -500000 };
    std::int32_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 3);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works negative huge number", "[midiint,negative,huge]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int64_t num{ -68719476735 };
    std::int64_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 6);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works negative biggest number", "[midiint,negative,biggest]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int64_t num{ std::numeric_limits<std::int64_t>::max() };
    std::int64_t in{};

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 10);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}

TEST_CASE("midiint works negative smallest number", "[midiint,negative,smallest]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::int64_t num{ std::numeric_limits<std::int64_t>::min() };
    std::int64_t in{ 101 };

    iobin.out(bj::midiint(num));

    REQUIRE(iobin.stream().str().size() == 10);

    iobin.in(bj::midiint(in));

    REQUIRE(in == num);

}