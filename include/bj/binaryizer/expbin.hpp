// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <compare>
#include <utility>

namespace bj {

    template<typename T>
    class [[nodiscard]] binwrap final {

        T item;

    public:

        template<typename ...Args>
        explicit binwrap(Args &&...args) noexcept(noexcept(T{ std::forward<Args>(args)... }))
            : item{ std::forward<Args>(args)... } {}

        [[nodiscard]] T *operator->() noexcept { return *item; }
        [[nodiscard]] const T *operator->() const noexcept { return *item; }
        [[nodiscard]] T &operator*() noexcept { return item; }
        [[nodiscard]] const T &operator*() const noexcept { return item; }

        auto operator<=>(const binwrap &) const = default;

    };

    template<typename T>
    class [[nodiscard]] expbin final {

        T &item;

    public:

        explicit expbin(T &t) noexcept : item{ t } {}
        expbin() = delete;
        expbin(const expbin &) = delete;
        expbin(expbin &&) = delete;
        expbin &operator=(const expbin &) = delete;
        expbin &operator=(expbin &&) = delete;

        [[nodiscard]] T *operator->() noexcept { return &item; }
        [[nodiscard]] const T *operator->() const noexcept { return &item; }
        [[nodiscard]] T &operator*() noexcept { return item; }
        [[nodiscard]] const T &operator*() const noexcept { return item; }

        auto operator<=>(const expbin &) const = default;
    };

} // namespace bj.