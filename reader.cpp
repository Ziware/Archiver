//
// Created by ziware on 20/10/22.
//

#include "reader.h"

Reader::Reader(const std::string& file_name) : in_(file_name, std::ios::binary), cnt_(0), buff_(0) {
    if (!in_.is_open()) {
        throw ArchiverExceptions::NoFile(file_name.data());
    }
}
Reader::~Reader() {
    in_.close();
}

bool Reader::IsEOF() {
    return in_.peek() == EOF;
}
std::vector<bool> Reader::GetVec(size_t sz) {
    std::vector<bool> res;
    res.reserve(sz);
    while (res.size() != sz) {
        res.push_back(GetBit());
    }
    std::reverse(res.begin(), res.end());
    return res;
}
bool Reader::GetBit() {
    if (cnt_ == 0) {
        if (IsEOF()) {
            throw ArchiverExceptions::OutOfFile("unknown file name");
        }
        buff_ = in_.get();
        cnt_ = 8;
    }
    bool res = (buff_ & (1 << (cnt_ - 1))) != 0;
    buff_ &= (1 << (cnt_ - 1)) - 1;
    --cnt_;
    return res;
}
