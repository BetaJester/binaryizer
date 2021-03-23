// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include "../binaryizer.hpp"

namespace bj {

    template<explicity_raw_out T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T, N> &data) {
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<not_raw_out T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T, N> &data) {
        out.put(data.begin(), data.end());
    }

    template<explicity_raw_in T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T, N> &data) {
        in.getraw(reinterpret_cast<std::byte *>(data.data()), N * sizeof(T));
    }

    template<not_raw_in T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T, N> &data) {
        in.get(data.begin(), data.end());
    }

} // namespace bj.