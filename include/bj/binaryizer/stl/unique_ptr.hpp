// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <memory>
#include "../binaryizer.hpp"

namespace bj::inline v1{

    template<typename T, typename Deleter>
    inline void binaryize(obinaryizer &out, const std::unique_ptr<T, Deleter> &data) {
        if (data) {
            out.put<std::uint8_t>(1);
            out(*data);
        } else {
            out.put<std::uint8_t>(0);
        }
    }

    template<typename T, typename Deleter>
    inline void debinaryize(ibinaryizer &in, std::unique_ptr<T, Deleter> &data) {
        const auto is_set = in.get<std::uint8_t>();
        if (is_set) {
            data = std::make_unique<T>();
            in(*data);
        }
    }

    template<debinaryizer_constructable T, typename Deleter>
    inline void debinaryize(ibinaryizer &in, std::unique_ptr<T, Deleter> &data) {
        const auto is_set = in.get<std::uint8_t>();
        if (is_set) {
            data = std::make_unique<T>(in);
        }
    }

} // namespace bj::inline v1.