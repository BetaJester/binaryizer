// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <utility>
#include "../binaryizer.hpp"

namespace bj::inline v1{

    template<typename T1, typename T2>
    inline void binaryize(obinaryizer &out, const std::pair<T1, T2> &data) {
        out(data.first, data.second);
    }

    template<typename T1, typename T2>
    inline void debinaryize(ibinaryizer &in, std::pair<T1, T2> &data) {
        in(data.first, data.second);
    }

} // namespace bj::inline v1.