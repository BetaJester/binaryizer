// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <algorithm>
#include <iterator>
#include <cstdint>

#include "traits_n_concepts.hpp"
#include "endian.hpp"

namespace bj::inline v1{

    // Class for input.

    class [[nodiscard]] ibinaryizer {

    protected:

        template<typename T>
        void gettem(T &data) {
            getraw(reinterpret_cast<std::byte *>(&data), sizeof(T));
        }

        template<typename T, std::size_t N>
        void gettem(T(&data)[N]) {
            getraw(reinterpret_cast<std::byte *>(data), sizeof(T) * N);
        }

    public:

        virtual ~ibinaryizer() = default;
        virtual std::ptrdiff_t getraw(std::byte *const data, const std::size_t size) = 0;

        template<explicity_raw_in T>
        void get(T &data) {
            gettem(data);
        }

        template<arithmetic_not_raw_in T>
        void get(T &data) {
            gettem(data);
            data = endian_convert<forced_endian_in>(data);
        }

        template<boolean T>
        void get(T &data) {
            data = get<std::uint8_t>();
        }

        template<arithmetic T>
        [[nodiscard]] T get() {
            T data;
            get(data);
            return data;
        }

        template<debinaryizer_constructable T>
        [[nodiscard]] T get() {
            return T{ *this };
        }

        template<debinaryizable T>
        [[nodiscard]] T get() {
            T t;
            get(t);
            return t;
        }

        template<explicity_raw_in T, std::size_t N>
        void get(T(&data)[N]) {
            gettem(data);
        }

        template<not_raw_in T, std::size_t N>
        void get(T(&data)[N]) {
            get(std::begin(data), std::end(data));
        }

        template<std::forward_iterator It>
        void get(It first, It last) {
            std::for_each(first, last, [this](auto &x) { this->get(x); });
        }

        template<typename ...Args>
        void operator()(Args &&...args) {
            (get(std::forward<Args>(args)), ...);
        }

        template<debinaryizable_internal T>
        void get(T &&t) {
            t.debinaryize(*this);
        }

        template<debinaryizable_external T>
        void get(T &&t) {
            debinaryize(*this, t);
        }

    };

} // namespace bj::inline v1.