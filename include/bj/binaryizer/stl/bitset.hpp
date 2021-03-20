// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bitset>
#include <algorithm> // max.
#include "../binaryizer.hpp"
#include "../midiint.hpp"

namespace bj {

    template<std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::bitset<N> &data) {
        // Gets 64bit chunks, most significant first.
        std::uint64_t input;
        constexpr std::size_t input_count = N / 64u;
        for (std::size_t i{}; i < input_count; ++i) {
            in(midiint(input));
            std::bitset<N> temp_bitset(input);
            data <<= 64;
            data |= temp_bitset;
        }
    }

    template<std::size_t N>
    inline void binaryize(obinaryizer &out, const std::bitset<N> &data) {
        // Put 64bit chunks, most significant first.
        constexpr std::bitset<N> mask{ std::numeric_limits<std::uint64_t>::max() };
        constexpr std::ptrdiff_t output_count = N / 64u;
        for (std::ptrdiff_t i{output_count-1}; i >= 0; --i) {
            const auto shifted = data >> static_cast<std::size_t>(i * 64u);
            const auto masked = shifted & mask;
            const auto output_value = masked.to_ullong();
            out(midiint(output_value));
        }
    }

} // namespace bj.