// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <valarray>
#include "../binaryizer.hpp"
#include "size.hpp"

namespace bj::inline v1{

    template<typename T>
    inline void binaryize(obinaryizer &out, const std::valarray<T> &data) {
        impl::put_size(out, data.size());
        out.put(std::begin(data), std::end(data));
    }

    template<typename T>
    inline void debinaryize(ibinaryizer &in, std::valarray<T> &data) {
        const auto size = impl::get_size(in);
        data.resize(size);
        in.get(std::begin(data), std::end(data));
    }

} // namespace bj::inline v1.