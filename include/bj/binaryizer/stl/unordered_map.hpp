// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <unordered_map>
#include "../binaryizer.hpp"
#include "pair.hpp"

namespace bj {

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::unordered_map<Key, T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_map<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            std::pair<Key, T> p;
            in(p);
            data.insert(p);
        }
    }

    template<typename Key, debinaryizer_constructable T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_map<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            Key k;
            in(k);
            data.emplace(k, in);
        }
    }

} // namespace bj.