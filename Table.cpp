#include "Table.h"
#include "Util.h"
#include "Base.h"
#include "Global.h"
#include "Buffer.h"
#include "Color.h"

#include <curses.h>
#include <sstream>

namespace Table {
    int startIndex = 0;
    int endIndex = 0;

    void show(int fromPos/*=0*/) {
        if (fromPos > Buffer::size())
            fromPos = Buffer::size();
        startIndex = fromPos;
        move(0, 0);
    
        // draw the top (index) line
        attron(ColorPair::HEADER);
        moveRight(G::isz + 1);
        for (int i = 0; i < G::cols; i++) {
            if (i % 4 == 0)
                addch(' ');
            printw(Base::toHex(i) + " ");
        }
        attroff(ColorPair::HEADER);
        newline();
    
        // draw the rest of the lines
        int index = fromPos;
        size_t numLines = (Buffer::size() - fromPos) / G::cols + 1;
        for (size_t line = 0; line < numLines && line < G::height-2; line++) {
            newline();
    
            // left index/offset
            attron(ColorPair::HEADER);
            printw(Base::toHex(index, G::isz) + " ");
            attroff(ColorPair::HEADER);
    
            // hex data
            std::stringstream ss;
            for (int i = 0; i < G::cols; i++) {
                if (i % 4 == 0)
                    addch(' ');
    
                char byte =
                    index == -1 ? 0 : Buffer::at(index);
                printw(Base::toHex(byte) + " ");
                ss << Base::toText(byte);
    
                if (index >= 0)
                    endIndex = index;

                if (index < Buffer::size() - 1 && index >= 0)
                    index++;
                else index = -1;
            }
    
            // string data (on the right)
            addch(' ');
            for (char c : ss.str())
                addch(c);
        }
    
        refresh();
    }

    void resize() {
        show(startIndex);
    }

    void pos2coords(int pos, int &x, int &y) {
        x = 0; y = 0;
        int scrOffset = pos - startIndex;

        y = scrOffset / G::cols;
        y += 2;     // top 2 lines

        int xOffset = scrOffset % G::cols;
        x = xOffset * 3;    // 2 hex digits, one space, each
        x += G::isz + 2;    // left column + 2 spaces
        x += xOffset / 4;   // extra spaces every 4 bytes
    }

    void pos2coordsText(int pos, int &x, int &y) {
        x = 0; y = 0;
        int scrOffset = pos - startIndex;

        y = scrOffset / G::cols;
        y += 2;     // top 2 lines

        int xOffset = scrOffset % G::cols;
        x = G::cols * 3;    // 2 hex digits, one space, each
        x += G::isz + 2;    // left column + 2 spaces
        x += G::cols / 4;   // extra spaces every 4 bytes
        x += xOffset;       // inside the table
    }

    void scrollIntoView(int pos) {
        if (pos >= startIndex && pos <= endIndex)
            return;
        else if (pos < startIndex)
            show(pos - pos % G::cols);
        else {
            // we know that the last line should contain pos,
            // so now we calculate the new minIndexInView
            int maxLinesInView = G::height - 2;
            int lineBeg = pos - pos % G::cols;
            int newMinIndex = lineBeg - (maxLinesInView - 1) * G::cols;
            show(newMinIndex);
        }
    }
}