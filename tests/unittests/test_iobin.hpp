// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <sstream>
#include <bj/binaryizer/io/fstream_binaryizer.hpp>
#include <bj/binaryizer/io/stringstream_binaryizer.hpp>

inline auto test_ibin() {
    return bj::ifstream_binaryizer{"unittests.bin"};
}

inline auto test_obin() {
    return bj::ofstream_binaryizer{"unittests.bin"};
}

inline auto test_iobin() {
    return bj::stringstream_binaryizer{};
}