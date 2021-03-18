// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <string>
#include <catch2/catch.hpp>
#include <bj/binaryizer/stackstack.hpp>

TEST_CASE("bj::stackstack works forwards", "[stackstack,forwarditerate]") {

    bj::stackstack<char, 5> stack;
    REQUIRE(stack.capacity() == 5);
    REQUIRE(stack.size() == 0);

    stack.push('a');
    stack.push('b');
    stack.push('c');
    stack.push('d');
    stack.push('e');

    REQUIRE(stack.size() == 5);

    std::string string;
    string.push_back(*stack.pop());
    string.push_back(*stack.pop());
    string.push_back(*stack.pop());
    string.push_back(*stack.pop());
    string.push_back(*stack.pop());

    REQUIRE(stack.size() == 0);

    REQUIRE(string == "edcba");

}

TEST_CASE("bj::stackstack works forwards loop", "[stackstack,forwarditerate,loop]") {

    bj::stackstack<char, 5> stack;
    REQUIRE(stack.capacity() == 5);
    REQUIRE(stack.size() == 0);

    stack.push('a');
    stack.push('b');
    stack.push('c');
    stack.push('d');
    stack.push('e');

    REQUIRE(stack.size() == 5);

    std::string string;

    for (auto &c : stack) {
        static_assert(!std::is_const_v<std::remove_reference_t<decltype(c)>>);
        string.push_back(c);
    }

    REQUIRE(stack.size() == 5);

    REQUIRE(string == "abcde");

}

TEST_CASE("bj::stackstack works forwards loop const", "[stackstack,forwarditerate,loop,const]") {

    bj::stackstack<char, 5> stack;
    REQUIRE(stack.capacity() == 5);
    REQUIRE(stack.size() == 0);

    stack.push('a');
    stack.push('b');
    stack.push('c');
    stack.push('d');
    stack.push('e');

    REQUIRE(stack.size() == 5);

    std::string string;

    const auto &cstack = stack;

    for (auto &c : cstack) {
        static_assert(std::is_const_v<std::remove_reference_t<decltype(c)>>);
        string.push_back(c);
    }

    REQUIRE(stack.size() == 5);

    REQUIRE(string == "abcde");

}

TEST_CASE("bj::stackstack works revese explicit loop", "[stackstack,backwardsiterate,loop]") {

    bj::stackstack<char, 5> stack;
    REQUIRE(stack.capacity() == 5);
    REQUIRE(stack.size() == 0);

    stack.push('a');
    stack.push('b');
    stack.push('c');
    stack.push('d');

    REQUIRE(stack.size() == 4);

    std::string string;

    for (auto it = stack.rbegin(); it < stack.rend(); ++it) {
        static_assert(!std::is_const_v<std::remove_reference_t<decltype(*it)>>);
        string.push_back(*it);
    }

    REQUIRE(stack.size() == 4);

    REQUIRE(string == "dcba");

}

TEST_CASE("bj::stackstack works const revese explicit loop", "[stackstack,backwardsiterate,loop,const]") {

    bj::stackstack<char, 5> stack;
    REQUIRE(stack.capacity() == 5);
    REQUIRE(stack.size() == 0);

    stack.push('a');
    stack.push('b');
    stack.push('c');
    stack.push('d');

    REQUIRE(stack.size() == 4);

    std::string string;

    const auto &cstack = stack;

    for (auto it = cstack.crbegin(); it < cstack.crend(); ++it) {
        static_assert(std::is_const_v<std::remove_reference_t<decltype(*it)>>);
        string.push_back(*it);
    }

    REQUIRE(stack.size() == 4);

    REQUIRE(string == "dcba");

}