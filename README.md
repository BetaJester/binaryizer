# bj::binaryizer
Simple header only C++ serialization library with an annoying to type name.

[![CMake](https://github.com/BetaJester/binaryizer/actions/workflows/cmake.yml/badge.svg)](https://github.com/BetaJester/binaryizer/actions/workflows/cmake.yml)

```
// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.
```

## Requirements

* C++20

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

You can of course use `bj::ibinaryizable` and `bj::obinaryizable` as arguments instead of templates, which is needed when using inheritance and is best when using another type of debinaryizing: constructors.

**With constructors**

```cpp
struct thing {
    int a, b, c;
    
    thing(bj::ibinaryizer &in) {
        in(a, b, c);
    }
    
	void debinaryize(bj::obinaryizer &out) {
    	out(a, b, c);
	}
};
```

This actually gives (will anyway) an advantage if you are using STL containers, as they can use emplace methods instead of default constructing and then debinaryizing an object. If you binaryize your object in the correct way and it contains objects that can be debinaryized, you can pass the object to them during construction too. Advanced Example coming.

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

You may note the use of `archive.get<int>();`{:.language-cpp} in the above. There are a number of methods supported, they are listed in *coming soon, sorry*. It would have been easy to use `archive(version)` but const correctness can be important.



## TODO

- [ ] STL header & tests (finish containers)
- [x] Endian optional & tests, like every endian flip possibility.
- [ ] Endian ignored for contiguous data if not applicable to optimise
- [ ] Unique pointers & tests
- [ ] Inheritance docs and tests
- [ ] Document all methods
- [x] Expose all methods?
- [x] Constructor
- [ ] std::range
- [ ] Damn std::vector<bool>?