#ifndef DEC_HEX_MARKER_H
#define DEC_HEX_MARKER_H

#include <cstddef>

namespace Marker {
    extern std::size_t pos;
    
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveToOrigin();

    void show();
    void hide();
}

#endif