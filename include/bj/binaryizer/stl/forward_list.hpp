// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <forward_list>
#include "../binaryizer.hpp"

namespace bj {

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::forward_list<T, Alloc> &data) {
        std::uint32_t size{};
        for ([[maybe_unused]] const auto &d : data) ++size;
        out.put<std::uint32_t>(size);
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::forward_list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    template<debinaryizer_constructable T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::forward_list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        auto iter = data.before_begin();
        for (std::uint32_t i{}; i < size; ++i) {
            iter = data.emplace_after(iter, in);
        }
    }

} // namespace bj.