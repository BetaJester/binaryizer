// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <sstream>
#include <bj/binaryizer/iostream_binaryizer.hpp>

inline auto test_iobin() {
    return bj::iostream_binaryizer<std::stringstream>(std::ios::binary | std::ios::in | std::ios::out);
}