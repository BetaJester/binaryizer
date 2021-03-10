// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <fmt/format.h>

struct exttester {

    int a{};
    int b{};
    int c{};

    mutable int binarized{};
    int debinarized{};

    auto operator<=>(const exttester &) const = default;

    bool operator==(const exttester &rhs) const noexcept {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }

    friend std::ostream &operator<<(std::ostream &out, const exttester &x) {
        return out << fmt::format("[{},{},{}]", x.a, x.b, x.c);
    }

};

template<typename Archive>
void binaryize(Archive &archive, const exttester &e) {
    archive(e.a, e.b, e.c);
    ++e.binarized;
}

template<typename Archive>
void debinaryize(Archive &archive, exttester &e) {
    archive(e.a, e.b, e.c);
    ++e.debinarized;
}