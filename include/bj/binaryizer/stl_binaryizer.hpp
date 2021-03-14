// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#pragma once

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <set>
#include <utility> // std::pair.
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

#include "binaryizer.hpp"

namespace bj {

    // std::array.

    template<typename T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T, N> &data) {
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<noraw_out T, std::size_t N>
    inline void binaryize(obinaryizer &out, const std::array<T, N> &data) {
        out.put(data.begin(), data.end());
    }

    template<typename T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T, N> &data) {
        in.getraw(reinterpret_cast<std::byte *>(data.data()), N * sizeof(T));
    }

    template<noraw_in T, std::size_t N>
    inline void debinaryize(ibinaryizer &in, std::array<T, N> &data) {
        in.get(data.begin(), data.end());
    }

    // std::vector.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::vector<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.putraw(reinterpret_cast<const std::byte *>(data.data()), data.size() * sizeof(T));
    }

    template<noraw_out T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::vector<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::vector<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.getraw(reinterpret_cast<std::byte *>(data.data()), size * sizeof(T));
    }

    template<noraw_in T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::vector<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    template<debinaryizable_emplace T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::vector<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.reserve(size);
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace_back(in);
        }
    }

    // std::deque.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::deque<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::deque<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    template<debinaryizable_emplace T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::deque<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace_back(in);
        }
    }

    // std::forward_list.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::forward_list<T, Alloc> &data) {
        std::uint32_t size{};
        for ([[maybe_unused]] const auto &d : data) ++size;
        out.put<std::uint32_t>(size);
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::forward_list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    template<debinaryizable_emplace T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::forward_list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        auto iter = data.before_begin();
        for (std::uint32_t i{}; i < size; ++i) {
            iter = data.emplace_after(iter, in);
        }
    }

    // std::list.

    template<typename T, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::list<T, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    template<debinaryizable_emplace T, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::list<T, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace_back(in);
        }
    }

    // std::basic_string.

    template<typename T, typename Traits, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::basic_string<T, Traits, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Traits, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::basic_string<T, Traits, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        data.resize(size);
        in.get(data.begin(), data.end());
    }

    // std::set.

    template<typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::set<T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::set<T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            // Not a huge fan of this.
            T t;
            in(t);
            data.insert(t);
        }
    }

    template<debinaryizable_emplace T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::set<T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace(in);
        }
    }

    // std::pair.

    template<typename T1, typename T2>
    inline void binaryize(obinaryizer &out, const std::pair<T1, T2> &data) {
        out(data.first, data.second);
    }

    template<typename T1, typename T2>
    inline void debinaryize(ibinaryizer &in, std::pair<T1, T2> &data) {
        in(data.first, data.second);
    }

    // std::map.

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::map<Key, T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::map<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            std::pair<Key, T> p;
            in(p);
            data.insert(p);
        }
    }

    template<typename Key, debinaryizable_emplace T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::map<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            Key k;
            in(k);
            data.emplace(k, in);
        }
    }

    // std::multiset.

    template<typename Key, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::multiset<Key, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::multiset<Key, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            // Not a huge fan of this.
            Key t;
            in(t);
            data.insert(t);
        }
    }

    template<debinaryizable_emplace Key, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::multiset<Key, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace(in);
        }
    }

    // std::multimap.

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::multimap<Key, T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::multimap<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            std::pair<Key, T> p;
            in(p);
            data.insert(p);
        }
    }

    template<typename Key, debinaryizable_emplace T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::multimap<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            Key k;
            in(k);
            data.emplace(k, in);
        }
    }

    // Unordered...

    // std::unordered_set.

    template<typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::unordered_set<T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_set<T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            // Not a huge fan of this.
            T t;
            in(t);
            data.insert(t);
        }
    }

    template<debinaryizable_emplace T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_set<T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace(in);
        }
    }

    // std::unordered_map.

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::unordered_map<Key, T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_map<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            std::pair<Key, T> p;
            in(p);
            data.insert(p);
        }
    }

    template<typename Key, debinaryizable_emplace T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_map<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            Key k;
            in(k);
            data.emplace(k, in);
        }
    }

    // std::unordered_multiset.

    template<typename Key, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::unordered_multiset<Key, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_multiset<Key, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            // Not a huge fan of this.
            Key t;
            in(t);
            data.insert(t);
        }
    }

    template<debinaryizable_emplace Key, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_multiset<Key, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            data.emplace(in);
        }
    }

    // std::unordered_multimap.

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void binaryize(obinaryizer &out, const std::unordered_multimap<Key, T, Compare, Alloc> &data) {
        out.put<std::uint32_t>(static_cast<std::uint32_t>(data.size()));
        out.put(data.begin(), data.end());
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_multimap<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            std::pair<Key, T> p;
            in(p);
            data.insert(p);
        }
    }

    template<typename Key, debinaryizable_emplace T, typename Compare, typename Alloc>
    inline void debinaryize(ibinaryizer &in, std::unordered_multimap<Key, T, Compare, Alloc> &data) {
        const std::uint32_t size = in.get<std::uint32_t>();
        for (std::uint32_t i{}; i < size; ++i) {
            Key k;
            in(k);
            data.emplace(k, in);
        }
    }

    // Protected access.
    // Underlying container in wrappers is always called "c".
    // Expecation: as protected (so accessible to third party classes) in the standard
    // this is unlikely to change. A class inheriting from a class, neither of which
    // use polymorphism, and adds no data members, will have the same layout as the parent
    // class. 

    template<class Parent>
    struct inner_container : Parent {
        using Parent::c;
    };

    // std::stack.

    template<typename T, typename Container>
    inline void binaryize(obinaryizer &out, const std::stack<T, Container> &data) {
        const Container &c = data.*(&inner_container<std::stack<T, Container>>::c);
        out(c);
    }

    template<typename T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::stack<T, Container> &data) {
        Container &c = data.*(&inner_container<std::stack<T, Container>>::c);
        in(c);
    }

    template<debinaryizable_emplace T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::stack<T, Container> &data) {
        Container &c = data.*(&inner_container<std::stack<T, Container>>::c);
        in(c);
    }

    // std::queue.

    template<typename T, typename Container>
    inline void binaryize(obinaryizer &out, const std::queue<T, Container> &data) {
        const Container &c = data.*(&inner_container<std::queue<T, Container>>::c);
        out(c);
    }

    template<typename T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::queue<T, Container> &data) {
        Container &c = data.*(&inner_container<std::queue<T, Container>>::c);
        in(c);
    }

    template<debinaryizable_emplace T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::queue<T, Container> &data) {
        Container &c = data.*(&inner_container<std::queue<T, Container>>::c);
        in(c);
    }

    // std::priority_queue.

    template<typename T, typename Container>
    inline void binaryize(obinaryizer &out, const std::priority_queue<T, Container> &data) {
        const Container &c = data.*(&inner_container<std::priority_queue<T, Container>>::c);
        out(c);
    }

    template<typename T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::priority_queue<T, Container> &data) {
        Container &c = data.*(&inner_container<std::priority_queue<T, Container>>::c);
        in(c);
    }

    template<debinaryizable_emplace T, typename Container>
    inline void debinaryize(ibinaryizer &in, std::priority_queue<T, Container> &data) {
        Container &c = data.*(&inner_container<std::priority_queue<T, Container>>::c);
        in(c);
    }

} // namespace bj.