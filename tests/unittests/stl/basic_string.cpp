// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/basic_string.hpp>
#include "../test_iobin.hpp"

TEST_CASE("std::string de/binaryized", "[container,arithmetic,string,basic_string]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::string cont = "Get ready 'cause this ain't funny, My name's Mike D and I'm about to get money";
    std::string empt;

    REQUIRE(cont != empt);

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(cont == empt);

}