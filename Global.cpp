#include "Global.h"

#include <curses.h>
#include <string>

namespace G {
    int height, width;
    
    void setStatusBarText(std::string text) {
        move(G::height-1, 0);
        attron(A_BOLD);

        for (char c : text)
            addch(c);

        attroff(A_BOLD);
    }
}