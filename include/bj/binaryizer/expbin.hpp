// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <compare>
#include <utility>

namespace bj {

    //template<typename T>
    //class [[nodiscard]] binwrap final {
    //
    //public:
    //
    //    T item;
    //
    //    [[nodiscard]] T *operator->() noexcept { return &item; }
    //    [[nodiscard]] const T *operator->() const noexcept { return &item; }
    //    [[nodiscard]] T &operator*() noexcept { return item; }
    //    [[nodiscard]] const T &operator*() const noexcept { return item; }
    //
    //    auto operator<=>(const binwrap &) const = default;
    //
    //};

    template<typename T>
    class [[nodiscard]] expbin final {

    public:

        using type = std::decay_t<T>;

        T item;

        template<typename Archive>
        void binaryize(Archive &out) const {
            out.putraw(reinterpret_cast<const std::byte*>(&item), sizeof(item));
        }

        template<typename Archive>
        void debinaryize(Archive &in) {
            in.getraw(reinterpret_cast<std::byte*>(&item), sizeof(item));
        }

        //explicit expbin(T &t) noexcept : item{ t } {}
        //expbin() = delete;
        //expbin(const expbin &) = delete;
        //expbin(expbin &&) = delete;
        //expbin &operator=(const expbin &) = delete;
        //expbin &operator=(expbin &&) = delete;

        [[nodiscard]] type *operator->() noexcept { return &item; }
        [[nodiscard]] const type *operator->() const noexcept { return &item; }
        [[nodiscard]] T &operator*() noexcept { return item; }
        [[nodiscard]] const T &operator*() const noexcept { return item; }

        auto operator<=>(const expbin &) const = default;
    };

    // Deduction guide.
    template<typename T>
    expbin(T &)->expbin<T &>;

    // Deduction guide.
    template<typename T>
    expbin(T &&)->expbin<const T>;

} // namespace bj.