//
// Created by ziware on 20/10/22.
//

#pragma once

#include "constatns.h"
#include "archiver_exceptions.h"

class Writer {
public:
    explicit Writer(const std::string& file_name);
    ~Writer();

    void WriteVec(std::vector<bool> v);
    void WriteCustom(size_t c, size_t bit_cnt);
    void WriteBit(bool b);

private:
    std::ofstream out_;
    size_t cnt_;
    size_t buff_;
};