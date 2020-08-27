#include "InputSeq.h"
#include "Buffer.h"

#include <curses.h>

namespace InputSeq {
    void save() {
        int key = getch();
        switch (key) {
            case 's':
                Buffer::save(SaveOption::SAME_FILE);
                break;
            case 'n':
                Buffer::save(SaveOption::NEW_FILE);
                break;
        }
    }

    bool quit() {
        if (!Buffer::isModified())
            return true;

        int key = getch();
        return key == 'q';
    }
}