// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include "ibinaryizer.hpp"
#include "obinaryizer.hpp"

namespace bj::inline v1{

    // Helper class for easy child classes.
    class [[nodiscard]] iobinaryizer : public ibinaryizer, public obinaryizer {
    
    public:
    
        ibinaryizer &as_in()  { return *this; }
        obinaryizer &as_out() { return *this; }
    
        template<typename ...Args>
        void in(Args &&...args) {
            (as_in()(std::forward<Args>(args)), ...);
        }
    
        template<typename ...Args>
        void out(Args &&...args) {
            (as_out()(std::forward<Args>(args)), ...);
        }
    
    };

} // namespace bj::inline v1.