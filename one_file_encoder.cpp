//
// Created by ziware on 22/10/22.
//

#include "one_file_encoder.h"

OneFileEncoder::OneFileEncoder(std::string file) : file_(file) {
}
void OneFileEncoder::Read() {
    std::unordered_map<size_t, size_t> count;
    count[FILENAME_END] = 1;
    count[ONE_MORE_FILE] = 1;
    count[ARCHIVE_END] = 1;
    for (auto c : file_) {
        ++count[c];
    }

    Reader reader(file_);
    while (!reader.IsEOF()) {
        ++count[ToSizeT(reader.GetVec(BYTE))];
    }

    Huffman huffman;

    mp_ = huffman.GetCanonicalCode(count);

    size_t max_symbol_code_size = mp_.back().second.size();
    code_count_.resize(max_symbol_code_size);

    for (const auto& [symbol, code] : mp_) {
        get_code_[symbol] = code;
        ++code_count_[code.size() - 1];
    }
}
void OneFileEncoder::Encode(Writer& writer, size_t& current_file_id, size_t files_count) {
    writer.WriteCustom(mp_.size(), CUSTOM_CHAR_SIZE);

    for (const auto& [symbol, code] : mp_) {
        writer.WriteCustom(symbol, CUSTOM_CHAR_SIZE);
    }

    for (const auto& tmp : code_count_) {
        writer.WriteCustom(tmp, CUSTOM_CHAR_SIZE);
    }

    for (auto c : file_) {
        writer.WriteVec(get_code_[c]);
    }

    writer.WriteVec(get_code_[FILENAME_END]);

    Reader reader(file_);
    while (!reader.IsEOF()) {
        writer.WriteVec(get_code_[ToSizeT(reader.GetVec(BYTE))]);
    }

    ++current_file_id;
    if (current_file_id < files_count) {
        writer.WriteVec(get_code_[ONE_MORE_FILE]);
    } else {
        writer.WriteVec(get_code_[ARCHIVE_END]);
    }
}
size_t OneFileEncoder::ToSizeT(std::vector<bool> vec) const {
    size_t res = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        res += (1 << i) * vec[i];
    }
    return res;
}
