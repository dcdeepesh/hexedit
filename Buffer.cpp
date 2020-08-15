#include "Buffer.h"

#include <fstream>
#include <string>

using std::size_t;
using std::ios;
using std::string;

namespace Buffer {
    std::ifstream ifs;
    size_t fileSize;
    char *buffer;
    string filePath;
    bool modified = false;

    void load(string filePath) {
        Buffer::filePath = filePath;
        ifs.open(filePath, ios::in | ios::binary);

        ifs.seekg(0, ios::end);
        fileSize = ifs.tellg();
        buffer = new char[fileSize];

        ifs.seekg(0, ios::beg);
        ifs.read(buffer, fileSize);
        ifs.close();
    }

    void save(SaveOption option) {
        std::string outFilePath;
        if (option == SaveOption::SAME_FILE)
            outFilePath = filePath;
        else
            outFilePath = "mod_" + filePath + "";

        std::ofstream ofs(outFilePath, ios::out | ios::binary);
        ofs.write(buffer, fileSize);
        ofs.close();
        modified = false;
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