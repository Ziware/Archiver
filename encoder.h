//
// Created by ziware on 20/10/22.
//

#pragma once

#include "constatns.h"
#include "one_file_encoder.h"

class Encoder {
public:
    Encoder(std::string archive_name, const std::vector<std::string>& file_names);
    void Encode();

private:
    std::string archive_name_;
    const std::vector<std::string> file_names_;
};
