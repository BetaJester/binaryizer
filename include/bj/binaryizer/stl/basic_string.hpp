// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <string>
#include "../binaryizer.hpp"
#include "size.hpp"

namespace bj::inline v1{

    template<explicity_raw_out T, typename Traits, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::basic_string<T, Traits, Alloc> &data) {
        impl::put_size(out, data.size());
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<explicity_raw_in T, typename Traits, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::basic_string<T, Traits, Alloc> &data) {
        const auto size = impl::get_size(in);
        data.resize(size);
        in.getraw(reinterpret_cast<std::byte *>(data.data()), size * sizeof(T));
    }

} // namespace bj::inline v1.