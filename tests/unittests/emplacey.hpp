// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <fmt/format.h>
#include <bj/binaryizer/binaryizer.hpp>

struct emplacey {

    int x{};

    mutable int binarized{};
    int debinarized{};

    auto operator<=>(const emplacey &) const = default;

    bool operator==(const emplacey & rhs) const noexcept {
        return x == rhs.x;
    }

    //emplacey() noexcept = default;
    emplacey(int n) : x{ n } {}
    //emplacey(emplacey &&) noexcept = default;
    //emplacey(const emplacey &) noexcept = default;
    //emplacey &operator=(emplacey &&) noexcept = default;
    //emplacey &operator=(const emplacey &) noexcept = default;

    emplacey(bj::ibinaryizer &in) {
        in(x);
        ++debinarized;
    }

    void binaryize(bj::obinaryizer &out) const {
        out(x);
        ++binarized;
    }

    friend std::ostream &operator<<(std::ostream &out, const emplacey &x) {
        return out << fmt::format("[{}]", x.x);
    }

};

namespace std {
    template <>
    struct hash<emplacey> {
        [[nodiscard]] size_t operator()(const emplacey &val) const noexcept {
            return std::hash<int>()(val.x);
        }
    };
} // namespace std.