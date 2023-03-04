//
// Created by ziware on 20/10/22.
//

#pragma once

#include "constatns.h"
#include "heap.h"

class Huffman {
public:
    std::vector<std::pair<size_t, std::vector<bool>>> GetCanonicalCode(const std::unordered_map<size_t, size_t>& count);
    std::unordered_map<std::vector<bool>, size_t> GetDecodeHashmap(const std::vector<size_t>& symbols,
                                                                   const std::vector<size_t>& cnt);
    std::vector<std::pair<size_t, size_t>> GetHuffmanCode(const std::unordered_map<size_t, size_t>& count);

private:
    struct Node {
        size_t name;
        Node* left;
        Node* right;

        Node();
        explicit Node(size_t name);
        Node(size_t name, Node* left, Node* right);
        ~Node();
        bool operator<(Node* other) const;
    };

    void GetCode(Node* tmp, size_t depth, std::vector<std::pair<size_t, size_t>>& res);

    static bool Comp(std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b);

    void AddOneFront(std::vector<bool>& vec);
    void BitShiftRight(std::vector<bool>& vec, size_t shift);
    void AddOneEnd(std::vector<bool>& vec);
    void BitShiftLeft(std::vector<bool>& vec, size_t shift);
};