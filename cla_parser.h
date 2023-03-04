//
// Created by ziware on 23/10/22.
//

#pragma once

#include "constatns.h"
#include "archiver_exceptions.h"
#include <iostream>
#include <string>
#include <vector>

class CLAParser {
public:
    CLAParser(int argc, char** argv);

    void AddArgument(std::string short_name, std::string long_name, std::string argument, std::string help_message,
                     bool allow_multiple_arguments, std::string* parse_to);
    void AddMultipleArgument(
        std::string argument, std::string help_message,
        std::vector<std::string>* parse_to);  /// only your first multiple argument will be available
    void AddFlag(std::string short_name, std::string long_name, std::string help_message, bool* parse_to);
    bool Parse();  /// returns 'true' if error or help message found

private:
    enum class CLAType {
        SINGLE_ARGUMENT,
        MULTIPLE_ARGUMENT,
        FLAG_ARGUMENT,
    };

    struct CLAObject {
        std::string short_name_;
        std::string long_name_;
        std::string argument_;
        std::string help_message_;
        bool add_multiple_arguments_;
        CLAType type_;

        bool* to_flag_;
        std::string* to_single_;
        std::vector<std::string>* to_multiple_;

        CLAObject(std::string short_name, std::string long_name, std::string argument, std::string help_message,
                  bool allow_multiple_arguments, std::string* parse_to);
        CLAObject(std::string argument, std::string help_message, std::vector<std::string>* parse_to);
        CLAObject(std::string short_name, std::string long_name, std::string help_message, bool* parse_to);
    };

    void PrintErrorMessage(std::string error_log);
    void PrintHelpMessage();

    bool need_help_;
    int argc_;
    char** argv_;
    std::vector<CLAObject> args_holder_;
};