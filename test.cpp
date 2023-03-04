//
// Created by ziware on 20/10/22.
//

#include <catch.hpp>

#include "huffman.h"
#include "heap.h"

TEST_CASE("HeapSimple") {
    Heap<int> h;
    h.Push(5);
    REQUIRE(h.Empty() == false);
    h.Push(4);
    h.Push(4);
    h.Push(2);
    REQUIRE(h.Size() == 4);
    REQUIRE(h.Top() == 2);
    h.Pop();
    REQUIRE(h.Top() == 4);
    h.Pop();
    h.Pop();
    h.Push(1);
    REQUIRE(h.Top() == 1);
    REQUIRE(h.Size() == 2);
    h.Pop();
    REQUIRE(h.Top() == 5);
    h.Pop();
    REQUIRE(h.Empty());
}

TEST_CASE("HeapCustomCompare") {
    auto priority_comp = [](std::pair<int, int>& a, std::pair<int, int>& b) { return a.first > b.first; };
    Heap<std::pair<int, int>, decltype(priority_comp)> h(priority_comp);
    h.Push({3, 1});
    h.Push({2, 9});
    REQUIRE(h.Top() == std::make_pair(3, 1));
    h.Push({5, 0});
    REQUIRE(h.Top() == std::make_pair(5, 0));
    h.Pop();
    h.Pop();
    REQUIRE(h.Top() == std::make_pair(2, 9));
    h.Pop();
    REQUIRE(h.Empty());
}

TEST_CASE("Huffman") {
    std::unordered_map<size_t, size_t> count;
    count['a'] = 5;
    count['b'] = 2;
    count['d'] = 4;
    count['e'] = 2;
    count['f'] = 1;
    count['g'] = 1;
    count['h'] = 1;
    Huffman huf;
    const auto& cur = huf.GetCanonicalCode(count);

    {
        const std::vector<std::pair<size_t, std::vector<bool>>> result = {
            {97, {false, false}},              // a -   00
            {100, {true, false}},              // d -   10
            {98, {false, false, true}},        // b -  001
            {101, {true, false, true}},        // e -  101
            {104, {false, true, true}},        // h -  011
            {102, {false, true, true, true}},  // f - 0111
            {103, {true, true, true, true}},   // g - 1111
        };                                     //    <----  read from right to left

        REQUIRE(cur == result);
    }

    std::vector<size_t> symbols;
    std::vector<size_t> cnt(cur.back().second.size());
    for (auto& t : cur) {
        symbols.push_back(t.first);
        ++cnt[t.second.size() - 1];
    }

    const auto& tmp = huf.GetDecodeHashmap(symbols, cnt);

    {
        const std::unordered_map<std::vector<bool>, size_t> result = {
            {{false, false}, 97},              //   00 - a
            {{false, true}, 100},              //   01 - d
            {{true, false, false}, 98},        //  100 - b
            {{true, false, true}, 101},        //  101 - e
            {{true, true, false}, 104},        //  110 - h
            {{true, true, true, false}, 102},  // 1110 - f
            {{true, true, true, true}, 103},   // 1111 - g
        };                                     // <----  read from right to left
        REQUIRE(tmp == result);
    }
}
