// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <iterator>
#include <cstdint>

#include "traits_n_concepts.hpp"
#include "endian.hpp"

namespace bj {

    class [[nodiscard]] obinaryizer {

    protected:

        template<typename T>
        void puttem(const T &data) {
            putraw(reinterpret_cast<const std::byte *>(&data), sizeof(T));
        }

        template<typename T, std::size_t N>
        void puttem(const T(&data)[N]) {
            putraw(reinterpret_cast<const std::byte *>(data), sizeof(T) * N);
        }

    public:

        virtual ~obinaryizer() = default;

        virtual void putraw(const std::byte *const data, const std::size_t size) = 0;

        //template<typename T> requires is_expbin_v<T>
        //    void put(T &&data) {
        //        puttem(*data);
        //    }

        template<explicity_raw_out T>
        void put(const T &data) {
            puttem(data);
        }

        template<arithmetic_not_raw_out T>
        void put(const T data) {
            puttem(endian_convert<forced_endian_out>(data));
        }

        template<boolean T>
        void put(const T data) {
            put<std::uint8_t>(data);
        }

        template<explicity_raw_out T, std::size_t N>
        void put(const T(&data)[N]) {
            puttem(data);
        }

        template<not_raw_out T, std::size_t N>
        void put(T(&data)[N]) {
            put(std::begin(data), std::end(data));
        }

        template<std::forward_iterator It>
        void put(It first, It last) {
            std::for_each(first, last, [this](auto &x) { this->put(x); });
        }

        template<typename ...Args>
        void operator()(Args &&...args) {
            (put(std::forward<Args>(args)), ...);
        }

        template<binaryizable_internal T>
        void put(const T &t) {
            t.binaryize(*this);
        }

        template<binaryizable_external T>
        void put(const T &t) {
            binaryize(*this, t);
        }

    };

} // namespace bj.