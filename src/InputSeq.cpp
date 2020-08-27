#include "InputSeq.h"
#include "Buffer.h"
#include "Global.h"

#include <curses.h>

namespace InputSeq {
    void save() {
        G::setStatusBarText(
            "-- (s)-Save sequence -- [s=same file, n=new file]");
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

        G::setStatusBarText(
            "-- (q)-Quit sequence - There are unsaved changes -- [q=quit without saving]");

        int key = getch();
        return key == 'q';
    }
}