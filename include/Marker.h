#ifndef DEC_HEX_MARKER_H
#define DEC_HEX_MARKER_H

#include <cstddef>

namespace Marker {
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveToOrigin();

    void show();
    void hide();
    std::size_t getPos();
}

#endif