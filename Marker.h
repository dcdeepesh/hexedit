#ifndef DEC_HEX_MARKER_H
#define DEC_HEX_MARKER_H

namespace Marker {
    extern int pos;
    
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveToOrigin();

    void show();
    void hide();
}

#endif