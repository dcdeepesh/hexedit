#ifndef ARG_PARSE_EXCEPT_H
#define ARG_PARSE_EXCEPT_H

#include <exception>
#include <string>

/**
 * Exceptions thrown by the argument parser(ArgParser) are of the
 * type ArgParseException instead of std::exception.
 */
class ArgParseException : std::exception {
public:
    /**
     * Initializes a new ArgParseException with the message given as
     * parameter.
     *
     * @param msg The message
     */
    ArgParseException(std::string message);
    const char* what() const throw();

private:
    std::string msg;
};

#endif