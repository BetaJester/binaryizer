// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <set>
#include "../binaryizer.hpp"
#include "size.hpp"

namespace bj {

    template<typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::set<T, Compare, Alloc> &data) {
        impl::put_size(out, data.size());
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::set<T, Compare, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            // Not a huge fan of this.
            T t;
            in(t);
            data.insert(t);
        }
    }

    template<debinaryizer_constructable T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::set<T, Compare, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace(in);
        }
    }

} // namespace bj.