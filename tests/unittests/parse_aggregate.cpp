// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/parse_aggregate.hpp>
#include <fmt/format.h>
#include "test_iobin.hpp"

struct S {
    int i{};
    char c{};
    float f{};

    auto operator<=>(const S &) const noexcept = default;

    friend std::ostream &operator<<(std::ostream &out, const S &s) {
        return out << fmt::format("[{},{},{}]", s.i, s.c, s.f);
    }
};

TEST_CASE("to_tuple works", "[tuple,aggregate]") {

    S s{ 10, 'r', 29.87f };

    auto t = bj::to_tuple(s);
    
    static_assert(std::is_same_v<decltype(std::get<0>(t)), int&>);
    static_assert(std::is_same_v<decltype(std::get<1>(t)), char&>);
    static_assert(std::is_same_v<decltype(std::get<2>(t)), float&>);

}

TEST_CASE("struct de/binarying works" "[tuple,aggregate,binary]") {

    auto iobin = test_iobin();

    S s{ 10, 'r', 29.87f };

    //auto t = bj::to_tuple(s);

    bj::for_each_aggregate(s, [&](auto a) { iobin.out(a); });

    S i;

    bj::for_each_aggregate(i, [&](auto &a) { iobin.in(a); });

    REQUIRE(s == i);

}

TEST_CASE("struct parsed de/binarying works" "[struct,aggregate,binary]") {

    auto iobin = test_iobin();

    S s{ 10, 'r', 29.87f };
    S i;

    REQUIRE(s != i);

    iobin.out(bj::parsed(s));
    iobin.in(bj::parsed(i));

    REQUIRE(s == i);

}

TEST_CASE("struct wrap parsed de/binarying works" "[struct,aggregate,binary,wrap]") {

    auto iobin = test_iobin();

    bj::parsed<S> s{ 10, 'r', 29.87f };
    bj::parsed<S> i;

    REQUIRE(s != i);

    iobin.out(s);
    iobin.in(i);

    REQUIRE(s == i);

}
