// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <tuple>
#include "../binaryizer.hpp"

namespace bj {

    struct tupleoverload {

        template<typename T, typename ...Types>
        void operator()(obinaryizer &out, T &&t, Types &&...ts) {
            (*this)(out, std::forward<Types>(ts)...);
            out(std::forward<T>(t));
        }
        template<typename T>
        void operator()(obinaryizer &out, T &&t) {
            out(std::forward<T>(t));
        }

        template<typename T, typename ...Types>
        void operator()(ibinaryizer &in, T &&t, Types &&...ts) {
            (*this)(in, std::forward<Types>(ts)...);
            in(std::forward<T>(t));
        }
        template<typename T>
        void operator()(ibinaryizer &in, T &&t) {
            in(std::forward<T>(t));
        }

    };

    template<typename ...Types>
    inline void binaryize(obinaryizer &out, const std::tuple<Types...> &data) {
        tupleoverload tol;
        std::apply([&](const Types &...items) { tol(out, items...); }, data);
    }

    template<typename ...Types>
    inline void debinaryize(ibinaryizer &in, std::tuple<Types...> &data) {
        tupleoverload tol;
        std::apply([&](Types &...items) { tol(in, items...); }, data);
    }

} // namespace bj.