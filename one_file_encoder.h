//
// Created by ziware on 22/10/22.
//

#pragma once

#include "constatns.h"
#include "reader.h"
#include "writer.h"
#include "huffman.h"

class OneFileEncoder {
public:
    explicit OneFileEncoder(std::string file);

    void Read();
    void Encode(Writer& writer, size_t& current_file_id, size_t files_count);

private:
    std::string file_;
    std::vector<std::pair<size_t, std::vector<bool>>> mp_;
    std::unordered_map<size_t, std::vector<bool>> get_code_;
    std::vector<size_t> code_count_;

    size_t ToSizeT(std::vector<bool> vec) const;
};