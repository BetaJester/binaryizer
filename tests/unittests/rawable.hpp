// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bj/binaryizer/traits_n_concepts.hpp>

struct rawable {
    int a{};
    bool b{};
    float c{};

    auto operator<=>(const rawable &) const = default;
};

namespace bj {
    template<> struct explicitly_raw<rawable> : std::true_type {};
} // namespace bj.