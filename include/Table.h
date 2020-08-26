#ifndef DEC_HEX_TABLE_H
#define DEC_HEX_TABLE_H

#include <cstddef>

namespace Table {
    void show(std::size_t fromPos = 0);
    void resize();
    void pos2coords(std::size_t pos, int &x, int &y);
    void pos2coordsText(std::size_t pos, int &x, int &y);
    void scrollIntoView(std::size_t pos);
}

#endif