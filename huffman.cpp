//
// Created by ziware on 20/10/22.
//

#include "huffman.h"

std::vector<std::pair<size_t, size_t>> Huffman::GetHuffmanCode(const std::unordered_map<size_t, size_t>& count) {
    auto priority_comp = [](std::pair<size_t, Node*>& a, std::pair<size_t, Node*>& b) {
        return a.first < b.first || (a.first == b.first && a.second->name < b.second->name);
    };
    Heap<std::pair<size_t, Node*>, decltype(priority_comp)> q(priority_comp);
    for (const auto& el : count) {
        q.Push({el.second, new Node(el.first)});
    }
    while (q.Size() >= 2) {
        auto node1 = q.Top();
        q.Pop();
        auto node2 = q.Top();
        q.Pop();
        q.Push({node1.first + node2.first,
                new Node(std::min(node1.second->name, node2.second->name), node1.second, node2.second)});
    }
    auto root = q.Top().second;
    std::vector<std::pair<size_t, size_t>> res;
    GetCode(root, 0, res);
    delete root;
    if (res.size() == 1) {
        res[0].second = 1;  // only for 1 symbol alphabet
    }
    return res;
}

std::vector<std::pair<size_t, std::vector<bool>>> Huffman::GetCanonicalCode(
    const std::unordered_map<size_t, size_t>& count) {
    auto codes = GetHuffmanCode(count);
    std::sort(codes.begin(), codes.end(), Comp);
    std::vector<bool> code(1, false);
    std::vector<std::pair<size_t, std::vector<bool>>> res;
    size_t last = 1;
    for (int i = 0; i < codes.size(); ++i) {
        BitShiftRight(code, codes[i].second - last);
        res.emplace_back(codes[i].first, code);
        AddOneFront(code);
        last = codes[i].second;
    }
    return res;
}
void Huffman::GetCode(Huffman::Node* tmp, size_t depth, std::vector<std::pair<size_t, size_t>>& res) {
    if (tmp->left == nullptr || tmp->right == nullptr) {
        res.emplace_back(tmp->name, depth);
    }
    if (tmp->left != nullptr) {
        ++depth;
        GetCode(tmp->left, depth, res);
        --depth;
    }
    if (tmp->right != nullptr) {
        ++depth;
        GetCode(tmp->right, depth, res);
        --depth;
    }
}
void Huffman::AddOneFront(std::vector<bool>& vec) {
    size_t id = 0;
    while (id < vec.size() && vec[id]) {
        vec[id] = false;
        ++id;
    }
    if (id == vec.size()) {
        vec.push_back(false);
    }
    vec[id] = true;
}
void Huffman::BitShiftRight(std::vector<bool>& vec, size_t shift) {
    while (shift > 0) {
        vec.insert(vec.begin(), false);
        --shift;
    }
}
void Huffman::AddOneEnd(std::vector<bool>& vec) {
    size_t id = vec.size();
    while (id > 0 && vec[id - 1]) {
        --id;
        vec[id] = false;
    }
    if (id == 0) {
        vec.push_back(false);
        vec[id] = true;
    } else {
        --id;
        vec[id] = true;
    }
}
void Huffman::BitShiftLeft(std::vector<bool>& vec, size_t shift) {
    while (shift > 0) {
        vec.push_back(false);
        --shift;
    }
}
bool Huffman::Comp(std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b) {
    return a.second < b.second || (a.second == b.second && a.first < b.first);
}
std::unordered_map<std::vector<bool>, size_t> Huffman::GetDecodeHashmap(const std::vector<size_t>& symbols,
                                                                        const std::vector<size_t>& cnt) {
    std::unordered_map<std::vector<bool>, size_t> res;
    std::vector<bool> cur;
    size_t id = 0;
    for (size_t sz = 1; sz - 1 < cnt.size(); ++sz) {
        if (cur.size() < sz) {
            BitShiftLeft(cur, sz - cur.size());
        }
        for (size_t i = 0; i < cnt[sz - 1]; ++i, ++id) {
            res[cur] = symbols[id];
            AddOneEnd(cur);
        }
    }
    return res;
}

Huffman::Node::Node() : name(0), left(nullptr), right(nullptr) {
}
Huffman::Node::Node(size_t name) : name(name), left(nullptr), right(nullptr) {
}
Huffman::Node::Node(size_t name, Huffman::Node* left, Huffman::Node* right) : name(name), left(left), right(right) {
}
Huffman::Node::~Node() {
    delete left;
    delete right;
}
bool Huffman::Node::operator<(Huffman::Node* other) const {
    return this->name < other->name;
}