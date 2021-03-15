// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

struct nobin {
    int a{};
    bool b{};
    float c{};

    auto operator<=>(const nobin &) const = default;
};