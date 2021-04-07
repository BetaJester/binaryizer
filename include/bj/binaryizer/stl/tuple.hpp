// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <tuple>
#include "../algorithm.hpp"
#include "../binaryizer.hpp"

namespace bj::inline v1{

    template<typename ...Types>
    inline void binaryize(obinaryizer &out, const std::tuple<Types...> &data) {
        std::apply([&](const Types &...items) { do_backwards(out, items...); }, data);
    }

    template<typename ...Types>
    inline void debinaryize(ibinaryizer &in, std::tuple<Types...> &data) {
        std::apply([&](Types &...items) { do_backwards(in, items...); }, data);
    }

} // namespace bj::inline v1.