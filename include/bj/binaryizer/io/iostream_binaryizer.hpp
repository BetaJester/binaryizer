// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include "../binaryizer.hpp"

namespace bj {

    template<typename Stream>
    class stream_base {

    protected:

        Stream m_stream;

    public:

        template<typename ...Args>
        stream_base(const std::ios::openmode flags, Args &&...args) : m_stream{ std::forward<Args>(args)..., flags } {}

        [[nodiscard]] Stream &stream() noexcept { return m_stream; }
        [[nodiscard]] const Stream &stream() const noexcept { return m_stream; }

        [[nodiscard]] bool good() const { return m_stream.good(); }

    };

    template<typename IStream>
    class istream_binaryizer : public ibinaryizer, public stream_base<IStream> {

    protected:

        using stream_base<IStream>::m_stream;

    public:

        template<typename ...Args>
        istream_binaryizer(const std::ios::openmode flags, Args &&...args) : stream_base<IStream>{ flags, std::forward<Args>(args)... } {}

        std::ptrdiff_t getraw(std::byte *const data, const std::size_t size) override {
            m_stream.read(reinterpret_cast<char *>(data), static_cast<std::streamsize>(size));
            const auto amount = m_stream.gcount();
            return static_cast<std::ptrdiff_t>(amount);
        }

    };

    template<typename OStream>
    class ostream_binaryizer : public obinaryizer, public stream_base<OStream> {

    protected:

        using stream_base<OStream>::m_stream;

    public:

        template<typename ...Args>
        ostream_binaryizer(const std::ios::openmode flags, Args &&...args) : stream_base<OStream>{ flags, std::forward<Args>(args)... } {}

        void putraw(const std::byte *const data, const std::size_t size) override {
            m_stream.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
        }

    };

} // namespace bj.