// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <string>
#include "../binaryizer.hpp"

namespace bj {

    template<typename T, typename Traits, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::basic_string<T, Traits, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Traits, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::basic_string<T, Traits, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

} // namespace bj.