#include "Buffer.h"

#include <fstream>
#include <string>

using std::size_t;
using std::ios;

namespace Buffer {
    std::ifstream ifs;
    size_t fileSize;
    char *buffer;
    bool modified = false;

    void load(std::string filePath) {
        ifs.open(filePath, ios::in | ios::binary);

        ifs.seekg(0, ios::end);
        fileSize = ifs.tellg();
        buffer = new char[fileSize];

        ifs.seekg(0, ios::beg);
        ifs.read(buffer, fileSize);
        ifs.close();
    }

    const char* contents() { return buffer; }
    size_t size() { return fileSize; }

    char at(int pos) {
        if (pos < 0 || pos > fileSize)
            throw std::range_error("Buffer::at()");
        else
            return buffer[pos];
    }

    void set(int pos, char newByte) {
        if (pos < 0 || pos > fileSize)
            throw std::range_error("Buffer::set()");
        else {
            buffer[pos] = newByte;
            modified = true;
        }
    }

    bool isModified() { return modified; }

    void finish() {
        delete[] buffer;
        buffer = nullptr;
    }
}