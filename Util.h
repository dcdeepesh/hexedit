#ifndef DEC_HEX_UTIL_H
#define DEC_HEX_UTIL_H

#include "Table.h"
#include "Marker.h"
#include "Global.h"

#include <curses.h>
#include <string>

inline void moveRight(int n = 1) {
    move(getcury(stdscr), getcurx(stdscr) + n);
}

inline void moveLeft(int n = 1) {
    move(getcury(stdscr), getcurx(stdscr) - n);
}

inline void newline(int howMany = 1) {
    for (int i = 0; i < howMany; i++)
        addch('\n');
}

inline int printw(std::string str) {
    return printw(str.c_str());
}

#endif
