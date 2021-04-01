// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include <cstring> // memcpy.
#include "traits_n_concepts.hpp"

namespace bj::inline v1{

    template<typename T, std::size_t Size = 1024u>
    class buffered;

    template<ibufferable Parent, std::size_t Size>
    class [[nodiscard]] buffered<Parent, Size> : public Parent {
            
        std::array<std::byte, Size> buffer;
        std::size_t count{};
        std::size_t binbegin{};

        [[nodiscard]] std::size_t available() const noexcept { return count - binbegin; }

        std::size_t reload() {
            count = Parent::getraw(buffer.data(), Size);
            binbegin = 0;
            return count;
        }

    public:

        template<typename ...Args>
        buffered(Args &&...args)
            : Parent(std::forward<Args>(args)...) {}

        buffered(const buffered &) noexcept = default;
        buffered(buffered &&) noexcept = default;

        std::size_t getraw(std::byte *const data, const std::size_t size) override {

            // Hypophosis:
            //
            // A. We have enough data (or size is 0).
            // B. We don't have enough data (or no data).
            //
            // A B
            // 1 0 - Give them the data, if empty, reload.
            // 0 1 - Give them what (if any) data, we have, reload, recursive call with adjusted numbers.
            // 1 1 - Not possible.

            if (size <= available()) {
                std::memcpy(data, buffer.data() + binbegin, size);
                binbegin += size;
                if (available() == 0) {
                    reload();
                }
                return size;
            } else {
                const auto can_give = available();
                std::memcpy(data, buffer.data() + binbegin, can_give);
                reload();
                return getraw(data + can_give, size - can_give) + can_give;
            }
        }

    };

    template<obufferable Parent, std::size_t Size>
    class [[nodiscard]] buffered<Parent, Size> : public Parent {

        std::array<std::byte, Size> buffer;
        std::size_t count{};

        [[nodiscard]] std::size_t available() const noexcept { return Size - count; }

    public:

        template<typename ...Args>
        buffered(Args &&...args)
            : Parent(std::forward<Args>(args)...) {}

        buffered(const buffered &) noexcept = default;
        buffered(buffered &&) noexcept = default;

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

        void flush() noexcept {
            if (count) {
                Parent::putraw(buffer.data(), count);
                count = 0;
            }
        }

    };

    //template<iobufferable Parent, std::size_t Size>
    //class [[nodiscard]] buffered<Parent, Size> : public Parent {
    //
    //    struct buffer_t {
    //        std::array<std::byte, Size> buffer;
    //        std::size_t count{};
    //    };
    //
    //    buffer_t bin, bout;
    //    std::size_t binbegin{};
    //
    //    [[nodiscard]] std::size_t invailable() const noexcept { return bin.count - binbegin; }
    //    [[nodiscard]] std::size_t outvailable() const noexcept { return Size - bout.count; }
    //
    //    std::size_t reload() {
    //        bin.count = Parent::getraw(bin.buffer.data(), Size);
    //        binbegin = 0;
    //        return bin.count;
    //    }
    //
    //public:
    //
    //    template<typename ...Args>
    //    buffered(Args &&...args)
    //        : Parent(std::forward<Args>(args)...) {}
    //
    //    buffered(const buffered &) noexcept = default;
    //    buffered(buffered &&) noexcept = default;
    //
    //    ~buffered() noexcept {
    //        flush();
    //    }
    //
    //    void putraw(const std::byte *const data, const std::size_t size) override {
    //        if (size < outvailable()) {
    //            std::memcpy(bout.buffer.data() + bout.count, data, size);
    //            bout.count += size;
    //        } else if (size > Size) {
    //            flush();
    //            Parent::putraw(data, size);
    //        } else {
    //            flush();
    //            std::memcpy(bout.buffer.data(), data, size);
    //            bout.count += size;
    //        }
    //    }
    //
    //    std::size_t getraw(std::byte *const data, const std::size_t size) override {
    //
    //        // Hypophosis:
    //        //
    //        // If there is output data, piss it off so it's available for input.
    //        //
    //        // A. We have enough data (or size is 0).
    //        // B. We don't have enough data (or no data).
    //        //
    //        // A B
    //        // 1 0 - Give them the data, if empty, reload.
    //        // 0 1 - Give them what (if any) data, we have, reload, recursive call with adjusted numbers.
    //        // 1 1 - Not possible.
    //
    //        flush();
    //
    //        if (size <= invailable()) {
    //            std::memcpy(data, bin.buffer.data() + binbegin, size);
    //            binbegin += size;
    //            if (invailable() == 0) {
    //                reload();
    //            }
    //            return size;
    //        } else {
    //            const auto can_give = invailable();
    //            std::memcpy(data, bin.buffer.data() + binbegin, can_give);
    //            reload();
    //            return getraw(data + can_give, size - can_give) + can_give;
    //        }
    //    }
    //
    //    void flush() noexcept {
    //        if (bout.count) {
    //            Parent::putraw(bout.buffer.data(), bout.count);
    //            bout.count = 0;
    //        }
    //    }
    //
    //};

} // namespace bj.