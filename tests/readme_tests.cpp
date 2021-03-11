// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

// Prove that *all* code in README is correct.

#include <sstream>
#include <catch2/catch.hpp>
#include <bj/binaryizer/iostream_binaryizer.hpp>

namespace readme_internal {
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

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };
} // namespace readme_internal.

namespace readme_external {
    struct thing {
        int a, b, c;
    
        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };

    template<typename Archive>
    void binaryize(Archive &archive, const thing &e) {
        archive(e.a, e.b, e.c);
    }

    template<typename Archive>
    void debinaryize(Archive &archive, thing &e) {
        archive(e.a, e.b, e.c);
    }

} // namespace readme_external.

namespace readme_versioning {

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

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };

} // namespace readme_versioning.

// Save a couple of runtime tests.
static_assert(bj::is_binaryizable_v<readme_internal::thing>);
static_assert(bj::is_binaryizable_v<readme_external::thing>);
static_assert(bj::is_binaryizable_v<readme_versioning::thing>);

TEST_CASE("readme internal methods", "[readme,internal]") {

    readme_internal::thing thing1{ .a = 1, .b = 3, .c = 5 };
    readme_internal::thing thing2{ .a = 2, .b = 4, .c = 6 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme external methods", "[readme,external]") {

    readme_external::thing thing1{ .a = 1, .b = 3, .c = 5 };
    readme_external::thing thing2{ .a = 2, .b = 4, .c = 6 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme versioning methods", "[readme,internal,versioning]") {

    readme_versioning::thing thing1{ .a = 1, .b = 3, .c = 5, .d = 7 };
    readme_versioning::thing thing2{ .a = 2, .b = 4, .c = 6, .d = 8 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme versioning correctness", "[readme,internal,versioning]") {

    readme_versioning::thing thing1{ .a = 1, .b = 3, .c = 5, .d = 7 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    obin(thing1);

    int version{}, a{}, b{}, c{}, d{};
    ibin(version, a, b, c, d);
    REQUIRE(version == 2);
    REQUIRE(a == 1);
    REQUIRE(b == 3);
    REQUIRE(c == 5);
    REQUIRE(d == 7);
}