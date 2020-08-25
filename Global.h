#ifndef DEC_HEX_GLOBAL_H
#define DEC_HEX_GLOBAL_H

#include <string>

namespace G {
    const int cols = 16;
    const int isz = 8;

    extern int height, width;

    void setStatusBarText(std::string text);
}

#endif
