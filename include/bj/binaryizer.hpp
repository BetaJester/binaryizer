// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include <type_traits>
#include <vector>
#include <cstdint>

namespace bj {

    class ibinaryizer;
    class obinaryizer;
    class iobinaryizer;

    // Concepts / traits for output.

    template<typename T>
    concept binaryizable = requires(const T t, obinaryizer & b) { t.binaryize(b); };

    template<typename T>
    struct is_binaryizable {
        static constexpr bool value{ false };
    };

    template<binaryizable T>
    struct is_binaryizable<T> {
        static constexpr bool value{ true };
    };

    template<typename T> constexpr bool is_binaryizable_v = is_binaryizable<T>::value;


    // Concepts / traits for input.

    template<typename T>
    concept debinaryizable = requires(T t, ibinaryizer & b) { t.debinaryize(b); };

    template<typename T>
    struct is_debinaryizable {
        static constexpr bool value{ false };
    };

    template<debinaryizable T>
    struct is_debinaryizable<T> {
        static constexpr bool value{ true };
    };

    template<typename T> constexpr bool is_debinaryizable_v = is_debinaryizable<T>::value;

    // Class for output.

    class [[nodiscard]] obinaryizer {

    protected:

        virtual void putraw(const std::byte *const data, const std::size_t size) = 0;
        
        template<typename T>
        void puttem(const T &data) {
            putraw(reinterpret_cast<const std::byte *>(&data), sizeof(T));
        }

        template<typename T, std::size_t N>
        void putarr(const T (&data)[N]) {
            putraw(reinterpret_cast<const std::byte *>(data), sizeof(T) * N);
        }

    public:

        template<typename T>
        requires std::is_arithmetic_v<T>
        void put(const T data) {
            puttem(data);
        }

        template<typename T, std::size_t N>
        requires std::is_arithmetic_v<T>
        void put(const T (&data)[N]) {
            put<std::uint32_t>(N);
            putarr(data);
        }

        template<std::forward_iterator It>
        void put(It first, It last) {
            std::for_each(first, last, [this](auto &x) { this->put(x); });
        }

        template<typename T>
        void put(const std::vector<T> &data) {
            put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
            if constexpr (is_binaryizable_v<T>) {
                put(data.begin(), data.end());
            } else {
                putraw(reinterpret_cast<const std::byte*>(data.data()), data.size() * sizeof(T));
            }
        }

        template<typename T, std::size_t N>
        void put(const std::array<T, N> &data) {
            put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
            putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
        }

        template<typename ...Args>
        void operator()(Args &&...args) {
            (put(std::forward<Args>(args)), ...);
        }

        template<binaryizable T>
        void put(const T &t) {
            t.binaryize(*this);
        }

    };

    // Class for input.

    class [[nodiscard]] ibinaryizer {

    protected:

        virtual void getraw(std::byte *const data, const std::size_t size) = 0;

        template<typename T>
        void gettem(T &data) {
            getraw(reinterpret_cast<std::byte *>(&data), sizeof(T));
        }

        template<typename T, std::size_t N>
        void getarr(T (&data)[N]) {
            getraw(reinterpret_cast<std::byte *>(data), sizeof(T) * N);
        }

    public:

        template<typename T>
        requires std::is_arithmetic_v<T>
        void get(T &data) {
            gettem(data);
        }

        template<typename T>
        requires std::is_arithmetic_v<T>
        [[nodiscard]] T get() {
            T data;
            gettem(data);
            return data;
        }

        template<typename T, std::size_t N>
        requires std::is_arithmetic_v<T>
        void get(T (&data)[N]) {
            (void)get<std::uint32_t>();
            getarr(data);
        }

        template<std::forward_iterator It>
        void get(It first, It last) {
            std::for_each(first, last, [this](auto &x) { get(x); });
        }

        template<typename T>
        void get(std::vector<T> &data) {
            const std::uint32_t size = get<std::uint32_t>();
            data.resize(size);
            if constexpr (is_debinaryizable_v<T>) {
                get(data.begin(), data.end());
            } else {
                getraw(reinterpret_cast<std::byte *>(data.data()), size * sizeof(T));
            }
        }

        template<typename T, std::size_t N>
        void get(std::array<T,N> &data) {
            (void)get<std::uint32_t>();
            getraw(reinterpret_cast<std::byte *>(data.data()), data.size() * sizeof(T));
        }

        template<typename ...Args>
        void operator()(Args &&...args) {
            (get(std::forward<Args>(args)), ...);
        }

        template<debinaryizable T>
        void get(T &t) {
            t.debinaryize(*this);
        }

    };

    // Helper class for easy child classes.

    class [[nodiscard]] iobinaryizer : public ibinaryizer, public obinaryizer {};

} // namespace ragl.