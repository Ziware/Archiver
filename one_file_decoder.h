//
// Created by ziware on 22/10/22.
//

#pragma once

#include "constatns.h"
#include "writer.h"
#include "reader.h"
#include "huffman.h"

class OneFileDecoder {
public:
    explicit OneFileDecoder(Reader& reader);
    void GetInfo();
    void GetFilename();
    void GetFile();
    bool IsArchiveEnd() const;

private:
    bool archive_end_;
    Reader& reader_;
    std::unordered_map<std::vector<bool>, size_t> decode_;
    std::string file_;

    size_t ToSizeT(std::vector<bool> vec) const;
};