//
// Created by ziware on 23/10/22.
//

#include "cla_parser.h"

CLAParser::CLAParser(int argc, char **argv) : need_help_(false), argc_(argc), argv_(argv) {
    AddFlag("h", "help", "get help message", &need_help_);
}
void CLAParser::AddArgument(std::string short_name, std::string long_name, std::string argument,
                            std::string help_message, bool allow_multiple_arguments, std::string *parse_to) {
    args_holder_.push_back(
        CLAObject(short_name, long_name, argument, help_message, allow_multiple_arguments, parse_to));
}
void CLAParser::AddMultipleArgument(std::string argument, std::string help_message,
                                    std::vector<std::string> *parse_to) {
    args_holder_.push_back(CLAObject(argument, help_message, parse_to));
}
void CLAParser::AddFlag(std::string short_name, std::string long_name, std::string help_message, bool *parse_to) {
    args_holder_.push_back(CLAObject(short_name, long_name, help_message, parse_to));
}
void CLAParser::PrintErrorMessage(std::string error_log = "something went wrong") {
    std::cout << "\n";
    std::cout << "Check your argument line correctness\n"
              << "ERROR: " << error_log << '\n'
              << "     use flag \'-h\' to get help\n";
}
void CLAParser::PrintHelpMessage() {
    std::cout << "\n";
    std::cout << "Arguments available:\n";
    for (const auto &arg : args_holder_) {
        std::cout << "    ";
        if (arg.type_ == CLAType::FLAG_ARGUMENT) {
            std::cout << arg.short_name_ << " or " << arg.long_name_ << "          ---  to " << arg.help_message_;
        }
        if (arg.type_ == CLAType::SINGLE_ARGUMENT) {
            const CLAObject *mul_arg = nullptr;
            for (const auto &cur_arg : args_holder_) {
                if (cur_arg.type_ == CLAType::MULTIPLE_ARGUMENT) {
                    mul_arg = &cur_arg;
                    break;
                }
            }
            std::cout << arg.short_name_ << " or " << arg.long_name_ << "  " << arg.argument_ << "  ";
            if (arg.add_multiple_arguments_) {
                if (mul_arg == nullptr) {
                    throw ArchiverExceptions::NoMulArg("no multiple argument in CLAParser");
                }
                std::cout << mul_arg->argument_ << "          --- to " << arg.help_message_ << " "
                          << mul_arg->help_message_;
            } else {
                std::cout << "        --- to " << arg.help_message_;
            }
        }
        std::cout << '\n';
    }
}
bool CLAParser::Parse() {
    if (argc_ < ARG_NAME_POS) {
        PrintErrorMessage("write some arguments");
        return true;
    }

    std::string arg_name = *(argv_ + ARG_NAME_POS - 1);
    CLAObject *cur = nullptr;
    for (auto &arg : args_holder_) {
        if (arg.short_name_ == arg_name || arg.long_name_ == arg_name) {
            cur = &arg;
            break;
        }
    }
    if (cur == nullptr) {
        PrintErrorMessage("there are no argument named \'" + arg_name + "\'");
        return true;
    }
    if (cur->type_ == CLAType::FLAG_ARGUMENT) {
        if (argc_ > ARG_NAME_POS) {
            PrintErrorMessage("there are too many params in line");
            return true;
        } else {
            *cur->to_flag_ = true;
        }
    }

    if (cur->type_ == CLAType::SINGLE_ARGUMENT) {
        if (!cur->add_multiple_arguments_) {
            if (argc_ < ARG_ARGUMENT_POS) {
                PrintErrorMessage("write parameter name");
                return true;
            } else if (argc_ > ARG_ARGUMENT_POS) {
                PrintErrorMessage("there are too many params in line");
                return true;
            }
            *cur->to_single_ = *(argv_ + ARG_ARGUMENT_POS - 1);
        } else {
            CLAObject *mul_arg = nullptr;
            for (auto &cur_arg : args_holder_) {
                if (cur_arg.type_ == CLAType::MULTIPLE_ARGUMENT) {
                    mul_arg = &cur_arg;
                    break;
                }
            }
            if (mul_arg == nullptr) {
                throw ArchiverExceptions::NoMulArg("no multiple argument in CLAParser");
            }
            if (argc_ < MUL_ARG_POS) {
                PrintErrorMessage("write parameter name");
                return true;
            }
            *cur->to_single_ = *(argv_ + ARG_ARGUMENT_POS - 1);
            for (size_t i = MUL_ARG_POS - 1; i < argc_; ++i) {
                mul_arg->to_multiple_->push_back(*(argv_ + i));
            }
        }
    }

    if (need_help_) {
        PrintHelpMessage();
        return true;
    }
    return false;
}

CLAParser::CLAObject::CLAObject(std::string short_name, std::string long_name, std::string argument,
                                std::string help_message, bool add_multiple_arguments, std::string *parse_to)
    : short_name_("-" + short_name),
      long_name_("--" + long_name),
      argument_(argument),
      help_message_(help_message),
      add_multiple_arguments_(add_multiple_arguments),
      type_(CLAType::SINGLE_ARGUMENT),
      to_flag_(nullptr),
      to_single_(parse_to),
      to_multiple_(nullptr) {
}
CLAParser::CLAObject::CLAObject(std::string argument, std::string help_message, std::vector<std::string> *parse_to)
    : short_name_("undefined"),
      long_name_("undefined"),
      argument_(argument),
      help_message_(help_message),
      add_multiple_arguments_(false),
      type_(CLAType::MULTIPLE_ARGUMENT),
      to_flag_(nullptr),
      to_single_(nullptr),
      to_multiple_(parse_to) {
}
CLAParser::CLAObject::CLAObject(std::string short_name, std::string long_name, std::string help_message, bool *parse_to)
    : short_name_("-" + short_name),
      long_name_("--" + long_name),
      argument_("undefined"),
      help_message_(help_message),
      add_multiple_arguments_(false),
      type_(CLAType::FLAG_ARGUMENT),
      to_flag_(parse_to),
      to_single_(nullptr),
      to_multiple_(nullptr) {
}
