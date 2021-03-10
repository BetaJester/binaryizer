# binaryizer
Simple header only C++ serialization library

```
// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.
```

## Requirements

* C++20

## Usage

Very simple, your class or struct needs one or two functions/methods, `binaryize` and `debinaryize`. 

If they are class methods, the signature is as such:

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

If they are standalone functions the signature is such:

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

Note the intentional use of templates that have literally no indication that this library is being used, or any interest in what `Archive` is, simply that it is callable with a variable number of argument. This allows classes to be created without even including the library headers, zero dependencies.

If you are using standalone functions, it is best to place them in the same namespace as your class (it will work due to [Argument Dependent Lookup](https://en.cppreference.com/w/cpp/language/adl)), in the global namespace, or in the `bj` namespace if you don't want to pollute the global namespace.

