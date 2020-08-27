#include "Marker.h"
#include "Global.h"
#include "Buffer.h"
#include "Table.h"
#include "Color.h"
#include "Base.h"

#include <curses.h>
#include <string>
#include <cstddef>

using std::size_t;

namespace Marker {
    size_t pos = 0;

    void setPos(size_t pos) {
        if (pos >= Buffer::size())
            return;

        hide();
        Marker::pos = pos;
        Table::scrollIntoView(pos);
        show();
    }

    size_t getPos() { return pos; }

    void moveUp()       { setPos(pos - G::cols); }
    void moveDown()     { setPos(pos + G::cols); }
    void moveLeft()     { setPos(pos - 1); }
    void moveRight()    { setPos(pos + 1); }
    void moveToOrigin() { setPos(0); }

    void displayByte(int colorPair) {
        int x, y;
        attron(colorPair);

        Table::pos2coords(pos, x, y);
        move(y, x);
        printw(Base::toHex(Buffer::at(pos)));
        Table::pos2coordsText(pos, x, y);
        move(y, x);
        addch(Base::toText(Buffer::at(pos)));
        
        attroff(colorPair);
        refresh();
    }

    void show() {
        displayByte(ColorPair::HIGHLIGHT);
    }

    void hide() {
        displayByte(ColorPair::DEFAULT);
    }
}
