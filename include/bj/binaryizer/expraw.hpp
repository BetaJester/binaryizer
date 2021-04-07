// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <compare>
#include <cstdint>

namespace bj::inline v1{

    template<typename T>
    class [[nodiscard]] expraw final {

    public:

        using type = std::decay_t<T>;

        T item;

        expraw() noexcept = default;
        //expraw(T t) noexcept : item{ t } {}
        template<typename ...Args> expraw(Args &&...args) noexcept : item{ std::forward<Args>(args)... } {}


        template<typename Archive>
        void binaryize(Archive &out) const {
            out.putraw(reinterpret_cast<const std::byte*>(&item), sizeof(item));
        }

        template<typename Archive>
        void debinaryize(Archive &in) {
            in.getraw(reinterpret_cast<std::byte*>(&item), sizeof(item));
        }

        [[nodiscard]] type *operator->() noexcept { return &item; }
        [[nodiscard]] const type *operator->() const noexcept { return &item; }
        [[nodiscard]] T &operator*() noexcept { return item; }
        [[nodiscard]] const T &operator*() const noexcept { return item; }

        auto operator<=>(const expraw &) const = default;
    };

    // Deduction guide.
    template<typename T>
    expraw(T &)->expraw<T &>;

    // Deduction guide.
    template<typename T>
    expraw(T &&)->expraw<const T>;

} // namespace bj::inline v1.