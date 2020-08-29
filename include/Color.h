#ifndef DEX_HEX_COLORS_H
#define DEX_HEX_COLORS_H

#include <curses.h>

enum ColorPairID {
    CPID_DEFAULT, CPID_HIGHLIGHT, CPID_HEADER, CPID_MODIFIED
};

namespace Colors {
    void init(bool stdColors);
}

namespace ColorPair {
    const int DEFAULT = COLOR_PAIR(CPID_DEFAULT);
    const int HIGHLIGHT = COLOR_PAIR(CPID_HIGHLIGHT);
    const int HEADER = COLOR_PAIR(CPID_HEADER);
    const int MODIFIED = COLOR_PAIR(CPID_MODIFIED);
}

#endif
