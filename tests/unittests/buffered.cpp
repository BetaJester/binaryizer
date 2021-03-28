// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <sstream>
#include <catch2/catch.hpp>
#include <bj/binaryizer/buffered.hpp>
#include <bj/binaryizer/iostream_binaryizer.hpp>

template<auto N>
constexpr auto unfold = [](auto expr) {
    [expr] <auto ...Is>(std::index_sequence<Is...>) {
        ((expr(), void(Is)), ...);
    }(std::make_index_sequence<N>{});
};

TEST_CASE("buffered basic test", "[buffered,basic]") {

    bj::buffered<bj::iostream_binaryizer<std::stringstream>> iobin(std::ios::in | std::ios::out | std::ios::binary);

    iobin.out(2001);
    const int in = iobin.get<int>();

    REQUIRE(in == 2001);

}

TEST_CASE("buffered overflow test", "[buffered,overflow]") {

    bj::buffered<bj::iostream_binaryizer<std::stringstream>> iobin(std::ios::in | std::ios::out | std::ios::binary);

    int data[50]; // 200 bytes, smaller than buffer 1024, overflows 5th iteration.

    unfold<10>([&] { iobin.out(data); });

    // 1 200 G
    // 2 400 G
    // 3 600 G
    // 4 800 G
    // 5 1000 G
    // 6 flush then 200
    // 7 400
    // 8 600
    // 9 800
    // A 1000

    REQUIRE(iobin.stream().str().size() == 1000);

    iobin.flush();

    REQUIRE(iobin.stream().str().size() == 2000);
}