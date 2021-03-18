// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include <optional>

namespace bj {

    template<class T, std::size_t N>
    class [[nodiscard]] stackstack final {

        std::size_t m_count{};
        std::array<T, N> m_array{};

    public:

        stackstack() noexcept = default;

        constexpr void push(const T &item) noexcept {
            m_array[m_count++] = item;
        }

        [[nodiscard]] constexpr std::optional<T> pop() noexcept {
            if (m_count > 0) {
                return m_array[--m_count];
            } else {
                return {};
            }
        }

        [[nodiscard]] constexpr T& top() noexcept {
            return m_array[m_count - 1];
        }

        constexpr void clear() noexcept {
            m_count = 0;
        }

        [[nodiscard]] constexpr bool empty() const noexcept { return m_count == 0; }

        [[nodiscard]] constexpr std::size_t size() const noexcept { return m_count; }
        [[nodiscard]] constexpr std::size_t capacity() const noexcept { return N; }

        [[nodiscard]] constexpr auto begin() noexcept(noexcept(m_array.begin())) { return m_array.begin(); }
        [[nodiscard]] constexpr auto begin() const noexcept(noexcept(m_array.begin())) { return m_array.begin(); }
        [[nodiscard]] constexpr auto end() noexcept(noexcept(m_array.begin())) { return m_array.begin() + m_count; }
        [[nodiscard]] constexpr auto end() const noexcept(noexcept(m_array.begin())) { return m_array.begin() + m_count; }
        [[nodiscard]] constexpr auto rbegin() noexcept(noexcept(m_array.rbegin())) { return m_array.rbegin() + static_cast<std::ptrdiff_t>(N - m_count); }
        [[nodiscard]] constexpr auto rbegin() const noexcept(noexcept(m_array.rbegin())) { return m_array.rbegin() + (N - m_count); }
        [[nodiscard]] constexpr auto rend() noexcept(noexcept(m_array.rend())) { return m_array.rend(); }
        [[nodiscard]] constexpr auto rend() const noexcept(noexcept(m_array.rend())) { return m_array.rend(); }
        [[nodiscard]] constexpr auto cbegin() const noexcept(noexcept(m_array.cbegin())) { return m_array.cbegin(); }
        [[nodiscard]] constexpr auto cend() const noexcept(noexcept(m_array.cbegin())) { return m_array.cbegin() + m_count; }
        [[nodiscard]] constexpr auto crbegin() const noexcept(noexcept(m_array.crbegin())) { return m_array.crbegin() + static_cast<std::ptrdiff_t>(N - m_count); }
        [[nodiscard]] constexpr auto crend() const noexcept(noexcept(m_array.crend())) { return m_array.crend(); }

    };

} // namespace sgg::utility.