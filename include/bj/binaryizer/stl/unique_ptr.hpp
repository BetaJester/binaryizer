// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <memory>
#include "../binaryizer.hpp"

namespace bj {

    template<typename T, typename Deleter>
    inline void binaryize(obinaryizer &out, const std::unique_ptr<T, Deleter> &data) {
        out(*data);
    }

    template<typename T, typename Deleter>
    inline void debinaryize(ibinaryizer &in, std::unique_ptr<T, Deleter> &data) {
        if (!data) {
            data = std::make_unique<T>();
        }
        in(*data);
    }

    template<debinaryizable_emplace T, typename Deleter>
    inline void debinaryize(ibinaryizer &in, std::unique_ptr<T, Deleter> &data) {
        data = std::make_unique<T>(in);
    }

} // namespace bj.