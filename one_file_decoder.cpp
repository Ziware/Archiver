//
// Created by ziware on 22/10/22.
//

#include "one_file_decoder.h"

OneFileDecoder::OneFileDecoder(Reader& reader) : archive_end_(false), reader_(reader) {
}
void OneFileDecoder::GetInfo() {
    size_t symbols_count = ToSizeT(reader_.GetVec(CUSTOM_CHAR_SIZE));
    std::vector<size_t> symbols(symbols_count);
    for (size_t i = 0; i < symbols_count; ++i) {
        symbols[i] = ToSizeT(reader_.GetVec(CUSTOM_CHAR_SIZE));
    }
    std::vector<size_t> cnt;
    size_t cur_sum = 0;
    while (cur_sum < symbols_count) {
        cnt.push_back(ToSizeT(reader_.GetVec(CUSTOM_CHAR_SIZE)));
        cur_sum += cnt.back();
    }
    Huffman huf;
    decode_ = huf.GetDecodeHashmap(symbols, cnt);
}
void OneFileDecoder::GetFilename() {
    bool filename_end = false;
    std::vector<bool> buff;
    while (!filename_end) {
        buff.push_back(reader_.GetBit());
        auto it = decode_.find(buff);
        if (it != decode_.end()) {
            if (it->second == FILENAME_END) {
                filename_end = true;
                continue;
            }
            file_.push_back(static_cast<char>(it->second));
            buff.clear();
        }
    }
}
void OneFileDecoder::GetFile() {
    Writer writer(file_);
    bool file_end = false;
    std::vector<bool> buff;
    while (!file_end) {
        buff.push_back(reader_.GetBit());
        auto it = decode_.find(buff);
        if (it != decode_.end()) {
            if (it->second == ARCHIVE_END) {
                file_end = true;
                archive_end_ = true;
                continue;
            }
            if (it->second == ONE_MORE_FILE) {
                file_end = true;
                continue;
            }
            writer.WriteCustom(it->second, BYTE);
            buff.clear();
        }
    }
}
bool OneFileDecoder::IsArchiveEnd() const {
    return archive_end_;
}
size_t OneFileDecoder::ToSizeT(std::vector<bool> vec) const {
    size_t res = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        res += (1 << i) * vec[i];
    }
    return res;
}
