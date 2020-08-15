#ifndef DEC_HEX_BUFFER_H
#define DEC_HEX_BUFFER_H

#include <cstddef>
#include <string>

namespace Buffer {
    void load(std::string filePath);

    const char* contents();
    std::size_t size();
    char at(int pos);

    void finish();
}

#endif
