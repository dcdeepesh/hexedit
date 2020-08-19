#include "Buffer.h"
#include "Global.h"
#include "Marker.h"
#include "Color.h"
#include "Base.h"
#include "Util.h"
#include "Table.h"

#include <curses.h>

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
    
    char newHexByte[3];
    innstr(newHexByte, 2);

    int key;
    while (true) {
        key = getch();
        switch (key) {
            case '\n':
                Buffer::set(Marker::pos, Base::toText(newHexByte));
            case 'q':
                Table::resize();
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
                newHexByte[curLeft ? 0 : 1] = key;
                if (!curLeft) moveLeft(2);
                curLeft = !curLeft;
                break;
        }
    }
}

void inputLoop(){
    int key;
    bool saveSeq = false, quitSeq = false;

    while (true) {
        key = getch();
        switch (key) {
            case 'q':
                saveSeq = false;
                if (!Buffer::isModified())
                    return;
                if (quitSeq) return;
                else quitSeq = true;
                break;

            case 's':
                quitSeq = false;
                if (saveSeq)
                    Buffer::save(SaveOption::SAME_FILE);
                else saveSeq = true;
                break;

            case 'n':
                if (saveSeq)
                    Buffer::save(SaveOption::NEW_FILE);
                quitSeq = saveSeq = false;
                break;

            case KEY_UP: case 'k':
                quitSeq = saveSeq = false;
                Marker::moveUp();
                break;

            case KEY_DOWN: case 'j':
                quitSeq = saveSeq = false;
                Marker::moveDown();
                break;

            case KEY_LEFT: case 'h':
                quitSeq = saveSeq = false;
                Marker::moveLeft();
                break;
                
            case KEY_RIGHT: case 'l':
                quitSeq = saveSeq = false;
                Marker::moveRight();
                break;

            case '\n': case 'i':
                quitSeq = saveSeq = false;
                editLoop();
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