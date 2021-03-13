// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <bj/binaryizer/binaryizer.hpp>

struct emplacey {

    int x{};

    mutable int binarized{};
    int debinarized{};

    auto operator<=>(const emplacey &) const = default;

    bool operator==(const emplacey & rhs) const noexcept {
        return x == rhs.x;
    }

    emplacey(int n) : x{ n } {}

    emplacey(bj::ibinaryizer &in) {
        in(x);
        ++debinarized;
    }

    void binaryize(bj::obinaryizer &out) const {
        out(x);
        ++binarized;
    }

};