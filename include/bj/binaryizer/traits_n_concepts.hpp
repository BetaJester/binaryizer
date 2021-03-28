// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <type_traits>
#include "settings.hpp"
#include "expbin.hpp"

namespace bj {

    class ibinaryizer;
    class obinaryizer;
    class iobinaryizer;

    // How the crap isn't this supplied?
    template<typename T> concept boolean = std::is_same_v<T, bool>;
    template<typename T> concept arithmetic = std::is_arithmetic_v<T> && !boolean<T>;

    template<typename T> concept binaryizable_internal = requires(const T t, obinaryizer & b) { t.binaryize(b); };
    template<typename T> concept binaryizable_external = requires(const T t, obinaryizer & b) { binaryize(b, t); };
    template<typename T> concept debinaryizable_internal = requires(T t, ibinaryizer & b) { t.debinaryize(b); };
    template<typename T> concept debinaryizable_external = requires(T t, ibinaryizer & b) { debinaryize(b, t); };
    
    template<typename T> concept binaryizable = binaryizable_external<T> or binaryizable_internal<T>;
    template<typename T> concept debinaryizable = debinaryizable_external<T> or debinaryizable_internal<T>;

    template<typename T> concept debinaryizer_constructable = std::is_constructible_v<T, ibinaryizer &>;

    template<typename T> struct is_binaryizable : std::false_type {};
    template<binaryizable T> struct is_binaryizable<T> : std::true_type {};
    template<typename T> constexpr bool is_binaryizable_v = is_binaryizable<T>::value;
    template<typename T> struct is_debinaryizable : std::false_type {};
    template<debinaryizable T> struct is_debinaryizable<T> : std::true_type {};
    template<typename T> constexpr bool is_debinaryizable_v = is_debinaryizable<T>::value;
    
    template<typename T> concept arithmetic_native_out = arithmetic<T> && forced_endian_out == std::endian::native;
    template<typename T> concept arithmetic_not_raw_out = arithmetic<T> && forced_endian_out != std::endian::native;
    template<typename T> concept arithmetic_native_in = arithmetic<T> && forced_endian_in == std::endian::native;
    template<typename T> concept arithmetic_not_raw_in = arithmetic<T> && forced_endian_in != std::endian::native;

    template<typename T> concept not_raw_in = arithmetic_not_raw_in<T> || debinaryizable<T>;
    template<typename T> concept not_raw_out = arithmetic_not_raw_out<T> || binaryizable<T>;

    // Explicity raw output allowed.
    //template<typename T> struct is_binwrapped : std::false_type {};
    //template<typename T> struct is_binwrapped<binwrap<T>> : std::true_type {};
    //template<typename T> constexpr bool is_binwrapped_v = is_binwrapped<T>::value;
    //template<typename T> struct is_expbin : std::false_type {};
    //template<typename T> struct is_expbin<expbin<T>> : std::true_type {};
    //template<typename T> constexpr bool is_expbin_v = is_expbin<T>::value;
    template<typename T> struct explicitly_raw : std::false_type {};
    template<typename T> constexpr bool explicitly_raw_v = explicitly_raw<T>::value;
    
    template<typename T> concept explicity_raw_in = /*is_binwrapped_v<T> ||*/ arithmetic_native_in<T> || explicitly_raw_v<T>;
    template<typename T> concept explicity_raw_out = /*is_binwrapped_v<T> ||*/ arithmetic_native_out<T> || explicitly_raw_v<T>;


} // namespace bj.