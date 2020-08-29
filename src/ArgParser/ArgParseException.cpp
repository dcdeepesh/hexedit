#include "ArgParser/ArgParseException.h"

#include <string>

ArgParseException::ArgParseException(std::string message) {
    this->msg = message;
}

const char* ArgParseException::what() const throw() {
    return msg.c_str();
}