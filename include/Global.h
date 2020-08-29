#ifndef DEC_HEX_GLOBAL_H
#define DEC_HEX_GLOBAL_H

#include <curses.h>
#include <string>

namespace G {
    const int isz = 8;

    extern int height, width;
    extern int cols;

    void setStatusBarText(std::string text);
}

inline void moveRight(int n = 1) {
    move(getcury(stdscr), getcurx(stdscr) + n);
}

inline void moveLeft(int n = 1) {
    move(getcury(stdscr), getcurx(stdscr) - n);
}

inline int printw(std::string str) {
    return printw(str.c_str());
}

#endif
