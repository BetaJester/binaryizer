// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <valarray>
#include "../binaryizer.hpp"

namespace bj {

    template<typename T>
    inline void binaryize(obinaryizer &out, const std::valarray<T> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(std::begin(data), std::end(data));
    }

    template<typename T>
    inline void debinaryize(ibinaryizer &in, std::valarray<T> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(std::begin(data), std::end(data));
    }

} // namespace bj.