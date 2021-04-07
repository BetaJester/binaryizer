// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <tuple>
#include <type_traits>

namespace bj::inline v1{

    // Largely courtesy of https://codereview.stackexchange.com/questions/142804/get-n-th-data-member-of-a-struct
    namespace impl {

        struct filler { template<typename type> operator type (); };


        template<typename aggregate, typename index_sequence = std::index_sequence<>, typename = void>
        struct aggregate_arity : index_sequence {};

        template<typename aggregate, std::size_t ...indices>
        struct aggregate_arity <aggregate, std::index_sequence<indices...>,
               std::void_t<decltype(aggregate{(indices, std::declval<impl::filler>())...,
               std::declval<impl::filler>()})>>
            : aggregate_arity<aggregate, std::index_sequence<indices..., sizeof...(indices)>> {};
    
    } // namespace impl.

    template<typename T>
    constexpr std::size_t arity() noexcept {
        return impl::aggregate_arity<std::decay_t<T>>::size();
    }

    template<typename T>
    auto to_tuple(T &t) noexcept {
        constexpr auto a = arity<T>();
        if constexpr (a ==  0) { return std::tie(); } else
        if constexpr (a ==  1) { auto &[p0] = t; return std::tie(p0); } else
        if constexpr (a ==  2) { auto &[p0, p1] = t; return std::tie(p0, p1); } else
        if constexpr (a ==  3) { auto &[p0, p1, p2] = t; return std::tie(p0, p1, p2); } else
        if constexpr (a ==  4) { auto &[p0, p1, p2, p3] = t; return std::tie(p0, p1, p2, p3); } else
        if constexpr (a ==  5) { auto &[p0, p1, p2, p3, p4] = t; return std::tie(p0, p1, p2, p3, p4); } else
        if constexpr (a ==  6) { auto &[p0, p1, p2, p3, p4, p5] = t; return std::tie(p0, p1, p2, p3, p4, p5); } else
        if constexpr (a ==  7) { auto &[p0, p1, p2, p3, p4, p5, p6] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6); } else
        if constexpr (a ==  8) { auto &[p0, p1, p2, p3, p4, p5, p6, p7] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7); } else
        if constexpr (a ==  9) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8); } else
        if constexpr (a == 10) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } else
        if constexpr (a == 11) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } else
        if constexpr (a == 12) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } else
        if constexpr (a == 13) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } else
        if constexpr (a == 14) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } else
        if constexpr (a == 15) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } else
        if constexpr (a == 16) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); } else
        if constexpr (a == 17) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } else
        if constexpr (a == 18) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); } else
        if constexpr (a == 19) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } else
        if constexpr (a == 20) { auto &[p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19] = t; return std::tie(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); }
    }

    template<typename T, typename F>
    void for_each_aggregate(T &t, F &&f) {
        std::apply([&](auto &&...args) { ((void)f(args), ...); }, to_tuple(t));
    }

    template<typename T>
    class [[nodiscard]] parsed final {

    public:

        using type = std::decay_t<T>;

        T item;

        parsed() noexcept = default;
        template<typename ...Args> parsed(Args &&...args) noexcept : item{ std::forward<Args>(args)... } {}


        template<typename Archive>
        void binaryize(Archive &out) const {
            bj::for_each_aggregate(item, [&](auto a) { out(a); });
        }

        template<typename Archive>
        void debinaryize(Archive &in) {
            bj::for_each_aggregate(item, [&](auto &a) { in(a); });
        }

        [[nodiscard]] type *operator->() noexcept { return &item; }
        [[nodiscard]] const type *operator->() const noexcept { return &item; }
        [[nodiscard]] T &operator*() noexcept { return item; }
        [[nodiscard]] const T &operator*() const noexcept { return item; }

        auto operator<=>(const parsed &) const = default;
    };

    // Deduction guide.
    template<typename T>
    parsed(T &)->parsed<T &>;

    // Deduction guide.
    template<typename T>
    parsed(T &&)->parsed<const T>;

} // namespace bj::inline v1.