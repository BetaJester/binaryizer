// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <utility>

namespace bj::inline v1{

    // Brilliant idea courtesy of https://twitter.com/The_Whole_Daisy/status/1379580525078147072?s=20
    template<typename Fn, typename ...Types>
    void do_backwards(Fn &fn, Types &&...ts) {
        struct assignable {};
        auto do_one = [&](auto &t) {
            fn(t);
            return assignable{};
        };
        (do_one(std::forward<Types>(ts)) = ...); // op= is right associative :)
    }

} // namespace bj::inline v1.