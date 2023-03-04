//
// Created by ziware on 23/10/22.
//

#pragma once

#include <exception>

namespace ArchiverExceptions {  // NOLINT

class NoMulArg : public std::exception {
public:
    NoMulArg(const char* message);  // NOLINT
    const char* what() const noexcept override;

private:
    const char* message_;
};

class NoFile : public std::exception {
public:
    NoFile(const char* message);  // NOLINT
    const char* what() const noexcept override;

private:
    const char* message_;
};

class OutOfFile : public std::exception {
public:
    OutOfFile(const char* message);  // NOLINT
    const char* what() const noexcept override;

private:
    const char* message_;
};

}  // namespace ArchiverExceptions