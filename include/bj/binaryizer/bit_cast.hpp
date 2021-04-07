// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <type_traits>
#include <cstring>

namespace bj::inline v1::impl {

    // courtesy of cppreference until vendors catch up.
    template <class To, class From>
    requires (sizeof(To) == sizeof(From) && std::is_trivially_copyable_v<From> && std::is_trivially_copyable_v<To>)
    To 
    //typename std::enable_if_t<
    //    sizeof(To) == sizeof(From) &&
    //    std::is_trivially_copyable_v<From> &&
    //    std::is_trivially_copyable_v<To>,
    //    To>
        // constexpr support needs compiler magic
        bit_cast(const From &src) noexcept
    {
        static_assert(std::is_trivially_constructible_v<To>,
            "This implementation additionally requires destination type to be trivially constructible");

        To dst;
        std::memcpy(&dst, &src, sizeof(To));
        return dst;
    }

} // namespace bj::::inline v1impl.