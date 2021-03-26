// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bit>
#include <type_traits>
#include <cstdint>
#include "settings.hpp"
#include "bit_cast.hpp"

namespace bj {

    template<typename T>
    requires std::is_arithmetic_v<T> // Avoid our concepts header.
    [[nodiscard]] constexpr T swap_endian(const T n) noexcept {
        if constexpr (std::is_same_v<T, float>) {
            const auto nf = impl::bit_cast<std::uint32_t>(n);
            return impl::bit_cast<float>(((nf >> 24) & 0xFF) | ((nf << 8) & 0xFF0000) | ((nf >> 8) & 0xFF00) | ((nf << 24) & 0xFF000000));
        }
        if constexpr (std::is_same_v<T, double>) {
            auto x = impl::bit_cast<std::uint64_t>(n);
            x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
            x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
            x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
            return impl::bit_cast<double>(x);
        }
        if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) == 1) return n;
            if constexpr (sizeof(T) == 2) return static_cast<T>((n << 8) | (n >> 8)); // Cast to quiet clang.
            if constexpr (sizeof(T) == 4) {
                const auto nf = impl::bit_cast<std::uint32_t>(n);
                return impl::bit_cast<T>(((nf >> 24) & 0xFF) | ((nf << 8) & 0xFF0000) | ((nf >> 8) & 0xFF00) | ((nf << 24) & 0xFF000000));
            }
            if constexpr (sizeof(T) == 8) {
                T x = n;
                x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
                x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
                x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
                return x;
            }
        }
    }

    template<std::endian Endian, typename T>
    requires std::is_arithmetic_v<T> // Avoid our concepts header.
    [[nodiscard]] constexpr T endian_convert(const T n) noexcept {
        if constexpr (std::endian::native != Endian) {
            return swap_endian(n);
        } else {
            return n;
        }
    }

} // namespace bj.