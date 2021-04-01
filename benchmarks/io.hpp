// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <bj/binaryizer/io/fstream_binaryizer.hpp>
#include <bj/binaryizer/io/stringstream_binaryizer.hpp>
#include <bj/binaryizer/buffered.hpp>

inline auto get_iobin_buffered_ifstream() {
    return bj::buffered<bj::ifstream_binaryizer>("testoutput.bin");
}

inline auto get_iobin_buffered_ofstream() {
    return bj::buffered<bj::ofstream_binaryizer>("testoutput.bin", std::ios::trunc);
}

inline auto get_iobin_ifstream() {
    return bj::ifstream_binaryizer("testoutput.bin");
}

inline auto get_iobin_ofstream() {
    return bj::ofstream_binaryizer("testoutput.bin", std::ios::trunc);
}