#include "Mode.h"

#include <curses.h>
#include "InputSeq.h"
#include "Buffer.h"
#include "Marker.h"
#include "Global.h"
#include "Table.h"
#include "Base.h"
#include "Util.h"

namespace Mode {
    void normal() {
        int key;
        while (true) {
            key = getch();
            switch (key) {
                case 'q':
                    if (InputSeq::quit()) return;
                    else break;

                case 's':
                    InputSeq::save();
                    break;

                case KEY_UP: case 'k':
                    Marker::moveUp();
                    break;

                case KEY_DOWN: case 'j':
                    Marker::moveDown();
                    break;

                case KEY_LEFT: case 'h':
                    Marker::moveLeft();
                    break;

                case KEY_RIGHT: case 'l':
                    Marker::moveRight();
                    break;

                case '\n': case 'i':
                    Mode::edit();
                    break;
            }
        }
    }

    void edit() {
        Marker::hide();
        int x, y;
        Table::pos2coords(Marker::getPos(), x, y);
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
                    Buffer::set(Marker::getPos(), Base::toText(newHexByte));
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
}