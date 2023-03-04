//
// Created by ziware on 22/10/22.
//

#pragma once

#include <vector>
#include <functional>

template <typename T, typename Comp = std::less<T>>
class Heap {
public:
    Heap();
    explicit Heap(Comp& cmp);

    void Push(const T val);
    void Pop();
    const T& Top() const;
    size_t Size() const;
    bool Empty() const;

private:
    size_t MinChild(size_t val);

    std::vector<T> data_;
    Comp cmp_;
};

template <typename T, typename Comp>
Heap<T, Comp>::Heap() : cmp_(std::less<T>()) {
    data_.push_back(T());
}
template <typename T, typename Comp>
Heap<T, Comp>::Heap(Comp& cmp) : cmp_(cmp) {
    data_.push_back(T());
}

template <typename T, typename Comp>
void Heap<T, Comp>::Push(const T val) {
    data_.push_back(val);
    size_t id = data_.size() - 1;
    while (id != 1) {
        if (cmp_(data_[id], data_[id / 2])) {
            std::swap(data_[id], data_[id / 2]);
        }
        id /= 2;
    }
}
template <typename T, typename Comp>
void Heap<T, Comp>::Pop() {
    std::swap(data_[1], data_[data_.size() - 1]);
    data_.pop_back();
    size_t id = 1;
    while (id * 2 < data_.size()) {
        size_t mn = MinChild(id);
        if (mn == id) {
            break;
        }
        std::swap(data_[id], data_[mn]);
        id = mn;
    }
}
template <typename T, typename Comp>
size_t Heap<T, Comp>::MinChild(size_t val) {
    size_t mn = val * 2;
    if (val * 2 + 1 < data_.size()) {
        mn = val * 2 + 1;
        if (cmp_(data_[val * 2], data_[val * 2 + 1])) {
            mn = val * 2;
        }
    }
    if (cmp_(data_[mn], data_[val])) {
        return mn;
    } else {
        return val;
    }
}
template <typename T, typename Comp>
const T& Heap<T, Comp>::Top() const {
    return data_[1];
}
template <typename T, typename Comp>
size_t Heap<T, Comp>::Size() const {
    return data_.size() - 1;
}
template <typename T, typename Comp>
bool Heap<T, Comp>::Empty() const {
    return data_.size() == 1;
}
