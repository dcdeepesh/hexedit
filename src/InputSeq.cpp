#include "InputSeq.h"
#include "Buffer.h"
#include "Global.h"
#include "Table.h"
#include "Marker.h"

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

    void revert() {
        if (Buffer::isModified())
            G::setStatusBarText(
                "-- (r)-Revert sequence -- [r=undo all changes]");
        else
            G::setStatusBarText(
                "-- (r)-Revert sequence -- (No unsaved changes)");

        int key = getch();
        if (key == 'r' && Buffer::isModified()) {
            Buffer::revert();
            Table::refresh();
            Marker::show();
        }
    }

    void undo() {
        Buffer::undo(Marker::getPos());
        Table::refresh();
        Marker::show();
    }
}