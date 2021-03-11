// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <type_traits>

namespace bj {

    class ibinaryizer;
    class obinaryizer;
    class iobinaryizer;

    // Concepts / traits for output.

    template<typename T>
    concept binaryizable_internal = requires(const T t, obinaryizer & b) { t.binaryize(b); };

    template<typename T>
    concept binaryizable_external = requires(const T t, obinaryizer & b) { binaryize(b, t); };

    template<typename T>
    struct is_binaryizable {
        static constexpr bool value{ false };
    };

    template<binaryizable_internal T>
    struct is_binaryizable<T> {
        static constexpr bool value{ true };
    };

    template<binaryizable_external T>
    struct is_binaryizable<T> {
        static constexpr bool value{ true };
    };

    template<typename T> constexpr bool is_binaryizable_v = is_binaryizable<T>::value;

    template<typename T>
    concept binaryizable = binaryizable_external<T> or binaryizable_internal<T>;

    // Concepts / traits for input.

    template<typename T>
    concept debinaryizable_internal = requires(T t, ibinaryizer & b) { t.debinaryize(b); };

    template<typename T>
    concept debinaryizable_external = requires(T t, ibinaryizer & b) { debinaryize(b, t); };

    template<typename T>
    struct is_debinaryizable {
        static constexpr bool value{ false };
    };

    template<debinaryizable_internal T>
    struct is_debinaryizable<T> {
        static constexpr bool value{ true };
    };

    template<debinaryizable_external T>
    struct is_debinaryizable<T> {
        static constexpr bool value{ true };
    };

    template<typename T> constexpr bool is_debinaryizable_v = is_debinaryizable<T>::value;

    template<typename T>
    concept debinaryizable = debinaryizable_external<T> or debinaryizable_internal<T>;

    // And how the crap isn't this supplied?
    template<typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    // GCC is making me angry, this fixes an ambiguous call.
    template<typename T>
    concept unknown = std::is_arithmetic_v<T> == false && is_binaryizable_v<T> == false;

} // namespace bj.