// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <deque>
#include "../binaryizer.hpp"
#include "size.hpp"

namespace bj {

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::deque<T, Alloc> &data) {
        impl::put_size(out, data.size());
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::deque<T, Alloc> &data) {
        const auto size = impl::get_size(in);
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    template<debinaryizer_constructable T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::deque<T, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace_back(in);
        }
    }

} // namespace bj.