// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

// Prove that *all* code in README is correct.

#include <sstream>
#include <catch2/catch.hpp>
#include <bj/binaryizer/iostream_binaryizer.hpp>
#include <bj/binaryizer/midiint.hpp>
#include <bj/binaryizer/expraw.hpp>

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

namespace readme_constructable {
    struct thing {
        int a, b, c;

        thing(bj::ibinaryizer &archive) {
            archive(a, b, c);
        }

        void binaryize(bj::obinaryizer &archive) const {
            archive(a, b, c);
        }

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };
} // namespace readme_constructable.

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

namespace readme_expraw {
    struct rawdata {
        int x, y, z;

        // Not in readme.
        auto operator<=>(const rawdata &) const = default;
    };

    struct thing {
        rawdata data;
        int a, b, c;

        void binaryize(bj::obinaryizer &out) const {
            out(bj::expraw(data), a, b, c);
        }

        void debinaryize(bj::ibinaryizer &in) {
            in(bj::expraw(data), a, b, c);
        }

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };
} // namespace readme_expraw.

namespace readme_expraw_wrap {
    struct rawdata {
        int x, y, z;

        // Not in readme.
        auto operator<=>(const rawdata &) const = default;
    };

    struct thing {
        bj::expraw<rawdata> data;
        int a, b, c;

        void binaryize(bj::obinaryizer &out) const {
            out(data, a, b, c);
        }

        void debinaryize(bj::ibinaryizer &in) {
            in(data, a, b, c);
        }

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };
} // namespace readme_expraw_wrap.

namespace readme_explicitly_raw {
    struct rawdata {
        int x, y, z;

        // Not in readme.
        auto operator<=>(const rawdata &) const = default;
    };
} // namespace readme_explicitly_raw.
    
namespace bj {
    template<> struct explicitly_raw<readme_explicitly_raw::rawdata> : std::true_type {};
} // namespace bj.


namespace readme_explicitly_raw {
    struct thing {
        rawdata data;
        int a, b, c;

        void binaryize(bj::obinaryizer &out) const {
            out(data, a, b, c);
        }

        void debinaryize(bj::ibinaryizer &in) {
            in(data, a, b, c);
        }

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };
} // namespace readme_explicitly_raw.

namespace readme_midiint_basic {

    struct thing {
        int a, b, c;

        template<typename Archive>
        void binaryize(Archive &archive) const {
            archive(bj::midiint(a), bj::midiint(b), bj::midiint(c));
        }

        template<typename Archive>
        void debinaryize(Archive &archive) {
            archive(bj::midiint(a), bj::midiint(b), bj::midiint(c));
        }

        // Not in readme.
        auto operator<=>(const thing &) const = default;
    };

} // namespace readme_midiint_basic.

namespace readme_midiint_wrap {

    struct thing {
        bj::midiint<int> a, b, c;

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

} // namespace readme_midiint_wrap.

namespace readme_midiint_explicit {

    struct thing {
        int a, b, c;
        int d;

        template<typename Archive>
        void binaryize(Archive &archive) const {
            archive(bj::midiint<std::uint32_t>(2), a, b, c, d);
        }

        template<typename Archive>
        void debinaryize(Archive &archive) {
            const auto version = archive.template get<bj::midiint<std::uint32_t>>();
            switch (version.item) {
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

} // namespace readme_midiint_explicit.

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

TEST_CASE("readme constructing methods", "[readme,constructing]") {

    // Same internal structure.
    readme_internal::thing thing1{ .a = 1, .b = 3, .c = 5 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    obin(thing1);
    readme_constructable::thing thing2(ibin);
    obin(thing2);
    readme_constructable::thing thing3(ibin);

    REQUIRE(thing2 == thing3);

}

TEST_CASE("readme expbin methods", "[readme,expraw]") {

    readme_expraw::thing thing1{ .data{.x = 7, .y = 8, .z = 9}, .a = 1, .b = 3, .c = 5 };
    readme_expraw::thing thing2{ .data{.x = 0, .y = 10, .z = 11}, .a = 2, .b = 4, .c = 6 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme binwrap methods", "[readme,expraw,wrap]") {

    readme_expraw_wrap::thing thing1{ .data = { 7, 8, 9},  .a = 1, .b = 3, .c = 5 };
    readme_expraw_wrap::thing thing2;

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme explicitly_raw methods", "[readme,explicitly_raw]") {

    readme_explicitly_raw::thing thing1{ .data{.x = 7, .y = 8, .z = 9}, .a = 1, .b = 3, .c = 5 };
    readme_explicitly_raw::thing thing2{ .data{.x = 0, .y = 10, .z = 11}, .a = 2, .b = 4, .c = 6 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme midiint basic", "[readme,midiint,basic]") {

    readme_midiint_basic::thing thing1{ .a = 1, .b = 3, .c = 5 };
    readme_midiint_basic::thing thing2{ .a = 2, .b = 4, .c = 6 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme midiint wrapped", "[readme,midiint,wrap]") {

    readme_midiint_wrap::thing thing1{ .a = 1, .b = 3, .c = 5 };
    readme_midiint_wrap::thing thing2{ .a = 2, .b = 4, .c = 6 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}

TEST_CASE("readme midiint explicit", "[readme,midiint,explicit]") {

    readme_midiint_explicit::thing thing1{ .a = 1, .b = 3, .c = 5, .d = 7 };
    readme_midiint_explicit::thing thing2{ .a = 2, .b = 4, .c = 6, .d = 8 };

    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::binary | std::ios::in | std::ios::out);
    bj::ibinaryizer &ibin = iobin;
    bj::obinaryizer &obin = iobin;

    REQUIRE(thing1 != thing2);
    obin(thing1);
    ibin(thing2);
    REQUIRE(thing1 == thing2);
}