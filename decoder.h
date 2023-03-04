//
// Created by ziware on 20/10/22.
//

#pragma once

#include "constatns.h"
#include "one_file_decoder.h"

class Decoder {
public:
    explicit Decoder(std::string archive_name);
    void Decode();

private:
    std::string archive_name_;
};
