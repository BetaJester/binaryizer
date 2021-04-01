// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <sstream>
#include "../binaryizer.hpp"

namespace bj {

    class [[nodiscard]] stringstream_binaryizer final : public iobinaryizer{

        std::stringstream m_stream;

    public:

        stringstream_binaryizer() : m_stream{ std::ios::in | std::ios::out | std::ios::binary } {}

        std::ptrdiff_t getraw(std::byte *const data, const std::size_t size) override {
            m_stream.read(reinterpret_cast<char *>(data), static_cast<std::streamsize>(size));
            const auto amount = m_stream.gcount();
            return static_cast<std::ptrdiff_t>(amount);
        }

        void putraw(const std::byte *const data, const std::size_t size) override {
            m_stream.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
        }

        [[nodiscard]] std::stringstream &stream() { return m_stream; }
        [[nodiscard]] bool good() const { return m_stream.good(); }

    };

} // namespace bj.