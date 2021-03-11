// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bit>
#include <type_traits>
#include <cstdint>
#include <cstring>

namespace bj {

    class ibinaryizer;
    class obinaryizer;
    class iobinaryizer;

    // Concepts / traits for output.

    template<typename T>
    concept binaryizable_internal = requires(const T t, obinaryizer & b) { t.binaryize(b); };

    template<typename T>
    concept binaryizable_external = requires(const T t, obinaryizer & b) { binaryize(b, t); };

    template<typename T>
    struct is_binaryizable {
        static constexpr bool value{ false };
    };

    template<binaryizable_internal T>
    struct is_binaryizable<T> {
        static constexpr bool value{ true };
    };

    template<binaryizable_external T>
    struct is_binaryizable<T> {
        static constexpr bool value{ true };
    };

    template<typename T> constexpr bool is_binaryizable_v = is_binaryizable<T>::value;

    template<typename T>
    concept binaryizable = binaryizable_external<T> or binaryizable_internal<T>;

    // Concepts / traits for input.

    template<typename T>
    concept debinaryizable_internal = requires(T t, ibinaryizer & b) { t.debinaryize(b); };

    template<typename T>
    concept debinaryizable_external = requires(T t, ibinaryizer & b) { debinaryize(b, t); };

    template<typename T>
    struct is_debinaryizable {
        static constexpr bool value{ false };
    };

    template<debinaryizable_internal T>
    struct is_debinaryizable<T> {
        static constexpr bool value{ true };
    };

    template<debinaryizable_external T>
    struct is_debinaryizable<T> {
        static constexpr bool value{ true };
    };

    template<typename T> constexpr bool is_debinaryizable_v = is_debinaryizable<T>::value;

    template<typename T>
    concept debinaryizable = debinaryizable_external<T> or debinaryizable_internal<T>;

    // And how the crap isn't this supplied?
    template<typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    // GCC is making me angry, this fixes an ambiguous call.
    template<typename T>
    concept unknown = std::is_arithmetic_v<T> == false && is_binaryizable_v<T> == false;

    // Arithmetic type endian fixes.

#if defined(BJ_FORCE_ENDIAN_OUT_LITLE)
    constexpr std::endian forced_endian_out = std::endian::little;
#elif defined (BJ_FORCE_ENDIAN_OUT_BIG)
    constexpr std::endian forced_endian_out = std::endian::big;
#else
    constexpr std::endian forced_endian_out = std::endian::native;
#endif // BJ_FORCE_LITTLE_ENDIAN

#if defined(BJ_FORCE_ENDIAN_IN_LITLE)
    constexpr std::endian forced_endian_in = std::endian::little;
#elif defined (BJ_FORCE_ENDIAN_IN_BIG)
    constexpr std::endian forced_endian_in = std::endian::big;
#else
    constexpr std::endian forced_endian_in = std::endian::native;
#endif // BJ_FORCE_LITTLE_ENDIAN
    
    namespace derp {
        // courtesy of cppreference until vendors catch up.
        template <class To, class From>
        typename std::enable_if_t<
            sizeof(To) == sizeof(From) &&
            std::is_trivially_copyable_v<From> &&
            std::is_trivially_copyable_v<To>,
            To>
            // constexpr support needs compiler magic
            bit_cast(const From &src) noexcept
        {
            static_assert(std::is_trivially_constructible_v<To>,
                "This implementation additionally requires destination type to be trivially constructible");

            To dst;
            std::memcpy(&dst, &src, sizeof(To));
            return dst;
        }
    } // namespace derp.

    template<arithmetic T>
    [[nodiscard]] constexpr T swap_endian(const T n) noexcept {
        if constexpr (std::is_same_v<T, float>) {
            const auto nf = derp::bit_cast<std::uint32_t>(n);
            return derp::bit_cast<float>(((nf >> 24) & 0xFF) | ((nf << 8) & 0xFF0000) | ((nf >> 8) & 0xFF00) | ((nf << 24) & 0xFF000000));
        }
        if constexpr (std::is_same_v<T, double>) {
            auto x = derp::bit_cast<std::uint64_t>(n);
            x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
            x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
            x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
            return derp::bit_cast<double>(x);
        }
        if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) == 1) return n;
            if constexpr (sizeof(T) == 2) return (n << 8) | (n >> 8);
            if constexpr (sizeof(T) == 4) return ((n >> 24) & 0xFF) | ((n << 8) & 0xFF0000) | ((n >> 8) & 0xFF00) | ((n << 24) & 0xFF000000);
            if constexpr (sizeof(T) == 8) {
                T x = n;
                x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
                x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
                x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
                return x;
            }
        }
    }
    
    template<std::endian Endian, arithmetic T>
    [[nodiscard]] constexpr T endian_convert(const T n) noexcept {
        if constexpr (std::endian::native != Endian) {
            return swap_endian(n);
        } else {
            return n;
        }
    }

    // Class for output.

    class [[nodiscard]] obinaryizer {

    protected:

        template<typename T>
        void puttem(const T &data) {
            putraw(reinterpret_cast<const std::byte *>(&data), sizeof(T));
        }

        template<typename T, std::size_t N>
        void putarr(const T (&data)[N]) {
            putraw(reinterpret_cast<const std::byte *>(data), sizeof(T) * N);
        }

    public:
        
        virtual ~obinaryizer() = default;
        
        virtual void putraw(const std::byte *const data, const std::size_t size) = 0;

        template<unknown T>
        void put(const T data) {
            puttem(data);
        }

        template<arithmetic T>
        void put(const T data) {
            puttem(endian_convert<forced_endian_out>(data));
        }

        template<typename T, std::size_t N>
        void put(const T (&data)[N]) {
            putarr(data);
        }

        template<binaryizable T, std::size_t N>
        void put(const T(&data)[N]) {
            for (const auto &x : data) {
                put(x);
            }
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

    // Class for input.

    class [[nodiscard]] ibinaryizer {

    public:

        virtual ~ibinaryizer() = default;
        virtual void getraw(std::byte *const data, const std::size_t size) = 0;

        template<typename T>
        void gettem(T &data) {
            getraw(reinterpret_cast<std::byte *>(&data), sizeof(T));
        }

        template<typename T, std::size_t N>
        void gettem(T (&data)[N]) {
            getraw(reinterpret_cast<std::byte *>(data), sizeof(T) * N);
        }

        template<typename T>
        void get(T &data) {
            gettem(data);
        }

        template<arithmetic T>
        void get(T &data) {
            gettem(data);
            data = endian_convert<forced_endian_in>(data);
        }

        template<arithmetic T>
        [[nodiscard]] T get() {
            T data;
            get(data);
            return data;
        }

        template<typename T, std::size_t N>
        void get(T(&data)[N]) {
            gettem(data);
        }

        template<binaryizable T, std::size_t N>
        void get(T(&data)[N]) {
            for (auto &x : data) {
                get(x);
            }
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
        void get(T &t) {
            t.debinaryize(*this);
        }

        template<debinaryizable_external T>
        void get(T &t) {
            debinaryize(*this, t);
        }

    };

    // Helper class for easy child classes.

    class [[nodiscard]] iobinaryizer : public ibinaryizer, public obinaryizer {};

} // namespace ragl.