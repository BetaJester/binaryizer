// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <type_traits>
#include <cstdint>
#include "stackstack.hpp"

namespace bj {

    template<typename T>
    requires (std::is_integral_v<T> && std::is_unsigned_v<T> && sizeof(T) > 1)
    class [[nodiscard]] midiint final {

        T &item;

    public:

        midiint(T &t) noexcept : item{ t } {}

        template<typename Archive>
        void binaryize(Archive &out) const {

            if (item == 0) {
                out.template put<std::uint8_t>(0);
                return;
            }

            // TODO: Calculate largest actually needed for type.
            stackstack<std::uint8_t, 10> buffer;

            std::uintmax_t temp = item;

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

        }

    };

} // namespace bj.