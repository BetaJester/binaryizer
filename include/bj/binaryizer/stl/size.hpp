// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <cstdint>
#include "../binaryizer.hpp"
#include "../midiint.hpp"

namespace bj::inline v1::impl {

    inline void put_size(bj::obinaryizer &out, const std::size_t s) {
        if constexpr (!bj::containers_midiint_size) {
            if constexpr (bj::containers_32bit_size) {
                out.put(static_cast<std::uint32_t>(s));
            } else {
                out.put(static_cast<std::uint64_t>(s));
            }
        } else {
            if constexpr (bj::containers_32bit_size) {
                out.put<bj::midiint<std::uint32_t>>(static_cast<std::uint32_t>(s));
            } else {
                out.put<bj::midiint<std::uint64_t>>(s);
            }
        }
    }

    inline std::size_t get_size(bj::ibinaryizer &in) {
        if constexpr (!bj::containers_midiint_size) {
            if constexpr (bj::containers_32bit_size) {
                return in.get<std::uint32_t>();
            } else {
                #if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER)
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wuseless-cast"
                #endif
                return static_cast<std::size_t>(in.get<std::uint64_t>());
                #if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER)
                #pragma GCC diagnostic pop
                #endif
            }
        } else {
            if constexpr (bj::containers_32bit_size) {
                return in.get<bj::midiint<std::uint32_t>>().item;
            } else {
                return in.get<bj::midiint<std::uint64_t>>().item;
            }
        }
    }

} // namespace bj::impl.