// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <set>
#include "../binaryizer.hpp"
#include "size.hpp"

namespace bj::inline v1{

    template<typename Key, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::multiset<Key, Compare, Alloc> &data) {
        impl::put_size(out, data.size());
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::multiset<Key, Compare, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            // Not a huge fan of this.
            Key t;
            in(t);
            data.insert(t);
        }
    }

    template<debinaryizer_constructable Key, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::multiset<Key, Compare, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace(in);
        }
    }

} // namespace bj::inline v1.