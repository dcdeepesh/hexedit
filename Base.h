#ifndef DEC_HEX_BASE_H
#define DEC_HEX_BASE_H

#include <string>

namespace Base {
    std::string pad(const std::string &str, unsigned int lenAfterPad);
    char hexOf(int value);
    char charOf(char hexChar);

    std::string toHex(int value, unsigned int lenAfterPad = 2);
    char toText(char byte);
    char toText(char *hex);
}

#endif
