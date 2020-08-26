#include "Buffer.h"
#include "Global.h"
#include "Marker.h"
#include "Color.h"
#include "Base.h"
#include "Util.h"
#include "Table.h"
#include "Mode.h"

#include <curses.h>
#include <iostream>
#include <string>

void printUsage() {
    std::cout <<
        "No file provided.\n"
        "Usage: ./hexedit <fileName>\n"
        "Use option '-h' or --help' to get complete help."
    << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printUsage();
        return 0;
    }

    std::string fileName = argv[1];
    
    initscr();
    G::height = LINES;
    G::width = COLS;
    curs_set(0);
    cbreak();
    noecho();
    Colors::init();
    keypad(stdscr, TRUE);

    Buffer::load(fileName);
    Table::show();
    Marker::show();
    G::setStatusBarText("File Ready");
    Mode::normal();
    
    endwin();
    Buffer::finish();
    return 0;
}