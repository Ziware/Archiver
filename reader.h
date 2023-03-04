//
// Created by ziware on 20/10/22.
//

#pragma once

#include "constatns.h"
#include "archiver_exceptions.h"

class Reader {
public:
    explicit Reader(const std::string& file_name);
    ~Reader();

    std::vector<bool> GetVec(size_t sz);
    bool GetBit();
    bool IsEOF();

private:
    std::ifstream in_;
    size_t cnt_;
    size_t buff_;
};