// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bit>
#include <type_traits>
#include <cstdint>
#include <cstring>

namespace bj {

    // Arithmetic type endian fixes.

#if defined(BJ_FORCE_ENDIAN_OUT_LITLE)
    constexpr std::endian forced_endian_out = std::endian::little;
#elif defined (BJ_FORCE_ENDIAN_OUT_BIG)
    constexpr std::endian forced_endian_out = std::endian::big;
#else
    constexpr std::endian forced_endian_out = std::endian::native;
#endif // BJ_FORCE_LITTLE_ENDIAN

#if defined(BJ_FORCE_ENDIAN_IN_LITLE)
    constexpr std::endian forced_endian_in = std::endian::little;
#elif defined (BJ_FORCE_ENDIAN_IN_BIG)
    constexpr std::endian forced_endian_in = std::endian::big;
#else
    constexpr std::endian forced_endian_in = std::endian::native;
#endif // BJ_FORCE_LITTLE_ENDIAN

    namespace derp {
        // courtesy of cppreference until vendors catch up.
        template <class To, class From>
        typename std::enable_if_t<
            sizeof(To) == sizeof(From) &&
            std::is_trivially_copyable_v<From> &&
            std::is_trivially_copyable_v<To>,
            To>
            // constexpr support needs compiler magic
            bit_cast(const From &src) noexcept
        {
            static_assert(std::is_trivially_constructible_v<To>,
                "This implementation additionally requires destination type to be trivially constructible");

            To dst;
            std::memcpy(&dst, &src, sizeof(To));
            return dst;
        }
    } // namespace derp.

    template<arithmetic T>
    [[nodiscard]] constexpr T swap_endian(const T n) noexcept {
        if constexpr (std::is_same_v<T, float>) {
            const auto nf = derp::bit_cast<std::uint32_t>(n);
            return derp::bit_cast<float>(((nf >> 24) & 0xFF) | ((nf << 8) & 0xFF0000) | ((nf >> 8) & 0xFF00) | ((nf << 24) & 0xFF000000));
        }
        if constexpr (std::is_same_v<T, double>) {
            auto x = derp::bit_cast<std::uint64_t>(n);
            x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
            x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
            x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
            return derp::bit_cast<double>(x);
        }
        if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) == 1) return n;
            if constexpr (sizeof(T) == 2) return (n << 8) | (n >> 8);
            if constexpr (sizeof(T) == 4) return ((n >> 24) & 0xFF) | ((n << 8) & 0xFF0000) | ((n >> 8) & 0xFF00) | ((n << 24) & 0xFF000000);
            if constexpr (sizeof(T) == 8) {
                T x = n;
                x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
                x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
                x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
                return x;
            }
        }
    }

    template<std::endian Endian, arithmetic T>
    [[nodiscard]] constexpr T endian_convert(const T n) noexcept {
        if constexpr (std::endian::native != Endian) {
            return swap_endian(n);
        } else {
            return n;
        }
    }

} // namespace bj.