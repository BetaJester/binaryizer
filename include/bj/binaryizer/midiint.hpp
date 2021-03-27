// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <type_traits>
#include <cstdint>
#include "stackstack.hpp"
#include "bit_cast.hpp"

namespace bj {

    namespace impl {

        template<typename T>
        requires (std::is_integral_v<T> && sizeof(T) > 1)
            class [[nodiscard]] midiint final {

            T &item;

            template<std::integral U>
            static U flip(const U &t) {
                using S = std::make_unsigned_t<U>;
                S s = impl::bit_cast<S>(t);
                s = ~s + 1;
                return impl::bit_cast<U>(s);
            }

            template<std::integral U>
            static std::make_unsigned_t<U> safeabs(const U &t) {
                using S = std::make_unsigned_t<U>;
                if (t >= 0) return static_cast<S>(t);
                S s = impl::bit_cast<S>(t);
                s = ~s + 1;
                return s;
            }

            public:

                explicit midiint(T &t) noexcept : item{ t } {}

                template<typename Archive>
                void binaryize(Archive &out) const {

                    if (item == 0) {
                        out.template put<std::uint8_t>(0);
                        return;
                    }

                    std::uintmax_t temp{};

                    bool is_negative{};
                    bool is_max_negative{};

                    if constexpr (std::is_signed_v<T>) {
                        is_negative = item < 0;
                        if constexpr (std::is_same_v<T, std::intmax_t>) {
                            is_max_negative = item == std::numeric_limits<T>::min();
                        }
                        temp = safeabs(item);
                        temp <<= 1; // Lost bit if is_max_negative.
                        temp |= is_negative ? 1 : 0;
                    } else {
                        temp = item;
                    }

                    // TODO: Calculate largest actually needed for type.
                    stackstack<std::uint8_t, 10> buffer;

                    // Edge case for absolute max (or would it be min :P) negative number
                    // and the highest bit size available. Replacing the lost bit.
                    if constexpr (std::is_signed_v<T> && std::is_same_v<T, std::intmax_t>) {
                        if (is_max_negative) {
                            std::uint8_t b = static_cast<std::uint8_t>(temp) & 0x7F;
                            b |= 0x80;
                            buffer.push(b);
                            temp >>= 7;
                            temp |= 1ull << (sizeof(std::uintmax_t) * 8 - 7);
                        }
                    }

                    while (temp > 0) {
                        std::uint8_t b = static_cast<std::uint8_t>(temp) & 0x7F;
                        if (temp > 127) {
                            b |= 0x80;
                        }
                        buffer.push(b);
                        temp >>= 7;
                    }

                    for (const auto b : buffer) {
                        out(b);
                    }

                }

                template<typename Archive>
                void debinaryize(Archive &in) {

                    stackstack<std::uint8_t, 10> buffer;

                    for (std::uint8_t c{}; true;) {
                        in(c);
                        buffer.push(c & 0x7F);
                        if ((c & 0x80) == 0) {
                            break;
                        }
                    }

                    std::uintmax_t temp{};
                    constexpr int loop_adjust = std::is_signed_v<T> ? 1 : 0;

                    for (auto it = buffer.rbegin(); it < buffer.rend() - loop_adjust; ++it) {
                        temp = (temp << 7) | *it;
                    }

                    if constexpr (std::is_signed_v<T>) {
                        const auto b = *buffer.begin();
                        const bool is_negative = b & 1;
                        temp = (temp << 6) | b >> 1;
                        if (is_negative) {
                            item = static_cast<T>(flip(temp));
                        } else {
                            item = static_cast<T>(temp);
                        }
                    } else {
                        item = static_cast<T>(temp);
                    }

                }

        };

        template<typename T>
        requires (std::is_integral_v<T> && sizeof(T) > 1)
            class [[nodiscard]] midiwrap final {

            public:

                T item;
                operator T &() noexcept { return item; }
                operator const T &() const noexcept { return item; }

                midiwrap() noexcept = default;
                midiwrap(const midiwrap &t) noexcept : item{ t } {}
                midiwrap(midiwrap &&t) noexcept : item{ std::forward<T>(t) } {}
                midiwrap &operator=(const midiwrap &t) noexcept { item = t.item; return *this; }
                midiwrap &operator=(midiwrap &&t) noexcept { item = std::forward<T>(t.item); return *this; }

                midiwrap(const T &t) noexcept : item{ t } {}
                midiwrap(T &&t) noexcept : item{ std::forward<T>(t) } {}
                midiwrap &operator=(const T &t) noexcept { item = t; return *this; }
                midiwrap &operator=(T &&t) noexcept { item = std::forward<T>(t); return *this; }

                template<typename Archive>
                void binaryize(Archive &out) const {
                    out(midiint(item));
                }

                template<typename Archive>
                void debinaryize(Archive &in) {
                    in(midiint(item));
                }

        };

    } // namespace impl.


    template<typename T>
    requires (std::is_integral_v<std::decay_t<T>> && sizeof(std::decay_t<T>) > 1)
    struct [[nodiscard]] midiint final {
        
        T item;

        midiint() noexcept = default;
        midiint(const T t) noexcept : item{ t } {}

        template<typename Archive>
        void binaryize(Archive &out) const {
            out(impl::midiint(item));
        }

        template<typename Archive>
        void debinaryize(Archive &in) {
            in(impl::midiint(item));
        }

        auto operator<=>(const midiint &) const = default;
    };

    // Deduction guide.
    template<typename T>
    requires (std::is_integral_v<std::decay_t<T>> && sizeof(std::decay_t<T>) > 1)
    midiint(T)->midiint<T &>;

} // namespace bj.