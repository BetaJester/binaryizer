// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <fmt/format.h>

struct county {

    int a{};
    int b{};
    int c{};

    mutable int binarized{};
    int debinarized{};

    auto operator<=>(const county &) const = default;

    bool operator==(const county &rhs) const noexcept {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }

    template<typename Archive>
    void binaryize(Archive &archive) const {
        archive(a, b, c);
        ++binarized;
    }

    template<typename Archive>
    void debinaryize(Archive &archive) {
        archive(a, b, c);
        ++debinarized;
    }

    friend std::ostream &operator<<(std::ostream &out, const county &x) {
        return out << fmt::format("[{},{},{}]", x.a, x.b, x.c);
    }

};