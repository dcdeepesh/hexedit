#include "Color.h"

#include <curses.h>

namespace Colors {
    void init() {
        start_color();
        init_pair(CPID_DEFAULT, COLOR_WHITE, COLOR_BLACK);
        init_pair(CPID_HIGHLIGHT, COLOR_BLACK, COLOR_YELLOW);
        init_pair(CPID_HEADER, COLOR_CYAN, COLOR_BLACK);
    }
}