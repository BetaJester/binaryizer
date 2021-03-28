// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include <cstring> // memcpy.
#include "traits_n_concepts.hpp"

namespace bj::inline v1{

    template<bufferable Parent, std::size_t Size = 1024u>
    class [[nodiscard]] buffered : public Parent {
    
        std::array<std::byte, Size> buffer;
        std::size_t count{};

        [[nodiscard]] std::size_t available() const noexcept { return Size - count; }

    public:

        template<typename ...Args>
        buffered(Args &&...args)
            : Parent(std::forward<Args>(args)...) {}

        ~buffered() noexcept {
            flush();
        }

        void putraw(const std::byte *const data, const std::size_t size) override {
            if (size < available()) {
                std::memcpy(buffer.data() + count, data, size);
                count += size;
            } else if (size > Size) {
                flush();
                Parent::putraw(data, size);
            } else {
                flush();
                std::memcpy(buffer.data(), data, size);
                count += size;
            }
        }

        void getraw(std::byte *const data, const std::size_t size) override {
            flush();
            Parent::getraw(data, size);
        }

        void flush() noexcept {
            Parent::putraw(buffer.data(), count);
            count = 0;
        }

    };

} // namespace bj.