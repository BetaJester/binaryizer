// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <algorithm>
#include <catch2/catch.hpp>
#include <bj/binaryizer/stl/valarray.hpp>
#include "../test_iobin.hpp"

template<typename T>
bool compare_valarrays(const std::valarray<T> &lhs, const std::valarray<T> &rhs) {
    return lhs.size() == rhs.size() && std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
}

TEST_CASE("std::valarray de/binarizes", "[valarray]") {

    auto iobin = test_iobin();
    REQUIRE(iobin.good());

    std::valarray<int> cont{ 3, 5, -2, 4, -10 };
    std::valarray<int> empt;

    REQUIRE(!compare_valarrays(cont, empt));

    iobin.out(cont);
    iobin.in(empt);

    REQUIRE(compare_valarrays(cont, empt));

}