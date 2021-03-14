// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/unique_ptr.hpp>
#include "../test_iobin.hpp"
#include "../county.hpp"
#include "../emplacey.hpp"

TEST_CASE("std::unique_ptr de/binaryized with arithmetic type", "[container,unique_ptr,arithmetic]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unique_ptr<int> cont = std::make_unique<int>(5);
    std::unique_ptr<int> empt;

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(*cont == *empt);

}

TEST_CASE("std::unique_ptr de/binaryized with binaryizable type county", "[container,unique_ptr,county]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unique_ptr<county> cont = std::make_unique<county>();
    std::unique_ptr<county> empt;

    iobin.out(cont);

    REQUIRE(cont->binarized == 1);
    REQUIRE(cont->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt->binarized == 0);
    REQUIRE(empt->debinarized == 1);

    REQUIRE(*cont == *empt);

}

TEST_CASE("std::unique_ptr de/binaryized with emplaceable type emplacey", "[container,unique_ptr,emplacey]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::unique_ptr<emplacey> cont = std::make_unique<emplacey>(8);
    std::unique_ptr<emplacey> empt;

    iobin.out(cont);

    REQUIRE(cont->binarized == 1);
    REQUIRE(cont->debinarized == 0);

    iobin.in(empt);

    REQUIRE(empt->binarized == 0);
    REQUIRE(empt->debinarized == 1);

    REQUIRE(*cont == *empt);

}