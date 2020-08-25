#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>

using std::string;

namespace Base {
    const char digits[] =
        {'0', '1', '2', '3', '4', '5', '6', '7',
         '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    string pad(const string &str, unsigned int lenAfterPad) { 
        if (str.length() >= lenAfterPad)
            return str;
        else
            return string(lenAfterPad - str.length(), '0') + str;
    }

    char hexOf(int value) {
        if (value < 0 || value > 15)
            throw std::range_error("hex char not [0-15]");

        return digits[value];
    }

    char charOf(char hexChar) {
        for (int i = 0; i < 16; i++)
            if (digits[i] == hexChar)
                return i;

        throw std::range_error("Base::charOf()");
    }

    string toHex(int value, unsigned int lenAfterPad = 2) {
        if (value == 0)
            return pad("0", lenAfterPad);
        if (value < 0)
            value = static_cast<unsigned char>((char) value);

        std::stringstream ss;
        while (value > 0) {
            ss << hexOf(value % 16);
            value /= 16;
        }

        string str = ss.str();
        std::reverse(str.begin(), str.end());
        return pad(str, lenAfterPad);
    }

    char toText(char byte) {
        return (byte > 32) ? byte : '.';
    }

    char toText(char *hex) {
        return 16 * charOf(hex[0]) + charOf(hex[1]);
    }
}
