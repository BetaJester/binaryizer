// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <fstream>
#include "binaryizer.hpp"

namespace bj {

    class fstream_binaryizer final : public iobinaryizer {

        std::fstream file;

    protected:

        void putraw(const std::byte *const data, const std::size_t size) override {
            file.write(reinterpret_cast<const char *>(data), size);
        }

        void getraw(std::byte *const data, const std::size_t size) override {
            file.read(reinterpret_cast<char *>(data), size);
        }

    public:

        winbinaryizer(const std::string_view filename)
            : file(filename.data(), std::ios::binary | std::ios::in | std::ios::out) {}

        void rewind() {
            file.flush();
            file.seekg(0);
            file.seekp(0);
        }

    };

} // namespace bj.