#ifndef DEX_HEX_COLORS_H
#define DEX_HEX_COLORS_H

#include <curses.h>

enum ColorPairID {
    CPID_DEFAULT, CPID_HIGHLIGHT, CPID_HEADER
};

namespace Colors {
    void init();
}

namespace ColorPair {
    const int DEFAULT = COLOR_PAIR(CPID_DEFAULT);
    const int HIGHLIGHT = COLOR_PAIR(CPID_HIGHLIGHT);
    const int HEADER = COLOR_PAIR(CPID_HEADER);
}

#endif
