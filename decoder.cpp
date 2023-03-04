//
// Created by ziware on 20/10/22.
//

#include "decoder.h"
Decoder::Decoder(std::string archive_name) : archive_name_(archive_name) {
}
void Decoder::Decode() {
    Reader reader(archive_name_);
    bool archive_end = false;
    while (!archive_end) {
        OneFileDecoder ofd(reader);
        ofd.GetInfo();
        ofd.GetFilename();
        ofd.GetFile();
        archive_end = ofd.IsArchiveEnd();
    }
}
