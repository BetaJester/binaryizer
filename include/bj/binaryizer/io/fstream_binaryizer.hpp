// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <fstream>
#include "iostream_binaryizer.hpp"

namespace bj {

    struct [[nodiscard]] ifstream_binaryizer : istream_binaryizer<std::ifstream> {
        ifstream_binaryizer(const std::string_view path, const std::ios::openmode extra = static_cast<std::ios::openmode>(0))
            : istream_binaryizer<std::ifstream>{ std::ios::binary | extra, path.data() } {}
    };

    struct [[nodiscard]] ofstream_binaryizer : ostream_binaryizer<std::ofstream> {
        ofstream_binaryizer(const std::string_view path, const std::ios::openmode extra = static_cast<std::ios::openmode>(0))
            : ostream_binaryizer<std::ofstream>{ std::ios::binary | extra, path.data() } {}
    };

} // namespace bj,