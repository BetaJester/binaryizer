#pragma once

#include <array>
#include <vector>
#include <deque>

#include "binaryizer.hpp"

namespace bj {

    // std::array.

    template<typename T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T,N> &data) {
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<binaryizable T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T,N> &data) {
        out.put(data.begin(), data.end());
    }

    template<typename T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T,N> &data) {
        in.getraw(reinterpret_cast<std::byte *>(data.data()), N * sizeof(T));
    }

    template<binaryizable T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T,N> &data) {
        in.get(data.begin(), data.end());
    }

    // std::vector.

    template<typename T>
    inline void binaryize(obinaryizer &out, const std::vector<T> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<binaryizable T>
    inline void binaryize(obinaryizer &out, const std::vector<T> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T>
    inline void debinaryize(ibinaryizer &in, std::vector<T> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.getraw(reinterpret_cast<std::byte *>(data.data()), size * sizeof(T));
    }

    template<binaryizable T>
    inline void debinaryize(ibinaryizer &in, std::vector<T> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    // std::deque.

    template<binaryizable T>
    inline void binaryize(obinaryizer &out, const std::deque<T> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<binaryizable T>
    inline void debinaryize(ibinaryizer &in, std::deque<T> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

} // namespace bj.