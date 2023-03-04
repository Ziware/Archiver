//
// Created by ziware on 20/10/22.
//

#include "writer.h"

Writer::Writer(const std::string& file_name) : out_(file_name, std::ios::binary), cnt_(0), buff_(0) {
    if (!out_.is_open()) {
        throw ArchiverExceptions::NoFile(file_name.data());
    }
}
Writer::~Writer() {
    while (cnt_ != 0) {
        WriteBit(false);
    }
    out_.close();
}

void Writer::WriteVec(std::vector<bool> v) {
    while (!v.empty()) {
        WriteBit(v.back());
        v.pop_back();
    }
}
void Writer::WriteCustom(size_t c, size_t bit_cnt) {
    for (size_t i = 0; i < bit_cnt; ++i) {
        WriteBit(((1 << (bit_cnt - i - 1)) & c) != 0);
    }
}
void Writer::WriteBit(bool b) {
    buff_ <<= 1;
    buff_ += b;
    ++cnt_;
    if (cnt_ == BYTE) {
        out_.put(static_cast<char>(buff_));
        buff_ = 0;
        cnt_ = 0;
    }
}
