// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

// Conversion algorithms courtesy of...
// http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html#BMA2_

#include <type_traits>
#include <cstdint>

namespace bj {

    template<typename T>
    requires (std::is_integral_v<T> && std::is_unsigned_v<T> && sizeof(T) > 1)
    class [[nodiscard]] midiint final {

        T &item;

    public:

        midiint(T &t) noexcept : item{ t } {}

        template<typename Archive>
        void binaryize(Archive &out) const {

            T temp = item;
            T buff = temp & 0x7F;
            while ((temp >>= 7) > 0) {
                buff <<= 8;
                buff |= 0x80;
                buff += temp & 0x7F;
            }

            while (true) {
                out(static_cast<std::uint8_t>(buff));
                if (buff & 0x80) {
                    buff >>= 8;
                } else {
                    break;
                }
            }

        }

        template<typename Archive>
        void debinaryize(Archive &in) {

            T value{};
            std::uint8_t c{};
            if (value = in.template get<std::uint8_t>(); value & 0x80) {
                value &= 0x7F;
                do {
                    value = (value << 7) + ((c = in.template get<std::uint8_t>()) & 0x7F);
                } while (c & 0x80);
            }
            item = value;

        }

    };

} // namespace bj.