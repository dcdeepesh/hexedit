#ifndef DEC_HEX_TABLE_H
#define DEC_HEX_TABLE_H

namespace Table {
    void show(int fromPos = 0);
    void resize();
    void pos2coords(int pos, int &x, int &y);
    void pos2coordsText(int pos, int &x, int &y);
    void scrollIntoView(int pos);
}

#endif