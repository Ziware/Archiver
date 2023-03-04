//
// Created by ziware on 20/10/22.
//

#include "encoder.h"
Encoder::Encoder(std::string archive_name, const std::vector<std::string>& file_names)
    : archive_name_(archive_name), file_names_(file_names) {
}

void Encoder::Encode() {
    Writer writer(archive_name_);
    size_t current_file_id = 0;
    for (const auto& file : file_names_) {
        OneFileEncoder ofe(file);
        ofe.Read();
        ofe.Encode(writer, current_file_id, file_names_.size());
    }
}
