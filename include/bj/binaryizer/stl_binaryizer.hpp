// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <set>

#include "binaryizer.hpp"

namespace bj {

    // std::array.

    template<typename T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T, N> &data) {
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<norawable T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T, N> &data) {
        out.put(data.begin(), data.end());
    }

    template<typename T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T, N> &data) {
        in.getraw(reinterpret_cast<std::byte *>(data.data()), N * sizeof(T));
    }

    template<norawable T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T, N> &data) {
        in.get(data.begin(), data.end());
    }

    // std::vector.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::vector<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<norawable T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::vector<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::vector<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.getraw(reinterpret_cast<std::byte *>(data.data()), size * sizeof(T));
    }

    template<norawable T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::vector<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    // std::deque.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::deque<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::deque<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    // std::forward_list.

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

    // std::list.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::list<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    // std::basic_string.

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

    // std::set.

    template<typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::set<T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::set<T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        // TODO: This isn't good enough. Emplace? Constructors?
        for (std::uint32_t i{}; i < size; ++i) {
            T t;
            in(t);
            data.insert(t);
        }
    }

} // namespace bj.