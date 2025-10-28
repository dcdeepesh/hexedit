#include "Mode.h"
#include "InputSeq.h"
#include "Buffer.h"
#include "Marker.h"
#include "Global.h"
#include "Table.h"
#include "Base.h"

#include <curses.h>
#include <string>
#include <cstddef>

using std::to_string;

// These values can be found by (in Vim insert mode) doing Ctrl-V, then
// pressing the key (e.g. Ctrl-D), putting that in quotations and assigning it
// to a char. Then you can use your LSP or print to get the value.
enum special_keys {
    CONTROL_D = 4,
    CONTROL_U = 21,
};

namespace Mode {
    void normal() {
        int key;
        bool modified;
        size_t mPos;
        std::string ogValMsg;
        while (true) {
            mPos = Marker::getPos();
            Buffer::at(mPos, modified);
            ogValMsg = "";
            if (modified)
                ogValMsg = "-- (Modified) Original Value: " +
                to_string(Buffer::ogVal(mPos)) +
                " (0x" + Base::toHex(Buffer::ogVal(mPos)) + ")";

            G::setStatusBarText(
                "Position: " + to_string(mPos) +
                " (0x" + Base::toHex(mPos) + ")" +
                " " + ogValMsg
            );

            key = getch();
            switch (key) {
                case 'q':
                    if (InputSeq::quit()) return;
                    else break;

                case 'u':
                    InputSeq::undo();
                    break;

                case 'r':
                    InputSeq::revert();
                    break;
                    
                case 's':
                    InputSeq::save();
                    break;

                case CONTROL_U:
                    for (int i = 0; i < 10; i++) {
                        Marker::moveUp();
                    }
                    break;
                case CONTROL_D:
                    for (int i = 0; i < 10; i++) {
                        Marker::moveDown();
                    }
                    break;
                case 'g': // Not really correct, but proper logic for 'gg' is annoying
                    Marker::moveToOrigin();
                    break;
                case 'G':
                    Marker::moveToEnd();
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
        std::size_t mPos = Marker::getPos();
        G::setStatusBarText(
            "Editing byte at: " + to_string(mPos) + " (0x" + Base::toHex(mPos) + ")" +
            " -- Original value = " +
            to_string(static_cast<unsigned char>(Buffer::at(mPos))) +
            " (0x" + Base::toHex(Buffer::at(mPos)) + ")"
        );

        Marker::hide();
        int x, y;
        Table::pos2coords(mPos, x, y);
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
                    Buffer::set(mPos, Base::toText(newHexByte));
                    [[fallthrough]];
                case 'q':
                    Table::refresh();
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
