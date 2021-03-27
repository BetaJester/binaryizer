// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bit>

namespace bj {

    // Arithmetic type endian fixes.

#if defined(BJ_FORCE_ENDIAN_LITLE)
#define BJ_FORCE_ENDIAN_OUT_LITLE
#define BJ_FORCE_ENDIAN_IN_LITLE
#elif defined (BJ_FORCE_ENDIAN_BIG)
#define BJ_FORCE_ENDIAN_OUT_BIG
#define BJ_FORCE_ENDIAN_IN_BIG
#endif 

#if defined(BJ_FORCE_ENDIAN_OUT_LITLE)
    constexpr std::endian forced_endian_out = std::endian::little;
#elif defined (BJ_FORCE_ENDIAN_OUT_BIG)
    constexpr std::endian forced_endian_out = std::endian::big;
#else
    constexpr std::endian forced_endian_out = std::endian::native;
#endif

#if defined(BJ_FORCE_ENDIAN_IN_LITLE)
    constexpr std::endian forced_endian_in = std::endian::little;
#elif defined (BJ_FORCE_ENDIAN_IN_BIG)
    constexpr std::endian forced_endian_in = std::endian::big;
#else
    constexpr std::endian forced_endian_in = std::endian::native;
#endif

#if defined(BJ_32BIT_CONTAINER_SIZE)
    constexpr bool containers_32bit_size = true;
#else
    constexpr bool containers_32bit_size = false;
#endif

#if defined(BJ_MIDIINT_CONTAINER_SIZE)
    constexpr bool containers_midiint_size = true;
#else
    constexpr bool containers_midiint_size = false;
#endif

} // namespace bj.