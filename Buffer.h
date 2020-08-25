#ifndef DEC_HEX_BUFFER_H
#define DEC_HEX_BUFFER_H

#include <cstddef>
#include <string>

enum class SaveOption {
    SAME_FILE, NEW_FILE
};

namespace Buffer {
    void load(std::string filePath);
    void save(SaveOption option);
    
    const char* contents();
    std::size_t size();
    char at(std::size_t pos);
    void set(std::size_t pos, char newByte);
    bool isModified();

    void finish();
}

#endif
