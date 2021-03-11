// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include "ibinaryizer.hpp"
#include "obinaryizer.hpp"

namespace bj {

    // Helper class for easy child classes.
    class [[nodiscard]] iobinaryizer : public ibinaryizer, public obinaryizer {};

} // namespace bj.