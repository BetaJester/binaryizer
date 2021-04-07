// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

namespace bj::inline v1{

    // Protected access.
    // Underlying container in wrappers is always called "c".
    // Expecation: as protected (so accessible to third party classes) in the standard
    // this is unlikely to change. A class inheriting from a class, neither of which
    // use polymorphism, and adds no data members, will have the same layout as the parent
    // class. 

    template<class Parent>
    struct inner_container : Parent {
        using Parent::c;
    };

} // namespace bj::inline v1.