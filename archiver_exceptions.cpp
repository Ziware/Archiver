//
// Created by ziware on 23/10/22.
//

#include "archiver_exceptions.h"
ArchiverExceptions::NoMulArg::NoMulArg(const char* message) : message_(message) {
}
const char* ArchiverExceptions::NoMulArg::what() const noexcept {
    return message_;
}
ArchiverExceptions::NoFile::NoFile(const char* message) : message_(message) {
}
const char* ArchiverExceptions::NoFile::what() const noexcept {
    return message_;
}
ArchiverExceptions::OutOfFile::OutOfFile(const char* message) : message_(message) {
}
const char* ArchiverExceptions::OutOfFile::what() const noexcept {
    return message_;
}
