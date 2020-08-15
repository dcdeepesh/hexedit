#ifndef DEC_HEX_BASE_H
#define DEC_HEX_BASE_H

#include <string>

namespace Base {
    std::string pad(const std::string &str, int lenAfterPad);
    char hexOf(int value);

    std::string toHex(int value, int lenAfterPad = 2);
    char toText(char byte);
}

#endif
