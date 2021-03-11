// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include "binaryizer.hpp"

namespace bj {

    template<typename IOStream>
    class iostream_binaryizer final : public iobinaryizer {

        IOStream m_stream;

    protected:

        void putraw(const std::byte *const data, const std::size_t size) override {
            m_stream.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
        }

        void getraw(std::byte *const data, const std::size_t size) override {
            m_stream.read(reinterpret_cast<char *>(data), static_cast<std::streamsize>(size));
        }

    public:

        template<typename ...Args>
        iostream_binaryizer(Args &&...args)
            : m_stream(std::forward<Args>(args)...) {}

        [[nodiscard]] IOStream &stream() noexcept { return m_stream; }
        [[nodiscard]] const IOStream &stream() const noexcept { return m_stream; }

        void rewind() {
            m_stream.flush();
            m_stream.seekg(0);
            m_stream.seekp(0);
        }

        [[nodiscard]] bool good() const { return m_stream.good(); }

    };

} // namespace bj.