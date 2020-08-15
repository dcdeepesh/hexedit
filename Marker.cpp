#include "Marker.h"
#include "Global.h"
#include "Buffer.h"
#include "Table.h"
#include "Color.h"
#include "Base.h"
#include "Util.h"

#include <curses.h>
#include <string>

namespace Marker {
    int pos = 0;

    void setPos(int pos) {
        if (pos < 0 || pos >= Buffer::size())
            return;

        hide();
        Marker::pos = pos;
        Table::scrollIntoView(pos);
        show();
    }

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
