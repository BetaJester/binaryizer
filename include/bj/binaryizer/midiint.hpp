// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <type_traits>
#include <cstdint>
#include "stackstack.hpp"

namespace bj {

    //void what1() {
    //    int y = -2;
    //    fmt::print("{0:#x} ({0})\n", y);
    //    unsigned int x = bit_cast<unsigned int>(~y);
    //    fmt::print("{0:#x} ({0})\n", x);
    //    y = bit_cast<int>(~x);
    //    fmt::print("{0:#x} ({0})\n", y);
    //}

    template<typename T>
    requires (std::is_integral_v<T> && sizeof(T) > 1)
    class [[nodiscard]] midiint final {

        T &item;

    public:

        explicit midiint(T &t) noexcept : item{ t } {}

        template<typename Archive>
        void binaryize(Archive &out) const {

            if (item == 0) {
                out.template put<std::uint8_t>(0);
                return;
            }

            std::uintmax_t temp{};

            if constexpr (std::is_signed_v<T>) {
                temp = derp::bit_cast<std::make_unsigned_t<T>>(~item);
            } else {
                temp = item;
            }

            // TODO: Calculate largest actually needed for type.
            stackstack<std::uint8_t, 10> buffer;

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

            item = 0;
            for (auto it = buffer.rbegin(); it < buffer.rend(); ++it) {
                item = (item << 7) | *it;
            }

            if constexpr (std::is_signed_v<T>) {
                if (item != 0) {
                    item = derp::bit_cast<T>(~item);
                }
            }

        }

    };

} // namespace bj.