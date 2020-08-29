#include "Global.h"

#include <curses.h>
#include <string>

namespace G {
    int height, width;
    int cols;
    
    void setStatusBarText(std::string text) {
        // clear the status bar first
        move(G::height-1, 0);
        for (int i = 0; i < G::width; i++)
            addch(' ');

        // write the actual msg
        move(G::height-1, 0);
        attron(A_BOLD);
        for (char c : text)
            addch(c);
        attroff(A_BOLD);
    }
}