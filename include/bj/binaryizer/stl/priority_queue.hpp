// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <queue>
#include "../binaryizer.hpp"
#include "inner_container.hpp"
#include "vector.hpp" // Default container.

namespace bj::inline v1{

    template<typename T, typename Container>
    inline void binaryize(obinaryizer &out, const std::priority_queue<T, Container> &data) {
        const Container &c = data.*(&inner_container<std::priority_queue<T, Container>>::c);
        out(c);
    }

    template<typename T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::priority_queue<T, Container> &data) {
        Container &c = data.*(&inner_container<std::priority_queue<T, Container>>::c);
        in(c);
    }

    template<debinaryizer_constructable T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::priority_queue<T, Container> &data) {
        Container &c = data.*(&inner_container<std::priority_queue<T, Container>>::c);
        in(c);
    }

} // namespace bj::inline v1.