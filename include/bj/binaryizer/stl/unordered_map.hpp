// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <unordered_map>
#include "../binaryizer.hpp"
#include "size.hpp"
#include "pair.hpp"

namespace bj::inline v1{

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::unordered_map<Key, T, Compare, Alloc> &data) {
        impl::put_size(out, data.size());
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_map<Key, T, Compare, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            std::pair<Key, T> p;
            in(p);
            data.insert(p);
        }
    }

    template<typename Key, debinaryizer_constructable T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_map<Key, T, Compare, Alloc> &data) {
        const auto size = impl::get_size(in);
        for (std::uint32_t i{}; i < size; ++i) {
            Key k;
            in(k);
            data.emplace(k, in);
        }
    }

} // namespace bj::inline v1.