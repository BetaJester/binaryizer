# bj::binaryizer
Header only C++ serialization library with an annoying to type name.

[![CMake](https://github.com/BetaJester/binaryizer/actions/workflows/cmake.yml/badge.svg)](https://github.com/BetaJester/binaryizer/actions/workflows/cmake.yml)

```
// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.
```

* [Overview](#overview)
* [Requirements](#requirements)
* [Usage](#usage)
* [Versioning your binaries](#versioning-your-binaries)
* [Endian Conversion](#endian-conversion)
* [Raw Output](#raw-output)
* [Other Notes](#other-notes)
* [TODO](#todo)


## Overview

Binaryizer is a relatively simple serialization library for C++. The goals are to allow several possible methods to serialize and deserialize objects with as little overhead as possible.

## Requirements

* C++20
  * Clang 10 tested
  * GCC 10 tested
  * MSVC 19.28 tested

## Usage

Very simple - your class or struct needs one or two functions/methods, `binaryize` and `debinaryize`. 

**As class methods**

```cpp
struct thing {
	int a, b, c;

    template<typename Archive>
    void binaryize(Archive &archive) const {
        archive(a, b, c);
    }

    template<typename Archive>
    void debinaryize(Archive &archive) {
        archive(a, b, c);
    }
};
```

**As standalone functions**

```cpp
struct thing {
    int a, b, c;
};

template<typename Archive>
void binaryize(Archive &archive, const thing &e) {
    archive(e.a, e.b, e.c);
}

template<typename Archive>
void debinaryize(Archive &archive, thing &e) {
    archive(e.a, e.b, e.c);
}
```

Note the use of templates with no indication that this library is being used, or any interest in what `Archive` is, simply that it is callable with a variable number of arguments. This allows classes to be created without even including the library headers, zero dependencies.

If you are using standalone functions, it is best to place them in the same namespace as your class ([ADL](https://en.cppreference.com/w/cpp/language/adl) will find it), in the global namespace, or in the `bj` namespace if you don't want to pollute the global namespace.

You can of course use `bj::ibinaryizer` and `bj::obinaryizer` as arguments instead of templates, which is needed when using inheritance and is best when using another type of debinaryizing, constructors.

**With constructors**

```cpp
struct thing {
    int a, b, c;

    thing(bj::ibinaryizer &archive) {
        archive(a, b, c);
    }

    void binaryize(bj::obinaryizer &archive) const {
        archive(a, b, c);
    }
};
```

This actually gives an advantage if you are using STL containers, as they can use emplace methods instead of default constructing and then debinaryizing an object. If you binaryize your object in the correct way and it contains objects that can be debinaryized, you can pass the object to them during construction too. 

## Versioning your binaries

It's not a bad idea to spend a few bytes to version your classes, allowing for future changes. Here, assume versioning was always used (it's quite hard to add it later) and that version 1 had `a`, `b` and `c` members and version 2 added a `d` member.

```cpp
struct thing {
    int a, b, c;
    int d;

    template<typename Archive>
    void binaryize(Archive &archive) const {
        archive(2, a, b, c, d);
    }

    template<typename Archive>
    void debinaryize(Archive &archive) {
        const int version = archive.template get<int>();
        switch (version) {
        case 1: 
            archive(a, b, c);
            d = 5;
            break;
        case 2:
            archive(a, b, c, d);
            break;
        default:
            throw std::runtime_error("Unknown version for 'thing' in binary");
        }
    }
};
```

As long as newly added members have a sensible default (or calculable) value, expansion of classes is pretty painless. This allows you to load older data, and the next time it is saved the new data will be version 2.

You may note the use of `archive.template get<int>();` in the above. It would have been easy to use `archive(version)` but const correctness can be important, and some items must be constructed using an `ibanaryizer`. Only arithmetic, boolean, and objects constructible using an `ibinaryizer` can be retrieved this way. The awkward `template` in the method is only needed when using the anonymous template method style above.

## Endian Conversion

Under normal use, the endianness of data is ignored and the native endian is used. There is a flag to change this.

* BJ_FORCE_ENDIAN_LITLE
* BJ_FORCE_ENDIAN_BIG

They set these flags, which can usually be just left alone unless you are doing something unusual.

* BJ_FORCE_ENDIAN_OUT_LITLE
* BJ_FORCE_ENDIAN_OUT_BIG
* BJ_FORCE_ENDIAN_IN_LITLE
* BJ_FORCE_ENDIAN_IN_BIG

It's important to note that if you force the endianness that would be used by the build natively there is zero cost. So, it's not a bad idea to "force" the endian you are far more likely to be using and it's only a cost if you build for an exotic system. As of 2021 all x86, x86_64 (Windows & macOS), "Apple Silicon" (new ARM based macOS), Android devices and iOS devices are little endian, so chances are high if you define BJ_FORCE_ENDIAN_LITLE in your build settings (more reliable than defining per file) you will never pay any cost for it.

## Raw Output

There is three ways to output a class/struct as completely raw data. This could be done for speed or specific formats. Note that endianness is totally ignored for raw data, and things like STL containers and pointers will just get pushed through with no conversion and nearly certainly cause errors when reloaded.

**expbin**

Used *at the point of reading or writing* `expbin` can explicitly output the raw data of information without interfering with the type system. It uses references, no copies of data are made.

```cpp
struct rawdata {
    int x, y, z;
};

struct thing {
    rawdata data;
    int a, b, c;

    void binaryize(bj::obinaryizer &out) const {
        out(bj::expbin(data), a, b, c);
    }

    void debinaryize(bj::ibinaryizer &in) {
        in(bj::expbin(data), a, b, c);
    }
};
```

**binwrap**

Items can be wrapped by `binwrap` to make them explicitly output as raw data. Can be used to store items in containers with no overhead. Dereferencing `*` and `->` operators are overloaded, and the internal `item` is exposed for aggregate construction and access.

```cpp
struct rawdata {
    int x, y, z;
};

struct thing {
    bj::binwrap<rawdata> data;
    int a, b, c;

    void binaryize(bj::obinaryizer &out) const {
        out(data, a, b, c);
    }

    void debinaryize(bj::ibinaryizer &in) {
        in(data, a, b, c);
    }
};
```

**explicitly_raw**

Lastly, items can be marked as explicitly convertible to raw data with a template overload. This is probably the path of least resistance, and works with minimal effort if the data is in a container, with no overhead or maintenance.

```cpp
struct rawdata {
    int x, y, z;
};
    
namespace bj {
    template<> struct explicitly_raw<rawdata> : std::true_type {};
} // namespace bj.

struct thing {
    rawdata data;
    int a, b, c;

    void binaryize(bj::obinaryizer &out) const {
        out(data, a, b, c);
    }

    void debinaryize(bj::ibinaryizer &in) {
        in(data, a, b, c);
    }
};
```

## STL Support

Virtually all STL containers are supported, including some of the more obscure ones.

Some containers that use contiguous data (including C style arrays) such as `std::vector`, `std::array` can output data in large chunks instead of piece by piece, when the data is useable for [raw output](#raw-output) or is an arithmetic type and the [endian](#endian-conversion) is not set or set to the same as the native endian.

`std::unique_ptr` will save the object it holds following the same rules as normal objects, and reconstruct them on debinaryizing. `std::shared_pointer` and raw pointers have no sensible owner rules that make sense for this library, the user must handle this themselves.

`std::pair` and `std::tuple` are useable if the items they contain play by the same rules as any other type recognized. Tuples are binaryized and debinaryized in reverse to allow items that require a `ibinaryizer` constructor argument, this passes tests in MSVC, Clang and GCC, and should be noted if the exact output file format is important.

## Midi Numbers

It is possible to output numbers in a 7 bit encoded format. I refer to this as midi format, as the midi file format is a heavy user of it.

Basically, integers are output 7 bits at a time with a flag bit to signify if another 7 bits is needed for more data. This means for example numbers between 0 and 127 are output in a single byte, 0 and 16,383 in two bytes, and so on.

This can save space in the output at a small cost of added computations, and needs to be considered for the use case. For example if you have a large number of 64 bit numbers, likely all to be low, the savings could be great, but if they are all very close to the maximum value for 64 bit (18,446,744,073,709,551,615) they can actually take a byte *more* each to store with midi numbers.

Works best for unsigned integers, also works with signed integers but the another least significant bit is added to keep track of sign, which may (or may not) increase the size by a byte, depending on the data.

## Other Notes

* Because the underlying size of `bool` isn't defined by the standard, it is always done as `std::uint8_t`, unless part of raw output when it is whatever your compiler uses.

## TODO

- [x] STL header & tests (finish containers)
- [x] Endian optional & tests, like every endian flip possibility
- [x] Endian ignored for contiguous data if not applicable to optimize
- [x] Unique pointers & tests
- [ ] Inheritance docs and tests
- [ ] Document all methods
- [ ] Expose all methods?
- [x] Constructor
- [ ] std::range
- [ ] Damn std::vector<bool>?
- [ ] Double check license on all files, all files in cmake lists.
- [ ] Refactor tests for easier everything
- [ ] std::optional / any support
- [ ] Fix signed midi numbers