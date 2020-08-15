#include <curses.h>
#include "Buffer.h"
#include "Global.h"
#include "Marker.h"
#include "Color.h"
#include "Base.h"
#include "Util.h"
#include "Table.h"

#include <iostream>

using std::cout;
using std::endl;

namespace G {
    int height, width;
}

void editLoop() {
    Marker::hide();
    int x, y;
    Table::pos2coords(Marker::pos, x, y);
    move(y, x);
    curs_set(2);
    bool curLeft = true;

    int key;
    while (true) {
        key = getch();
        switch (key) {
            case '\n':
                //save buffer
            case 'q':
                curs_set(0);
                Marker::show();
                return;

            case KEY_LEFT:
            case KEY_RIGHT:
                curLeft ? moveRight() : moveLeft();
                curLeft = !curLeft;
                break;

            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            case '8': case '9': case 'a': case 'b':
            case 'c': case 'd': case 'e': case 'f':
                addch(key);
                if (!curLeft) moveLeft(2);
                curLeft = !curLeft;
                break;
        }
    }
}

void inputLoop(){
    int key;
    while (true) {
        key = getch();
        switch (key) {
            case 'q': return;

            case KEY_UP:
            case 'k':
                Marker::moveUp();
                break;

            case KEY_DOWN:
            case 'j':
                Marker::moveDown();
                break;

            case KEY_LEFT:
            case 'h':
                Marker::moveLeft();
                break;
                
            case KEY_RIGHT:
            case 'l':
                Marker::moveRight();
                break;

            case '\n':  // enter key
            case 'i':
                editLoop();
                curs_set(0);
                break;
        }
    }
}

int main() {
    initscr();
    G::height = LINES;
    G::width = COLS;
    curs_set(0);
    cbreak();
    noecho();
    Colors::init();
    keypad(stdscr, TRUE);

    Buffer::load("Table.cpp");
    Table::show();
    Marker::show();
    inputLoop();
    
    endwin();
    Buffer::finish();
    return 0;
}