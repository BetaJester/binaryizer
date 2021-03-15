// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <cstdint>

template<class A, std::size_t AN, class B, std::size_t BN>
[[nodiscard]] bool compare_arrays(A(&a)[AN], B(&b)[BN]) {
    static_assert(AN == BN);
    for (std::size_t i{}; i < AN; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}